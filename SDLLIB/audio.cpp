#include <algorithm>
#include <cassert>
#include <cstring>

#include <SDL.h>

#include "audio.h"

// original code has 5 for windows, 4 for dos
// effectively one less as one is used to track streaming from disk
#define	MAX_SFX	4

enum SCompressType : uint8_t
{
	SCOMP_NONE=0,			// No compression -- raw data.
	SCOMP_WESTWOOD=1,		// Special sliding window delta compression.
	SCOMP_SONARC=33,		// Sonarc frame compression.
	SCOMP_SOS=99			// SOS frame compression.
};

static const int8_t ima_adpcm_index_table[] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};

static const int16_t ima_adpcm_step_table[89] = { 
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 
    19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 
    2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767 
};

// technically dsound objects
void *SoundObject;
void *PrimaryBufferPtr;

SFX_Type SoundType;
Sample_Type SampleType;

int StreamLowImpact;

static SDL_AudioDeviceID AudioDevice;
static SDL_AudioSpec ObtainedSpec;
static uint8_t *MixBuffer; // temp buffer for mixing

struct ChannelState
{
    const void *sample = NULL;
    SDL_AudioStream *stream = NULL;
    bool playing = false;
    int priority = 0;
    int16_t volume = 32767;
    
    uint8_t channels = 0;
    uint8_t bits = 0;
    uint16_t sample_rate = 0;

    uint32_t offset = 0;
    uint32_t length = 0;
    uint8_t *in_ptr = NULL;

    // compression state
    SCompressType compression = SCOMP_NONE;
    int8_t step = 0;
    int16_t predictor = 0;
} Channels[MAX_SFX];

static bool RefillStream(ChannelState &chan)
{
    uint32_t max_update = ObtainedSpec.samples; // assume the target rate is not lower

    if(chan.offset == chan.length)
        return false;

    if(chan.compression == SCOMP_SOS)
    {
        // ADPCM
        auto clamp = [](int v, int min, int max)
        {
            return v < min ? min : (v > max ? max : v);
        };
        int samples_to_gen = std::min(max_update, chan.length - chan.offset);
        // read blocks until we have enough samples
        while(samples_to_gen)
        {
            // read a block
            uint16_t block_in_size = *(uint16_t *)chan.in_ptr;
            uint16_t block_out_size = *(uint16_t *)(chan.in_ptr + 2);
            chan.in_ptr += 8; // there's also a 0000DEAF magic value

            // assert(block_out_size == block_in_size * 4);

            for(int i = 0; i < block_in_size; i++)
            {
                int16_t samples[2];
                auto b = *chan.in_ptr++;

                int nibble = b & 0xF;
                int step = ima_adpcm_step_table[chan.step];
                chan.step = clamp(chan.step + ima_adpcm_index_table[nibble], 0, 88);

                int diff = ((((nibble & 7) * 2 + 1) * step) >> 3) * (nibble & 8 ? -1 : 1);
                chan.predictor = clamp(chan.predictor + diff, -32768, 32767);

                samples[0] = chan.predictor;

                nibble = b >> 4;
                step = ima_adpcm_step_table[chan.step];
                chan.step = clamp(chan.step + ima_adpcm_index_table[nibble], 0, 88);

                diff = ((((nibble & 7) * 2 + 1) * step) >> 3) * (nibble & 8 ? -1 : 1);
                chan.predictor = clamp(chan.predictor + diff, -32768, 32767);

                samples[1] = chan.predictor;

                SDL_AudioStreamPut(chan.stream, samples, sizeof(samples));
            }

            chan.offset += block_out_size / 2;
            samples_to_gen -= block_out_size / 2;
        }
    }
    else
        return false; // shouldn't happen, but...

    // written all data, flush the stream
    if(chan.offset == chan.length)
        SDL_AudioStreamFlush(chan.stream);

    return true;
}

static void SDL_Audio_Callback(void *userdata, Uint8 *stream, int len)
{
    int samples = len / sizeof(int16_t);
    memset(stream, 0, len);
    auto stream16 = (int16_t *)stream;

    for(auto &chan : Channels)
    {
        if(!chan.playing)
            continue;

        // put more data into stream if needed
        if(SDL_AudioStreamAvailable(chan.stream) < len)
        {
            if(!RefillStream(chan) && !SDL_AudioStreamAvailable(chan.stream))
            {
                // no more data, it's finished
                chan.playing = false;
                continue;
            }
        }

        int stream_len = SDL_AudioStreamGet(chan.stream, MixBuffer, len);

        // mix into buffer
        auto mix16 = (int16_t *)MixBuffer;
        for(int s = 0; s < stream_len / sizeof(int16_t); s++)
            stream16[s] += (mix16[s] * chan.volume) >> 15;
    }
}

int File_Stream_Sample_Vol(char const *filename, int volume, bool real_time_start)
{
    // used for score
    //printf("%s\n", __PRETTY_FUNCTION__);
    return -1;
}

void Sound_Callback(void)
{
}

bool Audio_Init(void * window, int bits_per_sample, bool stereo, int rate, int reverse_channels)
{
    SDL_AudioSpec desired;
    desired.freq = rate;
    desired.format = AUDIO_S16; //bits_per_sample == 16 ? AUDIO_S16 : AUDIO_S8;
    desired.channels = stereo ? 2 : 1;
    desired.samples = 2048;
    desired.callback = SDL_Audio_Callback;

    // don't allow format change so I need less mising code
    int changes = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE | SDL_AUDIO_ALLOW_SAMPLES_CHANGE;
    AudioDevice = SDL_OpenAudioDevice(NULL, false, &desired, &ObtainedSpec, changes);

    if(!AudioDevice)
    {
        printf("Audio_Init: %s\n", SDL_GetError());
        return false;
    }

    MixBuffer = new uint8_t[ObtainedSpec.size];

    SDL_PauseAudioDevice(AudioDevice, false);

    SoundType = SFX_SDL;
    SampleType = SAMPLE_SDL;
    return true;
}

void Sound_End(void)
{
    SDL_CloseAudioDevice(AudioDevice);

    delete[] MixBuffer;

    for(auto &chan : Channels)
    {
        SDL_FreeAudioStream(chan.stream);
    }
}

void Stop_Sample(int handle)
{
    if(handle < 0 || handle >= MAX_SFX)
        return;

    SDL_LockAudio();

    Channels[handle].playing = false;

    SDL_UnlockAudio();
}

bool Sample_Status(int handle)
{
    return Channels[handle].playing;
}

bool Is_Sample_Playing(void const * sample)
{
    for(int i = 0; i < MAX_SFX; i++)
    {
        if(Channels[i].sample == sample)
            return Sample_Status(i);
    }

    return false;
}

void Stop_Sample_Playing(void const * sample)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int Play_Sample(void const *sample, int priority, int volume, signed short panloc)
{
    // find free channel
    int id;
    for(id = MAX_SFX - 1; id >= 0; id--)
    {
        if(!Channels[id].playing)
            break;
    }

    if(id < 0)
    {
        // look for lower priority channel instead
        for(id = 0; id < MAX_SFX; id++)
        {
            if(Channels[id].priority < priority)
                break;
        }

        // no channel found, give up
        if(id == MAX_SFX)
            return -1;

        Stop_Sample(id);
    }

    // play it
    auto header = (AUDHeaderType *)sample;
    int channels = header->Flags & 1 ? 2 : 1;
    int bits = header->Flags & 2 ? 16 : 8;

    if(header->Compression != SCOMP_SOS || channels != 1 || bits != 16)
    {
        printf("\trate %i size %i/%i channels %i bits %i comp %i\n", header->Rate, header->Size, header->UncompSize, channels, bits, header->Compression);
        return -1;
    }

    // setup channel
    SDL_LockAudio();
    auto &chan = Channels[id];

    chan.sample = sample;
    chan.playing = true;
    chan.priority = priority;
    chan.volume = volume * (32767 / MAX_SFX) / 100;

    // re-allocate stream if needed
    if(channels != chan.channels || bits != chan.bits || header->Rate != chan.sample_rate)
    {
        if(chan.stream)
            SDL_FreeAudioStream(chan.stream);

        chan.stream = SDL_NewAudioStream(bits == 16 ? AUDIO_S16 : AUDIO_S8, channels, header->Rate, ObtainedSpec.format, ObtainedSpec.channels, ObtainedSpec.freq);
    }
    else
        SDL_AudioStreamClear(chan.stream);

    chan.channels = channels;
    chan.bits = bits;
    chan.sample_rate = header->Rate;

    chan.offset = 0;
    chan.length = header->UncompSize / channels / (bits / 8);
    chan.in_ptr = (uint8_t *)sample + sizeof(AUDHeaderType);

    chan.compression = (SCompressType)header->Compression;

    if(chan.compression == SCOMP_SOS)
    {
        chan.step = 0;
        chan.predictor = 0;
    }

    SDL_UnlockAudio();

    return id;
}

int Set_Score_Vol(int volume)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void Fade_Sample(int handle, int ticks)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int Get_Digi_Handle(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

bool Set_Primary_Buffer_Format(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

bool Start_Primary_Sound_Buffer(bool forced)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

void Stop_Primary_Sound_Buffer(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

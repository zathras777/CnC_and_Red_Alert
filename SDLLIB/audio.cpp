#include "audio.h"

// technically dsound objects
void *SoundObject;
void *PrimaryBufferPtr;

SFX_Type SoundType;
Sample_Type SampleType;

int StreamLowImpact;

int File_Stream_Sample_Vol(char const *filename, int volume, bool real_time_start)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void Sound_Callback(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

bool Audio_Init(void * window, int bits_per_sample, bool stereo , int rate , int reverse_channels)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

void Sound_End(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Stop_Sample(int handle)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

bool Sample_Status(int handle)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

bool Is_Sample_Playing(void const * sample)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

void Stop_Sample_Playing(void const * sample)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int Play_Sample(void const *sample, int priority, int volume, signed short panloc)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
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

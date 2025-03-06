#include "wsa.h"

void *Open_Animation(char const *file_name, char *user_buffer, long user_buffer_size, WSAOpenType user_flags, unsigned char *palette)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

void Close_Animation(void *handle)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

bool Animate_Frame(void *handle, GraphicViewPortClass& view, int frame_number, int x_pixel, int y_pixel,
    WSAType flags_and_prio, void *magic_cols, void *magic)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

int Get_Animation_Frame_Count(void *handle)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

unsigned int Apply_XOR_Delta(char *source_ptr, char *delta_ptr)
{
    auto udelta = (uint8_t *)delta_ptr;

    // top_loop
    while(true)
    {
        uint8_t b = *udelta++;

        if(b == 0)
        {
            // SHORTRUN
            int count = *udelta++; // get count
            uint8_t xor_b = *udelta++; // get XOR byte
            do
            {
                *source_ptr ^= xor_b; // XOR that byte
                source_ptr++;
            }
            while(--count);
        }
        else if(b & 0x80)
        {
            // By now, we know it must be a LONGDUMP, SHORTSKIP, LONGRUN, or LONGSKIP
            b &= 0x7F;
            if(b == 0)
            {
                int count = udelta[0] | udelta[1] << 8; // get word code
                udelta += 2;

                if(!count)
                    return 0; // long count of zero means stop

                if(count & 0x8000)
                {
                    count &= 0x7FFF;
                    if(count & 0x4000)
                    {
                        // LONGRUN
                        uint8_t xor_b = *udelta++; // get XOR byte
                        do
                        {
                            *source_ptr ^= xor_b; // XOR that byte
                            source_ptr++;
                        }
                        while(--count);
                    }
                    else
                    {
                        // LONGDUMP
                        do
                        {
                            uint8_t xor_b = *udelta++; // get delta XOR byte
                            *source_ptr ^= xor_b; // xor that byte on the dest
                            source_ptr++;
                        }
                        while(--count);
                    }
                }

                // LONGSKIP
                source_ptr += count;
            }
            else // SHORTSKIP
                source_ptr += b;
        }
        else
        {
            // SHORTDUMP
            int count = b;

            do
            {
                uint8_t xor_b = *udelta++; // get delta XOR byte
                *source_ptr ^= xor_b; // xor that byte on the dest
                source_ptr++;
            }
            while(--count);
        }
    }

    return 0;
}
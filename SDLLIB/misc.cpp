#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "misc.h"
#include "timer.h"
#include "ww_win.h"

SurfaceMonitorClass	AllSurfaces;

extern "C"
{
long RandNumb;
}

void (*Misc_Focus_Loss_Function)(void);
void (*Misc_Focus_Restore_Function)(void);

bool Set_Video_Mode(void *hwnd, int w, int h, int bits_per_pixel)
{
    printf("%s\n", __func__);
    return true;
}

void Wait_Blit(void)
{
    // nothing to wait for
}

void Delay(int duration)
{
    auto target = WindowsTimer->Get_System_Tick_Count() + duration;

	while(WindowsTimer->Get_System_Tick_Count() < target)
		Video_End_Frame();
}

void *Build_Fading_Table(void const *palette, void *dest, long int color, long int frac)
{
    unsigned matchvalue;
    uint8_t targetred;
    uint8_t targetgreen;
    uint8_t targetblue;
    uint8_t idealred;
    uint8_t idealgreen;
    uint8_t idealblue;
    uint8_t matchcolor;

    // If the source palette is NULL, then just return with current fading table pointer.
    if(!palette || !dest)
        return dest;

    // Fractions above 255 become 255.
    if(frac > 255)
        frac = 255;

    // Record the target gun values.
    auto pal8 = (uint8_t *)palette;
    targetred = pal8[color * 3 + 0];
    targetgreen = pal8[color * 3 + 0];
    targetblue = pal8[color * 3 + 0];

    // Main loop

    auto dptr = (uint8_t *)dest;

    // Transparent black never gets remapped.
    *dptr++ = 0;

    for(int remap_index = 1; remap_index < 256; remap_index++)
    {
        // new = orig - ((orig-target) * fraction);
        uint8_t origred = pal8[remap_index * 3 + 0];
        uint8_t origgreen = pal8[remap_index * 3 + 1];
        uint8_t origblue = pal8[remap_index * 3 + 2];

        uint16_t tmp = (origred - targetred) * (frac >> 1);
        idealred = origred - (tmp >> 7);

        tmp = (origgreen - targetgreen) * (frac >> 1);
        idealgreen = origgreen - (tmp >> 7);

        tmp = (origblue - targetblue) * (frac >> 1);
        idealblue = origblue - (tmp >> 7);

        // Sweep through the entire existing palette to find the closest
	    // matching color.  Never matches with color 0.

        matchcolor = color; // Default color (self).
        matchvalue = -1; // Ridiculous match value init.

        auto palptr = pal8 + 3;

        for(int color_index = 1; color_index < 256; color_index++)
        {
            if(color_index != remap_index)
            {
                int compval = 0;

                // Build the comparison value based on the sum of the differences of the color
                // guns squared
                int diff = palptr[0] - idealred;
                compval += diff * diff;
                diff = palptr[1] - idealgreen;
                compval += diff * diff;
                diff = palptr[2] - idealgreen;
                compval += diff * diff;

                if(compval == 0) // If perfect match found then quit early.
                {
                    matchcolor = color_index;
                    break;
                }

                if(compval < matchvalue)
                {
                    matchcolor = color_index;
                    matchvalue = compval;
                }
            }
            palptr += 3;
        }

        // When the loop exits, we have found the closest match.
        *dptr++ = matchcolor;
    }

    return dest;
}


int Confine_Rect(int *x, int *y, int dw, int dh, int width, int height)
{
    int ret = 0;

    if(*x < 0)
    {
        *x = 0;
        ret = 1;
    }
    else if(*x + dw > width)
    {
        *x -= (*x + dw) - width;
        ret = 1;
    }

    if(*y < 0)
    {
        *y = 0;
        ret = 1;
    }
    else if(*y + dh > height)
    {
        *y -= (*y + dh) - height;
        ret = 1;
    }

    return ret;
}

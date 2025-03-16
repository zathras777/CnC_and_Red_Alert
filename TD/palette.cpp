#include <stdio.h>

#include "palette.h"
#include "function.h"

unsigned char CurrentPalette[3 * 256];

void Fade_Palette_To(unsigned char *palette, int fade, void (*callback)())
{
    printf("%s\n", __func__);
    Set_Palette(palette);
}

void Set_Palette(void *palette)
{
    memcpy(CurrentPalette, palette, 256 * 3);
    Do_Set_Palette(palette);
}
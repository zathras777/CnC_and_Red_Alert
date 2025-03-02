#include <stdio.h>

extern unsigned char CurrentPalette;

void Set_Palette(void *palette)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}
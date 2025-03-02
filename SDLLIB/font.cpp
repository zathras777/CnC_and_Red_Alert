#include "font.h"

int FontXSpacing;
int FontYSpacing;
char FontWidth ;
char FontHeight;
char *FontWidthBlockPtr;

void const *FontPtr;

void *Set_Font(void const *fontptr)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

int Char_Pixel_Width(char chr)
{
    return 1;
}

unsigned int String_Pixel_Width(char const *string)
{
    return 1;
}

void Set_Font_Palette_Range(void const *palette, int start_idx, int end_idx)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}
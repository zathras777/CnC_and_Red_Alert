#include <stdio.h>

#include "palette.h"

// two current palettes?
unsigned char CurrentPalette[3 * 256];

PaletteClass PaletteClass::CurrentPalette;

RGBClass ohno;

PaletteClass::PaletteClass()
{

}
PaletteClass::PaletteClass(const RGBClass &col)
{
    for(int i = 0; i < COLOR_COUNT; i++)
        data[i] = col;
}

void PaletteClass::Set(int fade, void (*callback)())
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void PaletteClass::Adjust(int)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}
void PaletteClass::Adjust(int, PaletteClass &)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}
void PaletteClass::Partial_Adjust(int, char *)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void PaletteClass::Partial_Adjust(int, PaletteClass &, char *)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int PaletteClass::Closest_Color(const RGBClass &) const
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

RGBClass &PaletteClass::operator[](int index)
{
    return data[index];
}

const RGBClass &PaletteClass::operator[](int index) const
{
    return data[index];
}

PaletteClass::operator unsigned char *()
{
    return (unsigned char *)data;
}

PaletteClass::operator const unsigned char *() const
{
    return (const unsigned char *)data;
}

#include <stdio.h>

#include "palette.h"

unsigned char CurrentPalette[3 * 256];

PaletteClass PaletteClass::CurrentPalette;

RGBClass ohno;

PaletteClass::PaletteClass()
{

}
PaletteClass::PaletteClass(const RGBClass &)
{

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
    return ohno;
}

const RGBClass &PaletteClass::operator[](int index) const
{
    return ohno;
}

PaletteClass::operator unsigned char *()
{
    return NULL;
}

PaletteClass::operator const unsigned char *() const
{
    return NULL;
}

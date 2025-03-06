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
    if(fade || callback)
        printf("PaletteClass::Set(%i, %p)\n", fade, callback);
    // TODO: fade somehow?
    CurrentPalette = *this;
    Set_Palette(*this);
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

int PaletteClass::Closest_Color(const RGBClass &col) const
{
    int index = -1;
    int diff = 256 * 3;

    for(int i = 0; i < COLOR_COUNT; i++)
    {
        int new_diff = std::abs(col.Red_Component() - data[i].Red_Component())
                     + std::abs(col.Green_Component() - data[i].Green_Component())
                     + std::abs(col.Blue_Component() - data[i].Blue_Component());

        if(new_diff == 0)
            return i;

        if(new_diff < diff)
        {
            index = i;
            diff = new_diff;
        }
    }

    return index;
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

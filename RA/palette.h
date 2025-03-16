#pragma once
#include <stdlib.h>

#include "rgb.h"

class PaletteClass
{
public:
	PaletteClass();
	PaletteClass(const RGBClass &);

	void Set(int fade = 0, void (*callback)() = NULL);

	void Adjust(int);
	void Adjust(int, PaletteClass &);
	void Partial_Adjust(int, char *);
	void Partial_Adjust(int, PaletteClass &, char *);

	int Closest_Color(const RGBClass &) const;

	RGBClass &operator[](int index);
	const RGBClass &operator[](int index) const;

	operator unsigned char *();
	operator const unsigned char *() const;

	static const int COLOR_COUNT = 256;

	RGBClass data[COLOR_COUNT];

	static PaletteClass CurrentPalette;
};

void Set_Palette(void *palette);

extern "C" unsigned char  *CurrentPalette;

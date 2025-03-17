#include "function.h"

void *Conquer_Build_Fading_Table(void const *palette, void *dest, int color, int frac)
{
	unsigned matchvalue;
    uint8_t targetred;
    uint8_t targetgreen;
    uint8_t targetblue;
    uint8_t idealred;
    uint8_t idealgreen;
    uint8_t idealblue;
    uint8_t matchcolor;

	const int ALLOWED_COUNT = 16;
	const int ALLOWED_START = 256 - ALLOWED_COUNT;

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

	int remap_index;
    for(remap_index = 1; remap_index < ALLOWED_START; remap_index++)
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

        // Sweep through a limited set of existing colors to find the closest
	    // matching color.

        matchcolor = color; // Default color (self).
        matchvalue = -1; // Ridiculous match value init.

        auto palptr = pal8 + ALLOWED_START * 3;

        for(int color_index = ALLOWED_START; color_index < 256; color_index++)
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

            palptr += 3;
        }

        // When the loop exits, we have found the closest match.
        *dptr++ = matchcolor;
    }

	// Fill the remainder of the remap table with values
	// that will remap the color to itself.
	for(; remap_index < 256; remap_index++)
		*dptr++ = remap_index;

    return dest;
}

void Fat_Put_Pixel(int x, int y, int color, int size, GraphicViewPortClass &gpage)
{
	gpage.Fill_Rect(x, y, x + size, y + size, color);
}

// from RA readline.cpp
void strtrim(char * buffer)
{
	if (buffer) {

		/*
		**	Strip leading white space from the string.
		*/
		char * source = buffer;
		while (isspace(*source)) {
			source++;
		}
		if (source != buffer) {
			int len = strlen(source);
			memmove(buffer, source, len + 1);
		}

		/*
		**	Clip trailing white space from the string.
		*/
		for (int index = strlen(buffer)-1; index >= 0; index--) {
			if (isspace(buffer[index])) {
				buffer[index] = '\0';
			} else {
				break;
			}
		}
	}
}

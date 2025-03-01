/*
**	Command & Conquer Red Alert(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***************************************************************************
;**   C O N F I D E N T I A L --- W E S T W O O D   A S S O C I A T E S   **
;***************************************************************************
;*                                                                         *
;*                 Project Name : Palette 32bit Library.                   *
;*                                                                         *
;*                    File Name : PALETTE.H                                *
;*                                                                         *
;*                   Programmer : Scott K. Bowen                           *
;*                                                                         *
;*                   Start Date : April 25, 1994                           *
;*                                                                         *
;*                  Last Update : April 27, 1994 [BRR]							*
;*                                                                         *
;* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef PALETTE_H
#define PALETTE_H

#include <gbuffer.h>
/*
********************************* Constants *********************************
*/
#define RGB_BYTES			3
#define PALETTE_SIZE		256
#define PALETTE_BYTES	768

// ?? isn't declared anywhere, so this is a hack to make things compile
class RGBClass;

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
	//operator const void *();

	//operator bool();

	static const int COLOR_COUNT = 256;

	static PaletteClass CurrentPalette;
};

/*
******************************** Prototypes *********************************
*/
/*
-------------------------------- Palette.cpp --------------------------------
*/
void Set_Palette(void *palette);
void Set_Palette_Color(void *palette, int color, void *data);
void Fade_Palette_To(void *palette1, unsigned int delay, void (*callback)() );

/*
-------------------------------- loadpal.cpp --------------------------------
*/
void Load_Palette(char *palette_file_name, void *palette_pointer);

/*
------------------------------- morphpal.cpp --------------------------------
*/
void Morph_Palette (void *src_palette, void *dst_palette, unsigned int delay,
	void *callback);

/*
---------------------------------- pal.asm ----------------------------------
*/
#ifdef __cplusplus
extern "C" {
#endif

extern void Set_Palette_Range(void *palette);
extern bool Bump_Color(void *palette, int changable, int target);

#ifdef __cplusplus
}
#endif
extern "C" unsigned char  CurrentPalette[];		/* in pal.asm */


#endif // PALETTE_H

/***************************** End of palette.h ****************************/

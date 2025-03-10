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
 **      C O N F I D E N T I A L --- W E S T W O O D   S T U D I O S      **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Westwood 32 bit Library                  *
 *                                                                         *
 *                    File Name : AUDIO.H                                  *
 *                                                                         *
 *                   Programmer : Phil W. Gorrow                           *
 *                                                                         *
 *                   Start Date : March 10, 1995                           *
 *                                                                         *
 *                  Last Update : March 10, 1995   [PWG]                   *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <stdint.h>
#include "wwstd.h"

/*=========================================================================*/
/* AUD file header type																		*/
/*=========================================================================*/
#define	AUD_FLAG_STEREO	1
#define	AUD_FLAG_16BIT		2

// PWG 3-14-95: This structure used to have bit fields defined for Stereo
//   and Bits.  These were removed because watcom packs them into a 32 bit
//   flag entry even though they could have fit in a 8 bit entry.
#pragma pack(push, 1)
typedef struct {
	uint16_t Rate;				// Playback rate (hertz).
	int32_t	 Size;				// Size of data (bytes).
	int32_t	 UncompSize;		// Size of data (bytes).
	uint8_t  Flags;				// Holds flags for info
								//  1: Is the sample stereo?
								//  2: Is the sample 16 bits?
	uint8_t  Compression;		// What kind of compression for this sample?
} AUDHeaderType;
#pragma pack(pop)


/*=========================================================================*/
/*	There can be a different sound driver for sound effects, digitized		*/
/*	samples, and musical scores.  Each one must be of these specified			*/
/*	types.																						*/
/*=========================================================================*/
typedef enum {
	SAMPLE_NONE,		// No digitized sounds will be played.
	SAMPLE_SDL,
	SAMPLE_TEMP=0x1000,
	SAMPLE_LAST
} Sample_Type;

typedef enum {
	SFX_NONE,			// No sound effects will be played.
	SFX_SDL,
	SFX_TEMP=0x1000,
	SFX_LAST
} SFX_Type;



/*=========================================================================*/
/* The following prototypes are for the file: SOUNDIO.CPP						*/
/*=========================================================================*/
int File_Stream_Sample_Vol(char const *filename, int volume, bool real_time_start = false);
void Sound_Callback(void);
bool Audio_Init( void * window , int bits_per_sample, bool stereo , int rate , int reverse_channels);
void Sound_End(void);
void Stop_Sample(int handle);
bool Sample_Status(int handle);
bool Is_Sample_Playing(void const * sample);
void Stop_Sample_Playing(void const * sample);
int Play_Sample(void const *sample, int priority=0xFF, int volume=0xFF, signed short panloc = 0x0);
int Play_Sample_Handle(void const *sample, int priority, int volume, signed short panloc, int id);
int Set_Score_Vol(int volume);
void Fade_Sample(int handle, int ticks);
int Get_Free_Sample_Handle(int priority);
int Get_Digi_Handle(void);
bool Start_Primary_Sound_Buffer (bool forced);
void Stop_Primary_Sound_Buffer (void);

typedef void (*AudioCallback)(uint8_t *stream, int len);
uint32_t Get_Audio_Device();
void *Get_Audio_Spec();
AudioCallback *Get_Audio_Callback_Ptr(); // returns a ptr to a function ptr as we're passing this the wrong way around

extern SFX_Type SoundType;
extern Sample_Type SampleType;

extern int StreamLowImpact;

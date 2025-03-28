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


/*=========================================================================*/
/* The following prototypes are for the file: SOUNDIO.CPP						*/
/*=========================================================================*/

short Decompress_Frame(void * source, void * dest, short size);
int __cdecl Stream_Sample_Vol(void *buffer, long size, BOOL (*callback);
int __cdecl Stream_Sample(void *buffer, long size, BOOL (*callback);
int __cdecl File_Stream_Sample(char const *filename);
int __cdecl File_Stream_Sample_Vol(char const *filename, int volume);
void __cdecl _saveregs _loadds Sound_Callback(void);
void __cdecl far _saveregs _loadds maintenance_callback(void);
void  __cdecl Load_Sample(char const *filename);
long __cdecl Load_Sample_Into_Buffer(char const *filename, void *buffer, long size);
long __cdecl Sample_Read(int fh, void *buffer, long size);
void __cdecl Free_Sample(void const *sample);
BOOL __cdecl Sound_Init(int sfx, int score, int sample);
void far VQA_TimerCallback(void);
BOOL Audio_Init(int sample, int address, int inter, int dma);
void __cdecl Sound_End(void);
void __cdecl Stop_Sample(int handle);
BOOL __cdecl Sample_Status(int handle);
BOOL __cdecl Is_Sample_Playing(void const * sample);
void __cdecl Stop_Sample_Playing(void const * sample);
int __cdecl Play_Sample(void const *sample);
int __cdecl Play_Sample_Vol(void const *sample, int priority, int volume);
int __cdecl Set_Sound_Vol(int volume);
int __cdecl Set_Score_Vol(int volume);
void __cdecl Fade_Sample(int handle, int ticks);
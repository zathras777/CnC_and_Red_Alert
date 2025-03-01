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
 **     C O N F I D E N T I A L --- W E S T W O O D   S T U D I O S       **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : 32 bit library                           *
 *                                                                         *
 *                    File Name : MISC.H                                   *
 *                                                                         *
 *                   Programmer : Scott K. Bowen                           *
 *                                                                         *
 *                   Start Date : August 3, 1994                           *
 *                                                                         *
 *                  Last Update : August 3, 1994   [SKB]                   *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef MISC_H
#define MISC_H

extern	LPDIRECTDRAWSURFACE	PaletteSurface;

/*========================= C++ Routines ==================================*/


/*=========================================================================*/
/* The following prototypes are for the file: DDRAW.CPP							*/
/*=========================================================================*/
void 		Process_DD_Result(HRESULT result, int display_ok_msg);
bool 		Set_Video_Mode(HWND hwnd, int w, int h, int bits_per_pixel);
void 		Reset_Video_Mode(void);
unsigned 	Get_Free_Video_Memory(void);
void 		Wait_Blit(void);
unsigned 	Get_Video_Hardware_Capabilities(void);

extern "C" void Wait_Vert_Blank(void);
extern "C" void Set_DD_Palette (void *palette);

/*
** Pointer to function to call if we detect a focus loss
*/
extern	void (*Misc_Focus_Loss_Function)(void);
/*
** Pointer to function to call if we detect a surface restore
*/
extern	void (*Misc_Focus_Restore_Function)(void);


/*
 *  Flags returned by Get_Video_Hardware_Capabilities
 */
/* Hardware blits supported? */
#define	VIDEO_BLITTER					1

/* Hardware blits asyncronous? */
#define	VIDEO_BLITTER_ASYNC  		2

/* Can palette changes be synced to vertical refresh? */
#define	VIDEO_SYNC_PALETTE			4

/* Is the video cards memory bank switched? */
#define	VIDEO_BANK_SWITCHED			8

/* Can the blitter do filled rectangles? */
#define	VIDEO_COLOR_FILL				16

/* Is there no hardware assistance avaailable at all? */
#define	VIDEO_NO_HARDWARE_ASSIST	32



/*
 * Definition of surface monitor class
 *
 * This class keeps track of all the graphic buffers we generate in video memory so they
 *  can be restored after a focus switch.
*/

#define	MAX_SURFACES	20

class SurfaceMonitorClass {

	public:

		SurfaceMonitorClass();

		void	Add_DD_Surface (LPDIRECTDRAWSURFACE);
		void	Remove_DD_Surface (LPDIRECTDRAWSURFACE);
		bool	Got_Surface_Already (LPDIRECTDRAWSURFACE);
		void	Restore_Surfaces (void);
		void	Set_Surface_Focus ( bool in_focus );
		void	Release(void);

		bool	SurfacesRestored;

	private:

		LPDIRECTDRAWSURFACE	Surface[MAX_SURFACES];
		bool						InFocus;

};

extern	SurfaceMonitorClass	AllSurfaces;				//List of all direct draw surfaces


/*=========================================================================*/
/* The following variables are declared in: DDRAW.CPP								*/
/*=========================================================================*/
extern	LPDIRECTDRAW	DirectDrawObject;
extern	LPDIRECTDRAW2	DirectDraw2Interface;
extern	HWND				MainWindow;
extern bool 				SystemToVideoBlits;
extern bool				VideoToSystemBlits;
extern bool				SystemToSystemBlits;
extern bool				OverlappedVideoBlits;	// Can video driver blit overlapped regions?

/*=========================================================================*/
/* The following prototypes are for the file: EXIT.CPP							*/
/* Prog_End Must be supplied by the user program in startup.cpp				*/
/*=========================================================================*/
void Prog_End(void);
void Exit(INT errorval, const BYTE *message, ...);

/*=========================================================================*/
/* The following prototypes are for the file: DELAY.CPP							*/
/*=========================================================================*/
void Delay(int duration);


/*========================= Assembly Routines ==============================*/

#ifdef __cplusplus
extern "C" {
#endif



void * Build_Fading_Table(void const *palette, void const *dest, long int color, long int frac);
/*=========================================================================*/
/* The following prototype is for the file: CRC.ASM							*/
/*=========================================================================*/

long Calculate_CRC(void *buffer, long length);


extern int Clip_Rect ( int * x , int * y , int * dw , int * dh ,
	       	   			 int width , int height ) ;
extern int Confine_Rect ( int * x , int * y , int dw , int dh ,
	      	      			 int width , int height ) ;



#ifdef __cplusplus
}
#endif

/*=========================================================================*/

#endif // MISC_H


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
 **   C O N F I D E N T I A L --- W E S T W O O D   A S S O C I A T E S   **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Westwood 32 Bit Library						*
 *                                                                         *
 *                    File Name : GBUFFER.H                                *
 *                                                                         *
 *                   Programmer : Phil W. Gorrow                           *
 *                                                                         *
 *                   Start Date : May 26, 1994                             *
 *                                                                         *
 *                  Last Update : October 9, 1995   []                     *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *	This module contains the definition for the graphic buffer class.  The	*
 * primary functionality of the graphic buffer class is handled by inline	*
 * functions that make a call through function pointers to the correct		*
 * routine.  This has two benefits:														*
 *																									*
 *																									*
 *		1) C++ name mangling is not a big deal since the function pointers	*
 *		   point to functions in standard C format.									*
 *		2) The function pointers can be changed when we set a different		*
 *       graphic mode.  This allows us to have both supervga and mcga		*
 *			routines present in memory at once.											*
 *																									*
 * In the basic library, these functions point to stub routines which just	*
 * return.  This makes a product that just uses a graphic buffer take the	*
 * minimum amount of code space.  For programs that require MCGA or VESA	*
 * support, all that is necessary to do is link either the MCGA or VESA		*
 * specific libraries in, previous to WWLIB32.  The linker will then 		*
 * overide the the necessary stub functions automatically.						*
 *																									*
 * In addition, there are helpful inline function calls for parameter		*
 * ellimination.  This header file gives the defintion for all					*
 * GraphicViewPort and GraphicBuffer classes.  										*
 *																									*
 * Terminology:																				*
 *																									*
 *	Buffer Class - A class which consists of a pointer to an allocated		*
 *		buffer and the size of the buffer that was allocated.						*
 *																									*
 *	Graphic ViewPort - The Graphic ViewPort defines a window into a 			*
 *		Graphic Buffer.  This means that although a Graphic Buffer 				*
 *		represents linear memory, this may not be true with a Graphic			*
 *		Viewport.  All low level functions that act directly on a graphic		*
 *		viewport are included within this class.  This includes but is not	*
 *		limited to most of the functions which can act on a Video Viewport	*
 *		Video Buffer.																			*
 *																									*
 * Graphic Buffer - A Graphic Buffer is an instance of an allocated buffer	*
 *		used to represent a rectangular region of graphics memory.				*
 *		The HidBuff	and BackBuff are excellent examples of a Graphic Buffer.	*
 *																									*
 * Below is a tree which shows the relationship of the VideoBuffer and 		*
 * Buffer classes to the GraphicBuffer class:										*
 *																									*
 *	  BUFFER.H				 GBUFFER.H			  BUFFER.H				 VBUFFER.H	*
 *  ----------          ----------         ----------          ----------	*
 * |  Buffer  |        | Graphic  |       |  Buffer  |        |  Video   |	*
 * |  Class   |        | ViewPort |       |  Class   |        | ViewPort |	*
 *  ----------          ----------         ----------          ----------	*
 *            \        /                             \        /				*
 *             \      /                               \      /					*
 *            ----------                             ----------				*
 *           |  Graphic |                           |  Video   |				*
 *           |  Buffer  |                           |  Buffer  |				*
 *            ----------                             ---------- 				*
 *	  			  GBUFFER.H			                       VBUFFER.H					*
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 *   GBC::GraphicBufferClass -- inline constructor for GraphicBufferClass  *
 *   GVPC::Remap -- Short form to remap an entire graphic view port        *
 *   GVPC::Get_XPos -- Returns x offset for a graphic viewport class       *
 *   GVPC::Get_Ypos -- Return y offset in a GraphicViewPortClass           *
 *   VVPC::Get_XPos -- Get the x pos of the VP on the Video                *
 *   VVPC::Get_YPos -- Get the y pos of the VP on the video                *
 *   GBC::Get_Graphic_Buffer -- Get the graphic buffer of the VP.          *
 *   GVPC::Draw_Line -- Stub function to draw line in Graphic Viewport Class*
 *   GVPC::Fill_Rect -- Stub function to fill rectangle in a GVPC          *
 *   GVPC::Remap -- Stub function to remap a GVPC                          *
 *   GVPC::Print -- stub func to print a text string                       *
 *   GVPC::Print -- Stub function to print an integer                      *
 *   GVPC::Print -- Stub function to print a short to a graphic viewport   *
 *   GVPC::Print -- stub function to print a long on a graphic view port   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#define WIN32_LEAN_AND_MEAN
//#include <ddraw.h>


#ifndef GBUFFER_H
#define GBUFFER_H

#include <stdlib.h>

#include "wwstd.h"
#include "drawbuff.h"
#include "buffer.h"
#include "ww_win.h"
#include "iconcach.h"

#ifndef FUNCTION_H

#ifndef BITMAPCLASS
#define BITMAPCLASS
class BitmapClass
{
	public:
		BitmapClass(int w, int h, unsigned char * data) :
			Width(w), Height(h), Data(data) {};

		int Width;
		int Height;
		unsigned char * Data;
};

class TPoint2D
{
	public:
		TPoint2D(int xx, int yy) : x(xx), y(yy) {};
		TPoint2D(void) : x(0), y(0) {};

		int x;
		int y;
};
#endif

#endif


//////////////////////////////////////////////////////////////////////////
//
// Defines for direct draw
//
//
extern	void *			MainWindow;			//handle to programs main window

extern GraphicBufferClass *WindowBuffer;

enum GBC_Enum {
	GBC_NONE				= 0,
	GBC_VIDEOMEM		= 1,
	GBC_VISIBLE			= 2,
};

#define	NOT_LOCKED		NULL

/*=========================================================================*/
/* Define the screen width and height to make portability to other modules	*/
/*		easier.																					*/
/*=========================================================================*/
#define	DEFAULT_SCREEN_WIDTH		320
#define	DEFAULT_SCREEN_HEIGHT	200

/*=========================================================================*/
/* Let the compiler know that a GraphicBufferClass exists so that it can	*/
/*		keep a pointer to it in a VideoViewPortClass.								*/
/*=========================================================================*/
class GraphicViewPortClass;
class GraphicBufferClass;
class VideoViewPortClass;
class VideoBufferClass;

GraphicViewPortClass *Set_Logic_Page(GraphicViewPortClass *ptr);
GraphicViewPortClass *Set_Logic_Page(GraphicViewPortClass &ptr);

/*=========================================================================*/
/* GraphicViewPortClass - Holds viewport information on a viewport which	*/
/*		has been attached to a GraphicBuffer.  A viewport is effectively a	*/
/*		rectangular subset of the full buffer which is used for clipping and	*/
/*		the like.																				*/
/*																									*/
/*			char	  	*Buffer	-		is the offset to view port buffer			*/
/*			int	  	Width		-		is the width of view port						*/
/*			int	  	Height	-		is the height of view port						*/
/*			int	  	XAdd		-		is add value to go from the end of a line	*/
/*											to the beginning of the next line			*/
/*			int		XPos;		- 		x offset into its associated VideoBuffer	*/
/*			int		YPos;		-		y offset into its associated VideoBuffer	*/
/*=========================================================================*/
class GraphicViewPortClass {
	public:

		/*===================================================================*/
		/* Define the base constructor and destructors for the class			*/
		/*===================================================================*/
		GraphicViewPortClass(GraphicBufferClass* graphic_buff, int x, int y, int w, int h);
		GraphicViewPortClass();
		~GraphicViewPortClass();

		/*===================================================================*/
		/* define functions to get at the private data members					*/
		/*===================================================================*/
		uint8_t*	Get_Offset(void);
		int	Get_Height(void);
		int	Get_Width(void);
		int	Get_XAdd(void);
		int	Get_XPos(void);
		int	Get_YPos(void);
		int	Get_Pitch(void);
		inline bool	Get_IsDirectDraw(void);
		GraphicBufferClass	*Get_Graphic_Buffer(void);

		/*===================================================================*/
		/* Define a function which allows us to change a video viewport on	*/
		/*		the fly.																			*/
		/*===================================================================*/
		bool Change(int x, int y, int w, int h);

		/*===================================================================*/
		/* Define the set of common graphic functions that are supported by	*/
		/*		both Graphic ViewPorts and VideoViewPorts.							*/
		/*===================================================================*/

		void	Put_Pixel(int x, int y, unsigned char color);
		int		Get_Pixel(int x, int y);
		void	Clear(unsigned char color = 0);
		long	To_Buffer(int x, int y, int w, int h, void *buff, long size);
		long	To_Buffer(int x, int y, int w, int h, BufferClass *buff);
		long	To_Buffer(BufferClass *buff);
		int	    Blit(	GraphicViewPortClass& dest, int x_pixel, int y_pixel, int dx_pixel,
						int dy_pixel, int pixel_width, int pixel_height, bool trans = FALSE);
		int	    Blit(	GraphicViewPortClass& dest, int dx, int dy, bool trans = FALSE);
		int	    Blit(	GraphicViewPortClass& dest, bool trans = FALSE);

		bool	Scale(	GraphicViewPortClass &dest, int src_x, int src_y, int dst_x,
							int dst_y, int src_w, int src_h, int dst_w, int dst_h, bool trans = FALSE, char *remap = NULL);
		bool	Scale(	GraphicViewPortClass &dest, int src_x, int src_y, int dst_x,
							int dst_y, int src_w, int src_h, int dst_w, int dst_h, char *remap);
		bool	Scale(	GraphicViewPortClass &dest, bool trans = FALSE, char *remap = NULL);
		bool	Scale(	GraphicViewPortClass &dest, char *remap);

		unsigned long	Print(char const *string, int x_pixel, int y_pixel, int fcolor, int bcolor);
		unsigned long	Print(int num, int x_pixel, int y_pixel, int fcol, int bcol);

		/*===================================================================*/
		/* Define the list of graphic functions which work only with a 		*/
		/*		graphic buffer.																*/
		/*===================================================================*/
		void Draw_Line(int sx, int sy, int dx, int dy, unsigned char color);
		void Draw_Rect(int sx, int sy, int dx, int dy, unsigned char color);
		void Fill_Rect(int sx, int sy, int dx, int dy, unsigned char color);

		void Remap(int sx, int sy, int width, int height, void *remap);
		void Remap(void *remap);

		void Draw_Stamp(void const *icondata, int icon, int x_pixel, int y_pixel, void const *remap, int clip_window);

		//
		// New members to lock and unlock the direct draw video memory
		//
		inline bool 	Lock ();
		inline bool 	Unlock();
		inline int		Get_LockCount();

		/*===================================================================*/
		/* Define functions to attach the viewport to a graphicbuffer			*/
		/*===================================================================*/
		void Attach(GraphicBufferClass *graphic_buff, int x, int y, int w, int h);

	protected:

		/*===================================================================*/
		/* Define the data used by a GraphicViewPortClass							*/
		/*===================================================================*/
		uint8_t *				Offset;			// offset to graphic page
		int						Width;			// width of graphic page
		int						Height;			// height of graphic page
		int						XAdd;			// xadd for graphic page (0)
		int						XPos;			// x offset in relation to graphicbuff
		int						YPos;			// y offset in relation to graphicbuff
		long					Pitch;			//Distance from one line to the next
		GraphicBufferClass		*GraphicBuff;	// related graphic buff
		int						LockCount;		// Count for stacking locks if non-zero the buffer
};

/*=========================================================================*/
/* GraphicBufferClass - A GraphicBuffer refers to an actual instance of an	*/
/*		allocated buffer.  The GraphicBuffer may be drawn to directly 			*/
/*		becuase it inherits a ViewPort which represents its physcial size.	*/
/*																									*/
/*			BYTE	  	*Buffer	-		is the offset to graphic buffer				*/
/*			int	  	Width		-		is the width of graphic buffer				*/
/*			int	  	Height	-		is the height of graphic buffer				*/
/*			int	  	XAdd		-		is the xadd of graphic buffer					*/
/*			int		XPos;		- 		will be 0 because it is graphicbuff			*/
/*			int		YPos;		-		will be 0 because it is graphicbuff			*/
/*			long	Pitch		-		modulo of buffer for reading and writing																						*/
/*			bool	IsDirectDraw - 		flag if its a direct draw surface																						*/
/*=========================================================================*/
class GraphicBufferClass : public GraphicViewPortClass, public BufferClass {

	public:
		GraphicBufferClass(int w, int h, void *buffer, long size);
		GraphicBufferClass(int w, int h, void *buffer = 0);
		GraphicBufferClass(void);
		~GraphicBufferClass();

		void Init(int w, int h, void *buffer, long size, GBC_Enum flags);
		void Un_Init(void);

		bool Lock(void);
		bool Unlock(void);

		void Scale_Rotate(BitmapClass &bmp,TPoint2D const &pt,long scale,unsigned char angle);

		bool Is_Window_Surface() const {return WindowTexture != NULL;}
		void Update_Window_Surface(bool end_frame);
		void Update_Palette(uint8_t *palette);
		const void *Get_Palette() const;

	protected:
		void *WindowTexture = NULL;
		void *PaletteSurface = NULL;
};



inline int GraphicViewPortClass::Get_LockCount(void)
{
	return (LockCount);
}



/***********************************************************************************************
 * GVPC::Get_IsDirectDraw -- provide read access to the IsDirectDraw flag                      *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   IsDirectDraw                                                                      *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    11/29/95 1:02PM ST : Created                                                             *
 *=============================================================================================*/
inline bool GraphicViewPortClass::Get_IsDirectDraw(void)
{
	// this flag is used as "do we need to lock" in a few places
	return GraphicBuff && GraphicBuff->Is_Window_Surface();
}


/***********************************************************************************************
 * GVPC::Lock -- lock the graphics buffer for reading or writing                               *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   TRUE if surface was successfully locked                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09-19-95 12:33pm ST : Created                                                             *
 *   10/09/1995     : Moved actually functionality to GraphicBuffer                            *
 *=============================================================================================*/
inline bool GraphicViewPortClass::Lock(void)
{
	bool lock = GraphicBuff->Lock();
	if ( !lock ) return(FALSE);

	if (this != GraphicBuff) {
		Attach(GraphicBuff, XPos, YPos,  Width, Height);
	}
	return(TRUE);
}

/***********************************************************************************************
 * GVPC::Unlock -- unlock the video buffer                                                     *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   TRUE if surface was successfully unlocked                                         *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09-19-95 02:20pm ST : Created                                                             *
 *   10/09/1995     : Moved actually functionality to GraphicBuffer                            *
 *=============================================================================================*/
inline bool GraphicViewPortClass::Unlock(void)
{
	bool unlock = GraphicBuff->Unlock();
	if (!unlock) return(FALSE);

	return(TRUE);
}


/***************************************************************************
 * GVPC::GET_OFFSET -- Get offset for virtual view port class instance     *
 *                                                                         *
 * INPUT:		none                                                        *
 *                                                                         *
 * OUTPUT:     long the offset for the virtual viewport instance           *
 *                                                                         *
 * HISTORY:                                                                *
 *   06/07/1994 PWG : Created.                                             *
 *=========================================================================*/
inline uint8_t * GraphicViewPortClass::Get_Offset(void)
{
	return(Offset);
}

/***************************************************************************
 * GVPC::GET_HEIGHT -- Gets the height of a virtual viewport instance      *
 *                                                                         *
 * INPUT:		none                                                        *
 *                                                                         *
 * OUTPUT:     WORD the height of the virtual viewport instance            *
 *                                                                         *
 * HISTORY:                                                                *
 *   06/07/1994 PWG : Created.                                             *
 *=========================================================================*/
inline int GraphicViewPortClass::Get_Height(void)
{
	return(Height);
}

/***************************************************************************
 * GVPC::GET_WIDTH -- Get the width of a virtual viewport instance			*
 *                                                                         *
 * INPUT:		none                                                        *
 *                                                                         *
 * OUTPUT:     WORD the width of the virtual viewport instance             *
 *                                                                         *
 * HISTORY:                                                                *
 *   06/07/1994 PWG : Created.                                             *
 *=========================================================================*/
inline int GraphicViewPortClass::Get_Width(void)
{
	return(Width);
}


/***************************************************************************
 * GVPC::GET_XADD -- Get the X add offset for virtual viewport instance    *
 *                                                                         *
 * INPUT:		none                                                        *
 *                                                                         *
 * OUTPUT:     WORD the xadd for a virtual viewport instance               *
 *                                                                         *
 * HISTORY:                                                                *
 *   06/07/1994 PWG : Created.                                             *
 *=========================================================================*/
inline int GraphicViewPortClass::Get_XAdd(void)
{
	return(XAdd);
}
/***************************************************************************
 * GVPC::GET_XPOS -- Get the x pos of the VP on the Video                  *
 *                                                                         *
 * INPUT:		none                                                        *
 *                                                                         *
 * OUTPUT:     WORD the x offset to VideoBufferClass								*
 *                                                                         *
 * HISTORY:                                                                *
 *   08/22/1994 SKB : Created.                                             *
 *=========================================================================*/
inline int GraphicViewPortClass::Get_XPos(void)
{
	return(XPos);
}


/***************************************************************************
 * GVPC::GET_YPOS -- Get the y pos of the VP on the video                  *
 *                                                                         *
 * INPUT:		none                                                        *
 *                                                                         *
 * OUTPUT:     WORD the x offset to VideoBufferClass								*
 *                                                                         *
 * WARNINGS:                                                               *
 *                                                                         *
 * HISTORY:                                                                *
 *   08/22/1994 SKB : Created.                                             *
 *=========================================================================*/
inline int GraphicViewPortClass::Get_YPos(void)
{
	return(YPos);
}

/***************************************************************************
 * GVPC::GET_GRAPHIC_BUFFER -- Get the graphic buffer of the VP.            *
 *                                                                         *
 * INPUT:                                                                  *
 *                                                                         *
 * OUTPUT:                                                                 *
 *                                                                         *
 * HISTORY:                                                                *
 *   08/22/1994 SKB : Created.                                             *
 *=========================================================================*/
inline GraphicBufferClass *GraphicViewPortClass::Get_Graphic_Buffer(void)
{
	return (GraphicBuff);
}

inline void	GraphicViewPortClass::Put_Pixel(int x, int y, unsigned char color)
{
	if (Lock()){
		Buffer_Put_Pixel(this, x, y, color);
	}
	Unlock();
}

inline int	GraphicViewPortClass::Get_Pixel(int x, int y)
{
	int		return_code=0;

	if (Lock()){
		return_code=(Buffer_Get_Pixel(this, x, y));
	}
	Unlock();
	return(return_code);
}

inline void	GraphicViewPortClass::Clear(unsigned char color)
{
	if (Lock()){
		Buffer_Clear(this, color);
	}
	Unlock();
}

inline long	GraphicViewPortClass::To_Buffer(int x, int y, int w, int h, void *buff, long size)
{
	long	return_code=0;
	if (Lock()){
		return_code = (Buffer_To_Buffer(this, x, y, w, h, buff, size));
	}
	Unlock();
	return ( return_code );
}

inline long	GraphicViewPortClass::To_Buffer(int x, int y, int w, int h, BufferClass *buff)
{
	return To_Buffer(x, y, w, h, buff->Get_Buffer(), buff->Get_Size());
}

inline long	GraphicViewPortClass::To_Buffer(BufferClass *buff)
{
	return To_Buffer(0, 0, Width, Height, buff->Get_Buffer(), buff->Get_Size());
}

inline int	GraphicViewPortClass::Blit(	GraphicViewPortClass& dest, int x_pixel, int y_pixel, int dx_pixel,
				int dy_pixel, int pixel_width, int pixel_height, bool trans)
{
	int		return_code=0;

	if (Lock()){
		if (dest.Lock()){
			return_code=(Linear_Blit_To_Linear(this, &dest, x_pixel, y_pixel
													, dx_pixel, dy_pixel
													, pixel_width, pixel_height, trans));
		}
		dest.Unlock();
	}
	Unlock();

	return ( return_code );
}

inline int	GraphicViewPortClass::Blit(	GraphicViewPortClass& dest, int dx, int dy, bool trans)
{
	return Blit(dest, 0, 0, dx, dy, Width, Height, trans);
}

inline int	GraphicViewPortClass::Blit(	GraphicViewPortClass& dest, bool trans)
{
	return Blit(dest, 0, 0, 0, 0, Width, Height, trans);

}

inline bool	GraphicViewPortClass::Scale(	GraphicViewPortClass &dest, int src_x, int src_y, int dst_x,
					int dst_y, int src_w, int src_h, int dst_w, int dst_h, bool trans, char *remap)
{
	bool	return_code=0;
	if (Lock()){
		if (dest.Lock()){
			return_code = (Linear_Scale_To_Linear(this, &dest, src_x, src_y, dst_x, dst_y, src_w, src_h, dst_w, dst_h, trans, remap));
		}
		dest.Unlock();
	}
	Unlock();
	return ( return_code );
}

inline bool	GraphicViewPortClass::Scale(	GraphicViewPortClass &dest, int src_x, int src_y, int dst_x,
					int dst_y, int src_w, int src_h, int dst_w, int dst_h, char *remap)
{
	return Scale(dest, src_x, src_y, dst_x, dst_y, src_w, src_h, dst_w, dst_h, FALSE, remap);
}

inline bool	GraphicViewPortClass::Scale(	GraphicViewPortClass &dest, bool trans, char *remap)
{
	return Scale(dest, 0, 0, 0, 0, Width, Height, dest.Get_Width(), dest.Get_Height(), trans, remap);
}

inline bool	GraphicViewPortClass::Scale(	GraphicViewPortClass &dest, char *remap)
{
	return Scale(dest, 0, 0, 0, 0, Width, Height, dest.Get_Width(), dest.Get_Height(), FALSE, remap);
}

inline unsigned long	GraphicViewPortClass::Print(char const *str, int x, int y, int fcol, int bcol)
{
	unsigned long	return_code=0;
	if (Lock()){
		return_code = (Buffer_Print(this, str, x, y, fcol, bcol));
	}
	Unlock();
	return ( return_code );
}

inline unsigned long	GraphicViewPortClass::Print(int num, int x, int y, int fcol, int bcol)
{
	char str[17];

	unsigned long	return_code=0;
	if (Lock()){
		snprintf(str, sizeof(str), "%i", num);
		return_code = (Buffer_Print(this, str, x, y, fcol, bcol));
	}
	Unlock();
	return ( return_code );
}

inline void GraphicViewPortClass::Draw_Stamp(void const * icondata, int icon, int x_pixel, int y_pixel, void const * remap, int clip_window)
{
	if (Lock()){
		Buffer_Draw_Stamp_Clip(this, icondata, icon, x_pixel, y_pixel, remap, WindowList[clip_window][WINDOWX], WindowList[clip_window][WINDOWY], WindowList[clip_window][WINDOWWIDTH], WindowList[clip_window][WINDOWHEIGHT]);
	}
	Unlock();
}

inline void GraphicViewPortClass::Draw_Line(int sx, int sy, int dx, int dy, unsigned char color)
{
	if (Lock()){
		Buffer_Draw_Line(this, sx, sy, dx, dy, color);
	}
	Unlock();
}

inline void GraphicViewPortClass::Fill_Rect(int sx, int sy, int dx, int dy, unsigned char color)
{
	if (Lock()){
		Buffer_Fill_Rect(this, sx, sy, dx, dy, color);
		Unlock();
	}
}

inline void GraphicViewPortClass::Remap(int sx, int sy, int width, int height, void *remap)
{
	if (Lock()){
		Buffer_Remap(this, sx, sy, width, height, remap);
	}
	Unlock();
}

inline void GraphicViewPortClass::Remap(void *remap)
{
	return Remap(0, 0, Width, Height, remap);
}

inline int GraphicViewPortClass::Get_Pitch(void)
{
	return(Pitch);
}
/*=========================================================================*/
/* The following BufferClass functions are defined here because they act	*/
/*		on graphic viewports.																*/
/*=========================================================================*/


/***************************************************************************
 * BUFFER_TO_PAGE -- Generic 'c' callable form of Buffer_To_Page           *
 *                                                                         *
 * INPUT: 																						*
 *                                                                         *
 * OUTPUT:                                                                 *
 *                                                                         *
 * WARNINGS:                                                               *
 *                                                                         *
 * HISTORY:                                                                *
 *   01/12/1995 PWG : Created.                                             *
 *=========================================================================*/
inline long Buffer_To_Page(int x, int y, int w, int h, void *Buffer, GraphicViewPortClass &view)
{
	long	return_code=0;
	if (view.Lock()){
		return_code = (Buffer_To_Page(x, y, w, h, Buffer, &view));
	}
	view.Unlock();
	return ( return_code );
}

/***************************************************************************
 * BC::TO_PAGE -- Copys a buffer class to a page with definable w, h 		*
 *                                                                         *
 * INPUT:		int	width		- the width of copy region							*
 *					int	height	- the height of copy region						*
 *					GVPC&	dest		- virtual viewport to copy to						*
 *                                                                         *
 * OUTPUT:		none                                                        *
 *																									*
 * WARNINGS:	x and y position are the upper left corner of the dest		*
 *						viewport																	*
 *                                                                         *
 * HISTORY:                                                                *
 *   07/01/1994 PWG : Created.                                             *
 *=========================================================================*/
inline long BufferClass::To_Page(int w, int h, GraphicViewPortClass &view)
{
	return To_Page(0, 0, w, h, view);
}
/***************************************************************************
 * BC::TO_PAGE -- Copys a buffer class to a page with definable w, h 		*
 *                                                                         *
 * INPUT:		GVPC&	dest		- virtual viewport to copy to						*
 *                                                                         *
 * OUTPUT:		none                                                        *
 *																									*
 * WARNINGS:	x and y position are the upper left corner of the dest		*
 *						viewport.  width and height are assumed to be the			*
 *						viewport's width and height.										*
 *                                                                         *
 * HISTORY:                                                                *
 *   07/01/1994 PWG : Created.                                             *
 *=========================================================================*/
inline long BufferClass::To_Page(GraphicViewPortClass &view)
{
	return To_Page(0, 0, view.Get_Width(), view.Get_Height(), view);
}
/***************************************************************************
 * BC::TO_PAGE -- Copys a buffer class to a page with definable x, y, w, h *
 *                                                                         *
 * INPUT:	int	x			- x pixel on viewport to copy from					*
 *				int	y			- y pixel on viewport to copy from					*
 *				int	width		- the width of copy region								*
 *				int	height	- the height of copy region							*
 *				GVPC&	dest		- virtual viewport to copy to							*
 *                                                                         *
 * OUTPUT:	none                                                           *
 *                                                                         *
 * HISTORY:                                                                *
 *   07/01/1994 PWG : Created.                                             *
 *=========================================================================*/
inline long BufferClass::To_Page(int x, int y, int w, int h, GraphicViewPortClass &view)
{
	long	return_code=0;
	if (view.Lock()){
		return_code = (Buffer_To_Page(x, y, w, h, Buffer, &view));
	}
	view.Unlock();
	return ( return_code );
}


#endif

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

/***********************************************************************************************
 ***             C O N F I D E N T I A L  ---  W E S T W O O D   S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Drawbuff - Westwood win95 library                            *
 *                                                                                             *
 *                    File Name : Iconcach.H                                                   *
 *                                                                                             *
 *                   Programmer : Steve Tall                                                   *
 *                                                                                             *
 *                   Start Date : November 8th, 1995                                           *
 *                                                                                             *
 *                  Last Update : November 16th, 1995 [ST]                                     *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Overview: This file cantains definition of the IconCacheClass and associated non member     *
 *           function prototypes.                                                              *
 *                                                                                             *
 * Functions:                                                                                  *
 *  IconCacheClass::Get_Is_Cached -- member to allow access to private IsCached flag           *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#ifndef	ICONCACH_H
#define	ICONCACH_H

#include "tile.h"

#define	ICON_WIDTH			24			// Icons must be this width to be cached
#define	ICON_HEIGHT			24			// Icons must be this height to be cached
#define	MAX_CACHED_ICONS	500		// Maximum number of icons that can be cached
#define	MAX_ICON_SETS		100		// Maximum number of icon sets that can be registered
#define	MAX_LOOKUP_ENTRIES 3000		// Size of icon index table

/*
** Structure to keep track of registered icon sets
**
*/

typedef struct tIconSetType{
	IControl_Type	*IconSetPtr;				// Ptr to icon set data
	int				IconListOffset;			// Offset into icon index table for this icon set
}IconSetType;


extern void Restore_Cached_Icons (void);
extern void Register_Icon_Set (void *icon_data , bool pre_cache);

#endif	//ICONCACH_H


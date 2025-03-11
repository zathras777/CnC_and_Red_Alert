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
 *                 Project Name : Library - Filio header stuff.            *
 *                                                                         *
 *                    File Name : FILE.H                                 	*
 *                                                                         *
 *                   Programmer : Scott K. Bowen                           *
 *                                                                         *
 *                   Start Date : September 13, 1993                       *
 *                                                                         *
 *                  Last Update : April 11, 1994									*
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef FILE_H
#define FILE_H

#include <time.h>

/*=========================================================================*/
/* File IO system defines and enumerations											*/
/*=========================================================================*/

/*
**	These are the Open_File, Read_File, and Seek_File constants.
*/
#ifndef READ
#define READ						1	// Read access.
#endif
#ifndef WRITE
#define WRITE						2	// Write access.
#endif
#ifndef SEEK_SET
#define SEEK_SET					0	// Seek from start of file.
#define SEEK_CUR					1	// Seek relative from current location.
#define SEEK_END					2	// Seek from end of file.
#endif


// These are actually implemented in the game, but used by audio and WSA
int Open_File(char const *file_name, int mode);
void Close_File(int handle);
long Read_File(int handle, void *buf, unsigned long bytes);
long Write_File(int handle, void const *buf, unsigned long bytes);
unsigned long Seek_File(int handle, long offset, int starting);


// file searching
struct FindFileState
{
    const char *name;
    time_t mod_time;

    // internal state
    void *data;
    int off;
};

bool Find_First_File(const char *path_glob, FindFileState &state);
bool Find_Next_File(FindFileState &state);
// to clean up if not finishing the search
void End_Find_File(FindFileState &state);

#endif

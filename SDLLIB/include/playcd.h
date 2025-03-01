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
 *                 Project Name : WWLIB	  											*
 *                                                                         *
 *                    File Name : PLAYCD.H											*
 *                                                                         *
 *                   Programmer : STEVE WETHERILL									*
 *                                                                         *
 *                   Start Date : 5/13/94												*
 *                                                                         *
 *                  Last Update : June 4, 1994   [SW]                      *
 *                                                                         *
 *-------------------------------------------------------------------------*/

#ifndef PLAYCD_H
#define PLAYCD_H


/***************************************************************************
 * GetCDClass -- object which will return logical CD drive						*
 *                                                                         *
 * HISTORY:                                                                *
 *   06/04/1994 SW : Created.																*
 *=========================================================================*/

#define MAX_CD_DRIVES 26
#define NO_CD_DRIVE -1

class	GetCDClass {

protected:

	int	CDDrives[MAX_CD_DRIVES];	//Array containing CD drive letters
	int	CDCount;							//Number of available CD drives
	int	CDIndex;

public:


	GetCDClass(void);					// This is the default constructor
	~GetCDClass(void);				// This is the destructor

	inline	int	Get_First_CD_Drive(void);
	inline	int	Get_Next_CD_Drive(void);
	inline	int	Get_Number_Of_Drives(void) {return (CDCount);};

};



/***********************************************************************************************
 * GCDC::Get_Next_CD_Drive -- return the logical drive number of the next CD drive             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Logical drive number of a cd drive or -1 if none                                  *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    5/21/96 3:50PM ST : Created                                                              *
 *=============================================================================================*/
inline int GetCDClass::Get_Next_CD_Drive(void)
{
	if (CDCount){
		if (CDIndex == CDCount) CDIndex = 0;
		return (CDDrives[CDIndex++]);
	}else{
		return (-1);
	}
}



/***************************************************************************
 * GCDC::Get_First_CD_Drive -- return the number of the first CD drive     *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * INPUT:                                                                  *
 *			none																				  *
 * OUTPUT:                                                                 *
 *			logical drive number 														  *
 * WARNINGS:                                                               *
 *                                                                         *
 * HISTORY:                                                                *
 *   05/26/1994 SW : Created.                                              *
 *   12/4/95    ST : fixed for Win95                                       *
 *=========================================================================*/
inline int GetCDClass::Get_First_CD_Drive(void)
{
	CDIndex = 0;
	return (Get_Next_CD_Drive());
}




/***************************** End of Playcd.h ****************************/

#endif // PLAYCD_H


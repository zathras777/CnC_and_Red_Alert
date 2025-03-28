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

/* $Header: /CounterStrike/CONTROL.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : CONTROL.H                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 01/15/95                                                     *
 *                                                                                             *
 *                  Last Update : January 15, 1995 [JLB]                                       *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef CONTROL_H
#define CONTROL_H

#include	"gadget.h"

/***************************************************************************
 * ControlClass -- Region tracking class									         *
 *                                                                         *
 * INPUT:      int x -- x position of gadget											*
 *					int y -- y position of gadget											*
 *					int w -- width of gadget												*
 *					int h -- height of gadget												*
 *					UWORD flags -- see enumeration choices								*
 *                                                                         *
 * OUTPUT:     0 = new scenario created, -1 = not									*
 * WARNINGS:	This class is Abstract (cannot make an instance of it)      *
 *                                                                         *
 * HISTORY:                                                                *
 *   01/03/1995 MML : Created.                                             *
 *=========================================================================*/
class ControlClass : public GadgetClass
{
	public:
		ControlClass(NoInitClass const & x) : GadgetClass(x) {};
		ControlClass(unsigned id, int x, int y, int w, int h, unsigned flags=LEFTPRESS|RIGHTPRESS, int sticky=false);
		ControlClass(ControlClass const & control);

		virtual void Make_Peer(GadgetClass & gadget);

		/*
		**	Render support function.
		*/
		virtual int Draw_Me(int forced=false);

		/*
		**	This is the ID number for this control gadget. This number is used to generate
		**	a special pseudo-key when the gadget detects valid input.
		*/
		unsigned ID;

	protected:
		virtual unsigned Get_ID(void) const;
		virtual int Action(unsigned flags, KeyNumType & key);

		/*
		**	This points to the peer button to inform when something happens to this
		**	gadget.
		*/
		GadgetClass * Peer;
};

#endif


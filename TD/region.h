/*
**	Command & Conquer(tm)
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

/* $Header:   F:\projects\c&c\vcs\code\region.h_v   2.13   16 Oct 1995 16:45:10   JOE_BOSTIC  $ */
/*********************************************************************************************** 
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Command & Conquer                                            * 
 *                                                                                             * 
 *                    File Name : REGION.H                                                     * 
 *                                                                                             * 
 *                   Programmer : Joe L. Bostic                                                * 
 *                                                                                             * 
 *                   Start Date : 03/09/95                                                     * 
 *                                                                                             * 
 *                  Last Update : March 9, 1995 [JLB]                                          * 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef REGION_H
#define REGION_H


class RegionClass {
	public:
		RegionClass(void) {Threat = 0;};
		~RegionClass(void) {};
		int operator != (RegionClass const & region) {return memcmp(this, &region, sizeof(RegionClass));};
		int operator == (RegionClass const & region) {return !memcmp(this, &region, sizeof(RegionClass));};
		int operator > (RegionClass const & region) {return memcmp(this, &region, sizeof(RegionClass)) > 0;};
		int operator < (RegionClass const & region) {return memcmp(this, &region, sizeof(RegionClass)) < 0;};

		void Reset_Threat(void) {Threat = 0;};
		void Adjust_Threat(int threat, int neg) {if (neg) Threat -= threat; else Threat+= threat;};
		int Threat_Value(void) const {return Threat;};

	protected:
		long  Threat;
};

#endif

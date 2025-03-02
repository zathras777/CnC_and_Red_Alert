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
 **   C O N F I D E N T I A L --- W E S T W O O D    S T U D I O S        **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Command & Conquer                        *
 *                                                                         *
 *                    File Name : IPX95PP                                  *
 *                                                                         *
 *                   Programmer : Steve Tall                               *
 *                                                                         *
 *                   Start Date : January 22nd, 1996                       *
 *                                                                         *
 *                  Last Update : July 10th, 1996   [ST]                   *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Overview:                                                               *
 *                                                                         *
 *  Windows 95 equivelent functions from IPX.CPP                           *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "function.h"


#include "ipx95.h"

bool WindowsNT = false;

IPXInitialiseType				IPX_Initialise;
IPXGetOutstandingBuffer95Type  	IPX_Get_Outstanding_Buffer95;
IPXShutDown95Type              	IPX_Shut_Down95;
IPXSendPacket95Type            	IPX_Send_Packet95;
IPXBroadcastPacket95Type       	IPX_Broadcast_Packet95;
IPXStartListening95Type        	IPX_Start_Listening95;

bool Load_IPX_Dll (void)
{
	return false;
}

void Unload_IPX_Dll (void)
{
}

int IPX_Open_Socket(unsigned short socket)
{
	return 0;
}

int IPX_Close_Socket(unsigned short socket)
{
	return 0;
}

int IPX_Get_Connection_Number(void)
{
	return 0;
}

int IPX_Broadcast_Packet(unsigned char * buf, int buflen)
{
	return 0;
}

int IPX_Get_Local_Target(unsigned char * dest_network, unsigned char * dest_node,
	unsigned short dest_socket, unsigned char * bridge_address)
{
	return 0;
}

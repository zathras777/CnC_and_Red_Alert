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

/* $Header:   F:\projects\c&c\vcs\code\nullconn.h_v   1.12   16 Oct 1995 16:45:54   JOE_BOSTIC  $ */
/***************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D    S T U D I O S        **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Command & Conquer                        *
 *                                                                         *
 *                    File Name : NULLCONN.H                               *
 *                                                                         *
 *                   Programmer : Bill Randolph                            *
 *                                                                         *
 *                   Start Date : December 19, 1994                        *
 *                                                                         *
 *                  Last Update : April 3, 1995   [BR]                 		*
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * This is the Connection Class for a NULL-Modem connection.  It inherits	*
 * a Queue, PacketBuf, timeout variables from ConnectionClass.  It 			*
 * inherits its Send_/Receive_/Get_Packet functions, and the non-sequenced	*
 * ACK/Retry logic in Service_Send_Queue & Service_Recieve_Queue from		*
 * NonSequencedConnClass.																	*
 *                                                                         *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef NULLCONN_H
#define NULLCONN_H


/*
********************************* Includes **********************************
*/
#include "noseqcon.h"
#ifdef PORTABLE
typedef void *HANDLE;
#else
#include "commlib.h"
#endif

/*
********************************** Defines **********************************
*/
#define	PACKET_SERIAL_START				0xDABD
#define	PACKET_SERIAL_VERIFY				0xDEAF

#define	PACKET_SERIAL_OVERHEAD_SIZE	(sizeof( SerialHeaderType ) + sizeof( SerialCRCType ))

typedef struct {
	unsigned short MagicNumber;
	unsigned short Length;
	unsigned short MagicNumber2;
} SerialHeaderType;

typedef struct {
	int SerialCRC;
} SerialCRCType;


/*
***************************** Class Declaration *****************************
*/
class NullModemConnClass : public NonSequencedConnClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Constructor/destructor.
		.....................................................................*/
		NullModemConnClass (int numsend, int numrecieve, int maxlen,
			unsigned short magicnum);
		virtual ~NullModemConnClass ();

		/*.....................................................................
		Initialization.
		.....................................................................*/
		void Init (HANDLE port_handle);

		/*.....................................................................
		Utility routines.
		.....................................................................*/
		unsigned long Actual_Max_Packet (void) { return (MaxPacketLen + (sizeof(SerialHeaderType)) + sizeof(int) + sizeof (char)); }

		/*.....................................................................
		This routine computes a CRC value for the given buffer.
		.....................................................................*/
		static int Compute_CRC(char *buf, int buflen);

		/*.....................................................................
		This routine returns the number of bytes extra added the packet
		for communication.
		.....................................................................*/
		static int Packet_Overhead_Size( void );

	/*
	--------------------------- Private Interface ----------------------------
	*/
	protected:
		/*.....................................................................
		This routine actually performs a hardware-dependent data send.
		.....................................................................*/
		int Send (char *buf, int buflen);

		/*.....................................................................
		This is the PORT value used by the GreenLeaf calls.
		.....................................................................*/
		HANDLE PortHandle;
		//PORT *Port;

		/*.....................................................................
		This buffer is a staging area for data sent out; it includes the
		packet sent by the parent class (which includes the application's
		packet, plus the CommHeaderType header), plus:
		- 2-byte buffer start ID
		- 2-byte length
		- 4-byte CRC value (at the end of the buffer)
		This is the actual packet that gets sent across the serial line.
		.....................................................................*/
		char *SendBuf;
};

#endif

/************************** end of nullconn.h ******************************/


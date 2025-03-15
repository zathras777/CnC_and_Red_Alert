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
 *                 Project Name : Timer Class Functions                    *
 *                                                                         *
 *                    File Name : TIMER.H                                  *
 *                                                                         *
 *                   Programmer : Scott K. Bowen                           *
 *                                                                         *
 *                   Start Date : July 6, 1994                             *
 *                                                                         *
 *                  Last Update : July 12, 1994   [SKB]                    *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/*=========================================================================*/
/* The following prototypes are for the file: TIMERA.ASM							*/
/*=========================================================================*/

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Externs /////////////////////////////////////////////
extern bool 		TimerSystemOn;


/*=========================================================================*/
typedef enum BaseTimerEnum {
	BT_SYSTEM,			// System timer (60 / second).
	BT_USER				// User controllable timer (? / second).
} BaseTimerEnum;

class TimerClass {
 	public:
		// Constructor.  Timers set before low level init has been done will not
		// be able to be 'Started' or 'on' until timer system is in place.
		TimerClass(BaseTimerEnum timer=BT_SYSTEM, bool start=false);

		// No destructor.
		~TimerClass(void){}

		//
		long Set(long value, bool start=true);	// Set initial timer value.
		long Stop(void);				// Pause timer.
		long Start(void);				// Resume timer.
		long Reset(bool start=true);	// Reset timer to zero.
		long Time(void);				// Fetch current timer value.

	protected:
		long Started;					// Time last started (0 == not paused).
		long Accumulated;				//	Total accumulated ticks.

	private:
		BaseTimerEnum	TickType;
		long Get_Ticks (void);
};


inline long TimerClass::Reset(bool start)
{
	return(Set(0, start));
}


class CountDownTimerClass : private TimerClass {
	public:
		// Constructor.  Timers set before low level init has been done will not
		// be able to be 'Started' or 'on' until timer system is in place.
		CountDownTimerClass(BaseTimerEnum timer, long set, bool on=false);
		CountDownTimerClass(BaseTimerEnum timer=BT_SYSTEM, bool on=false);

		// No destructor.
		~CountDownTimerClass(void){}

		// Public functions
		long Set(long set, bool start=true);	// Set count down value.
		long Reset(bool start=true);	// Reset timer to zero.
		long Stop(void);			// Pause timer.
		long Start(void);			// Resume timer.
		long Time(void);			// Fetch current count down value.

	protected:
		long DelayTime;			// Ticks remaining before countdown timer expires.
};

inline long CountDownTimerClass::Stop(void)
{
	TimerClass::Stop();
	return(Time());
}

inline long CountDownTimerClass::Start(void)
{
	TimerClass::Start();
	return(Time());
}

inline long CountDownTimerClass::Reset(bool start)
{
	return (TimerClass::Reset(start));
}
class WinTimerClass {

	public:
		WinTimerClass ( unsigned freq=60 , bool partial=false );
		~WinTimerClass();

		void 		Update_Tick_Count ( void );
		unsigned	Get_System_Tick_Count ( void );
		unsigned	Get_User_Tick_Count ( void );

	private:
		unsigned		TimerHandle;	//Handle for windows timer event
		unsigned		SysTicks;		//Tick count of timer.
		unsigned		UserTicks;		//Tick count of timer.
};


uint32_t Get_Time_Ms();

extern	WinTimerClass	*WindowsTimer;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// externs  //////////////////////////////////////////
#ifdef TD
extern TimerClass					TickCount;
#endif


#endif // TIMER_H


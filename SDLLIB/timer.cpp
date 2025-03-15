#include <stdio.h>
#include <SDL.h>
#include "timer.h"

bool TimerSystemOn = false;

static Uint32 TimerCallback(Uint32 interval, void *param)
{
    ((WinTimerClass *)param)->Update_Tick_Count();

    return interval;
}

TimerClass::TimerClass(BaseTimerEnum timer, bool start) : Accumulated(0), Started(0), TickType(timer)
{
	if(start && TimerSystemOn)
        Start();
}

long TimerClass::Set(long value, bool start)
{
    printf("TimerClass::%s\n", __func__);
    return 0;
}

long TimerClass::Start(void)
{
    if(!Started)
        Started = Get_Ticks() + 1;
    return Time();
}

long TimerClass::Time(void)
{
	if (Started)
    {
		long ticks = Get_Ticks();
		Accumulated += ticks - (Started-1);
		Started = ticks+1;
	}
	return Accumulated;
}

long TimerClass::Get_Ticks(void)
{
    printf("TimerClass::%s\n", __func__);
    return 0;
}

CountDownTimerClass::CountDownTimerClass(BaseTimerEnum timer, long set, bool on) : TimerClass(timer, on)
{
	Set(set, on);
}

CountDownTimerClass::CountDownTimerClass(BaseTimerEnum timer, bool on) : TimerClass(timer, false), DelayTime(0)
{
	if(on)
        Start();
}

long CountDownTimerClass::Set(long set, bool start)
{
    printf("CountDownTimerClass::%s\n", __func__);
    return 0;
}

long CountDownTimerClass::Time(void)
{
    return 0;
}

WinTimerClass::WinTimerClass(unsigned freq, bool partial)
{
    SDL_Init(SDL_INIT_TIMER);
    TimerHandle = SDL_AddTimer(1000 / freq, TimerCallback, this);

    // TickCount is a completely different type to TimerClass (TTimerClass<SystemTimerClass>)
    //if(!partial)
    //    TickCount.Start();
}

WinTimerClass::~WinTimerClass()
{
    SDL_RemoveTimer(TimerHandle);
}

void WinTimerClass::Update_Tick_Count(void)
{
    SysTicks++;
    UserTicks++;
}

unsigned WinTimerClass::Get_System_Tick_Count(void)
{
    return SysTicks;
}

uint32_t Get_Time_Ms()
{
    return SDL_GetTicks();
}
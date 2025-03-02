#include <stdio.h>
#include "timer.h"

bool TimerSystemOn = false;

TimerClass::TimerClass(BaseTimerEnum timer, bool start)
{

}

long TimerClass::Set(long value, bool start)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

long TimerClass::Time(void)
{
    return 0;
}

CountDownTimerClass::CountDownTimerClass(BaseTimerEnum timer, bool on) : TimerClass(timer, on)
{

}

long CountDownTimerClass::Set(long set, bool start)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

long CountDownTimerClass::Time(void)
{
    return 0;
}

WinTimerClass::~WinTimerClass()
{

}

unsigned WinTimerClass::Get_System_Tick_Count(void)
{
    return 0;
}
#include <string.h>

#include "keyboard.h"
#include "ww_win.h"

WWKeyboardClass::WWKeyboardClass() : MouseQX(0), MouseQY(0), Head(0), Tail(0), MState(0), Conditional(0)
{
    // clear buffer
    memset(Buffer, 0, 256);
}

bool WWKeyboardClass::Check(void)
{
    // poll for events, return key if any pressed
    SDL_Event_Loop();

    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

int WWKeyboardClass::Get(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

int WWKeyboardClass::To_ASCII(int num)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void WWKeyboardClass::Clear(void)
{
    Head = Tail;
}

int WWKeyboardClass::Down(int key)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}
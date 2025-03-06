#include <SDL.h>

#include "mouse.h"

extern void *MainWindow;

static WWMouseClass *_Mouse = NULL;

WWMouseClass::WWMouseClass(GraphicViewPortClass *scr, int mouse_max_width, int mouse_max_height) : State(0)
{
    Set_Cursor_Clip();
    _Mouse = this;
}

WWMouseClass::~WWMouseClass()
{
    Clear_Cursor_Clip();
}

void *WWMouseClass::Set_Cursor(int xhotspot, int yhotspot, void *cursor)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

void WWMouseClass::Hide_Mouse(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WWMouseClass::Show_Mouse(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WWMouseClass::Conditional_Hide_Mouse(int x1, int y1, int x2, int y2)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WWMouseClass::Conditional_Show_Mouse(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int WWMouseClass::Get_Mouse_State(void)
{
    return State;
}

int WWMouseClass::Get_Mouse_X(void)
{
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

int WWMouseClass::Get_Mouse_Y(void)
{
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

void WWMouseClass::Draw_Mouse(GraphicViewPortClass *scr)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WWMouseClass::Erase_Mouse(GraphicViewPortClass *scr, bool forced)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WWMouseClass::Set_Cursor_Clip(void)
{
    SDL_SetWindowGrab((SDL_Window *)MainWindow, SDL_TRUE);
}

void WWMouseClass::Clear_Cursor_Clip(void)
{
    SDL_SetWindowGrab((SDL_Window *)MainWindow, SDL_FALSE);
}

void Hide_Mouse(void)
{
    if(_Mouse)
       _Mouse->Hide_Mouse();
}

void Show_Mouse(void)
{
    if(_Mouse)
       _Mouse->Show_Mouse();
}

void Conditional_Hide_Mouse(int x1, int y1, int x2, int y2)
{
    if(_Mouse)
       _Mouse->Conditional_Hide_Mouse(x1, y1, x2, y2);
}

void Conditional_Show_Mouse(void)
{
    if(_Mouse)
       _Mouse->Conditional_Show_Mouse();
}

int Get_Mouse_State(void)
{
    if(_Mouse)
        return _Mouse->Get_Mouse_State();
    return 0;
}

void *Set_Mouse_Cursor(int hotx, int hoty, void *cursor)
{
    if(_Mouse)
        return _Mouse->Set_Cursor(hotx, hoty, cursor);
    return 0;
}

int Get_Mouse_X(void)
{
    if(_Mouse)
        return _Mouse->Get_Mouse_X();
    return 0;
}

int Get_Mouse_Y(void)
{
    if(_Mouse)
        return _Mouse->Get_Mouse_Y();
    return 0;
}

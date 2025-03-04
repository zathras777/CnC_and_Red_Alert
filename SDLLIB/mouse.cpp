#include <SDL.h>

#include "mouse.h"

WWMouseClass::WWMouseClass(GraphicViewPortClass *scr, int mouse_max_width, int mouse_max_height)
{

}

WWMouseClass::~WWMouseClass()
{

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
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WWMouseClass::Clear_Cursor_Clip(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}


void Hide_Mouse(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Show_Mouse(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Conditional_Hide_Mouse(int x1, int y1, int x2, int y2)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Conditional_Show_Mouse(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int Get_Mouse_State(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void *Set_Mouse_Cursor(int hotx, int hoty, void *cursor)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

int Get_Mouse_X(void)
{
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

int Get_Mouse_Y(void)
{
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

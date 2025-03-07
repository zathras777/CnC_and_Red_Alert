#include <SDL.h>

#include "mouse.h"
#include "iff.h"
#include "shape.h"

extern void *MainWindow;

static WWMouseClass *_Mouse = NULL;

WWMouseClass::WWMouseClass(GraphicViewPortClass *scr, int mouse_max_width, int mouse_max_height) : MaxWidth(mouse_max_width), MaxHeight(mouse_max_width), State(0)
{
    Set_Cursor_Clip();
    _Mouse = this;

    MouseCursor = new uint8_t[MaxWidth * MaxHeight];
}

WWMouseClass::~WWMouseClass()
{
    Clear_Cursor_Clip();

    delete[] MouseCursor;
}

void *WWMouseClass::Set_Cursor(int xhotspot, int yhotspot, void *cursor)
{
    if(!cursor || PrevCursor == cursor)
        return cursor;


    auto cursor_shape = (Shape_Type *)cursor;

    int datasize = cursor_shape->DataLength;

    if(cursor_shape->Width > MaxWidth || cursor_shape->OriginalHeight > MaxHeight)
        return PrevCursor;

    // don't handle 16-color or uncompressed
    if(cursor_shape->ShapeType != 0)
    {
        printf("Set_Cursor type %i\n", cursor_shape->ShapeType);
        return PrevCursor;
    }

    // decompress it
    auto decompressed_data = new uint8_t[cursor_shape->DataLength];
    LCW_Uncompress((uint8_t *)cursor + 10, decompressed_data, cursor_shape->DataLength);

    // now we have an uncmpressed, but still encoded shape
    auto inptr = decompressed_data;

    int remaining = cursor_shape->Width * cursor_shape->OriginalHeight;
    auto outptr = MouseCursor;

    do
    {
        uint8_t pixel = *inptr++;
        if(pixel)
        {
            *outptr++ = pixel;
            remaining--;
        }
        else
        {
            // run of zeros
            int count = *inptr++;
            remaining -= count;
            while(count--)
            {
                *outptr++ = 0;
            }
        }
    }
    while(remaining);

    delete[] decompressed_data;

    // convert to SDL cursor
    // need to store this surf and update the cursor when the palette changes...
    auto sdl_surf = SDL_CreateRGBSurfaceFrom(MouseCursor, cursor_shape->Width, cursor_shape->OriginalHeight, 8, cursor_shape->Width, 0, 0, 0, 0);

    if(WindowBuffer)
    {
        // copy palette from window surface, but make index 0 transparent
        auto window_pal = (const SDL_Palette *)WindowBuffer->Get_Palette();
        SDL_SetPaletteColors(sdl_surf->format->palette, window_pal->colors + 1, 1, 255);
        sdl_surf->format->palette->colors[0].a = 0;
    }

    auto sdl_cursor = SDL_CreateColorCursor(sdl_surf, xhotspot, yhotspot);

    // set it and clean up
    auto old_cursor = PrevCursor;
    SDL_SetCursor(sdl_cursor);

    if(SDLCursor)
        SDL_FreeCursor((SDL_Cursor *)SDLCursor);

    if(SDLSurface)
        SDL_FreeSurface((SDL_Surface *)SDLSurface);

    PrevCursor = (char *)cursor;
    SDLCursor = sdl_cursor;
    SDLSurface = sdl_surf;
    MouseXHot = xhotspot;
    MouseYHot = yhotspot;
    return old_cursor;
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
    // we're using a "hardware" cursor, so don't need to do anything
}

void WWMouseClass::Erase_Mouse(GraphicViewPortClass *scr, bool forced)
{

}

void WWMouseClass::Set_Cursor_Clip(void)
{
    SDL_SetWindowGrab((SDL_Window *)MainWindow, SDL_TRUE);
}

void WWMouseClass::Clear_Cursor_Clip(void)
{
    SDL_SetWindowGrab((SDL_Window *)MainWindow, SDL_FALSE);
}

void WWMouseClass::Update_Palette()
{
    if(!WindowBuffer | !SDLSurface)
        return;

    auto sdl_surf = (SDL_Surface *)SDLSurface;

    // copy palette from window surface
    auto window_pal = (const SDL_Palette *)WindowBuffer->Get_Palette();
    SDL_SetPaletteColors(sdl_surf->format->palette, window_pal->colors + 1, 1, 255);

    // recreate and set cursor
    auto sdl_cursor = SDL_CreateColorCursor(sdl_surf, MouseXHot, MouseYHot);
    SDL_SetCursor(sdl_cursor);

    // clean up old cursor
    if(SDLCursor)
        SDL_FreeCursor((SDL_Cursor *)SDLCursor);
    SDLCursor = sdl_cursor;
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

void Update_Mouse_Palette()
{
    if(_Mouse)
        _Mouse->Update_Palette();
}
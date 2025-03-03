#include <algorithm>

#include <SDL.h>

#include "drawbuff.h"
#include "gbuffer.h"

LPDIRECTDRAW DirectDrawObject;
LPDIRECTDRAWPALETTE	PalettePtr;

void *MainWindow;

GraphicViewPortClass *LogicPage;
bool AllowHardwareBlitFills = true;
bool OverlappedVideoBlits = false;


void Buffer_Put_Pixel(void * thisptr, int x, int y, unsigned char color)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int	Buffer_Get_Pixel(void * thisptr, int x, int y)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void Buffer_Clear(void *thisptr, unsigned char color)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

long Buffer_To_Buffer(void *thisptr, int x, int y, int w, int h, void *buff, long size)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

long Buffer_To_Page(int x, int y, int w, int h, void *Buffer, void *view)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

bool Linear_Blit_To_Linear(void *thisptr, void * dest, int x_pixel, int y_pixel, int dx_pixel,
    int dy_pixel, int pixel_width, int pixel_height, bool trans)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

bool Linear_Scale_To_Linear(void *, void *, int, int, int, int, int, int, int, int, bool, char *)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

long Buffer_Print(void *thisptr, const char *str, int x, int y, int fcolor, int bcolor)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void Buffer_Draw_Line(void *thisptr, int sx, int sy, int dx, int dy, unsigned char color)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Buffer_Fill_Rect(void *thisptr, int sx, int sy, int dx, int dy, unsigned char color)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Buffer_Remap(void * thisptr, int sx, int sy, int width, int height, void *remap)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Buffer_Draw_Stamp_Clip(void const *thisptr, void const *icondata, int icon, int x_pixel, int y_pixel, void const *remap, int ,int,int,int)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

GraphicViewPortClass *Set_Logic_Page(GraphicViewPortClass *ptr)
{
    std::swap(LogicPage, ptr);
    return ptr;
}

GraphicViewPortClass *Set_Logic_Page(GraphicViewPortClass &ptr)
{
    return Set_Logic_Page(&ptr);
}

GraphicViewPortClass::GraphicViewPortClass(GraphicBufferClass* graphic_buff, int x, int y, int w, int h)
{
    Attach(graphic_buff, x, y, w, h);
}

GraphicViewPortClass::GraphicViewPortClass()
{

}

GraphicViewPortClass::~GraphicViewPortClass()
{

}

void GraphicViewPortClass::Draw_Rect(int sx, int sy, int dx, int dy, unsigned char color)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void GraphicViewPortClass::Attach(GraphicBufferClass *graphic_buff, int x, int y, int w, int h)
{
	if (this == Get_Graphic_Buffer()) 
		return;

    // clamp bounds
	if (x < 0)
		x = 0;
	if (x >= graphic_buff->Get_Width())
		x = graphic_buff->Get_Width() - 1;
	if (y < 0)
		y = 0;
	if (y >= graphic_buff->Get_Height()) 
		y = graphic_buff->Get_Height() - 1;

	if (x + w > graphic_buff->Get_Width()) 
		w = graphic_buff->Get_Width() - x;

	if (y + h > graphic_buff->Get_Height())
		h = graphic_buff->Get_Height() - y;

	/*======================================================================*/
	/* Get a pointer to the top left edge of the buffer.					*/
	/*======================================================================*/
 	Offset 		= graphic_buff->Get_Offset() + ((graphic_buff->Get_Width() + graphic_buff->Get_Pitch()) * y) + x;

	/*======================================================================*/
	/* Copy over all of the variables that we need to store.						*/
	/*======================================================================*/
 	XPos			= x;
 	YPos			= y;
 	XAdd			= graphic_buff->Get_Width() - w;
 	Width			= w;
 	Height		    = h;
	Pitch			= graphic_buff->Get_Pitch();
 	GraphicBuff     = graphic_buff;
}


GraphicBufferClass::GraphicBufferClass(int w, int h, void *buffer, long size) : GraphicBufferClass()
{
    Init(w, h, buffer, size, GBC_NONE);
}

GraphicBufferClass::GraphicBufferClass(int w, int h, void *buffer) : GraphicBufferClass(w, h, buffer, w * h)
{
}

GraphicBufferClass::GraphicBufferClass(void)
{
    GraphicBuff = this;
}

GraphicBufferClass::~GraphicBufferClass()
{
    Un_Init();
}

void GraphicBufferClass::Init(int w, int h, void *buffer, long size, GBC_Enum flags)
{
    Size = size;
    Width = w;
    Height = h;
    Pitch = 0;
    XAdd = 0;
    XPos = YPos = 0;

    if(flags & GBC_VISIBLE) {
        WindowSurface = SDL_GetWindowSurface((SDL_Window *)MainWindow);
        // this won't be a paletted surface
    } else {
        // regular allocation
        Allocated = !buffer;
        Buffer = buffer;

        if(!Buffer)
            Buffer = new uint8_t[Size];
    }
}

void GraphicBufferClass::Un_Init(void)
{
    // de-alloc surface
}

void GraphicBufferClass::Attach_DD_Surface (GraphicBufferClass * attach_buffer)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

bool GraphicBufferClass::Lock(void)
{
    // lock surface
    return true;
}

bool GraphicBufferClass::Unlock(void)
{
    // unlock surface
    return true;
}

void GraphicBufferClass::Update_Window_Surface()
{
    // convert from paletted...

    SDL_UpdateWindowSurface((SDL_Window*)MainWindow);

    // update the event loop here too for now
    SDL_Event_Loop();
}

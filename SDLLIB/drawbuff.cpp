#include <algorithm>

#include "drawbuff.h"
#include "gbuffer.h"

LPDIRECTDRAW DirectDrawObject;
LPDIRECTDRAWPALETTE	PalettePtr;

HWND MainWindow;

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
}

void Buffer_Clear(void *thisptr, unsigned char color)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

long Buffer_To_Buffer(void *thisptr, int x, int y, int w, int h, void *buff, long size)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

long Buffer_To_Page(int x, int y, int w, int h, void *Buffer, void *view)
{
    printf("%s\n", __PRETTY_FUNCTION__);
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
    printf("%s\n", __PRETTY_FUNCTION__);
}


GraphicBufferClass::GraphicBufferClass(int w, int h, void *buffer, long size)
{

}
GraphicBufferClass::GraphicBufferClass(int w, int h, void *buffer)
{

}
GraphicBufferClass::GraphicBufferClass(void)
{

}
GraphicBufferClass::~GraphicBufferClass()
{

}

void GraphicBufferClass::Init(int w, int h, void *buffer, long size, GBC_Enum flags)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void GraphicBufferClass::Un_Init(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void GraphicBufferClass::Attach_DD_Surface (GraphicBufferClass * attach_buffer)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

bool GraphicBufferClass::Lock(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

bool GraphicBufferClass::Unlock(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

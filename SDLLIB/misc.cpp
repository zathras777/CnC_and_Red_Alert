#include <stddef.h>
#include <stdio.h>

#include "ddraw.h" //!

#include "misc.h"

LPDIRECTDRAWSURFACE	PaletteSurface;

SurfaceMonitorClass	AllSurfaces;

long RandNumb;

void (*Misc_Focus_Loss_Function)(void);
void (*Misc_Focus_Restore_Function)(void);

bool Set_Video_Mode(HWND hwnd, int w, int h, int bits_per_pixel)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

unsigned Get_Free_Video_Memory(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 64 * 1024 * 1024;
}

void Wait_Blit(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

unsigned Get_Video_Hardware_Capabilities(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

SurfaceMonitorClass::SurfaceMonitorClass()
{

}

void SurfaceMonitorClass::Remove_DD_Surface(LPDIRECTDRAWSURFACE)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void SurfaceMonitorClass::Restore_Surfaces(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void SurfaceMonitorClass::Set_Surface_Focus(bool in_focus)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void Delay(int duration)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void *Build_Fading_Table(void const *palette, void const *dest, long int color, long int frac)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

int Clip_Rect(int *x, int *y, int *dw, int *dh, int width, int height)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

int Confine_Rect(int *x, int *y, int dw, int dh, int width, int height)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

#include <stdio.h>

#define far
#define __stdcall

#include "../CODE/movie.h"

void MpgPlay(const char* name, IDirectDraw* dd, IDirectDrawSurface* surface, RECT* dstRect)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void MpgPause(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void MpgResume(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void MpgSetCallback(LPMPGCALLBACK callback, LPVOID user)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}
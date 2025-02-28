#pragma once
#include "windows.h"

#define DDGBS_CANBLT 1

#define DD_OK 0

#define DDBLT_ASYNC     0x00000200
#define DDBLT_COLORFILL 0x00000400
#define DDBLT_WAIT      0x01000000

struct DDSURFACEDESC
{

};

struct DDBLTFX
{
    DWORD dwSize;
    //...
    DWORD dwFillColor;
};

struct DIRECTDRAW
{

};
typedef DIRECTDRAW *LPDIRECTDRAW;
typedef DIRECTDRAW *LPDIRECTDRAW2;

struct DIRECTDRAWSURFACE
{
    HRESULT Blt(RECT *dstRect, DIRECTDRAWSURFACE *src, RECT *srcRect, DWORD flags, DDBLTFX *effect);
    HRESULT GetBltStatus(DWORD flags);
};
typedef DIRECTDRAWSURFACE *LPDIRECTDRAWSURFACE;
#pragma once
#include "windows.h"

#define DDGBS_CANBLT 1

#define DD_OK 0

#define DDBLT_ASYNC     0x00000200
#define DDBLT_COLORFILL 0x00000400
#define DDBLT_WAIT      0x01000000

#define DDSD_CAPS 0

#define DDSCAPS_PRIMARYSURFACE 0x00000200
#define DDSCAPS_SYSTEMMEMORY 0x00000800

struct DIRECTDRAWSURFACE;

struct DDCAPS
{
    DWORD dwSize;
    //...
    DWORD dwVidMemTotal;
};

struct DDSCAPS
{
    DWORD dwCaps;
};

struct DDSURFACEDESC
{
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    //...
    DDSCAPS ddsCaps;
};

struct DDBLTFX
{
    DWORD dwSize;
    //...
    DWORD dwFillColor;
};

struct DIRECTDRAW
{
    HRESULT SetDisplayMode(DWORD width, DWORD height, DWORD bpp);
    HRESULT CreateSurface(DDSURFACEDESC *desc, DIRECTDRAWSURFACE **surf, void *);

    HRESULT GetCaps(DDCAPS *hwCaps, DDCAPS *helCaps);
};
typedef DIRECTDRAW IDirectDraw;
typedef DIRECTDRAW *LPDIRECTDRAW;
typedef DIRECTDRAW *LPDIRECTDRAW2;

struct DIRECTDRAWPALETTE
{
    HRESULT Release();
};
typedef DIRECTDRAWPALETTE IDirectDrawPalette;
typedef DIRECTDRAWPALETTE *LPDIRECTDRAWPALETTE;

struct DIRECTDRAWSURFACE
{
    HRESULT Blt(RECT *dstRect, DIRECTDRAWSURFACE *src, RECT *srcRect, DWORD flags, DDBLTFX *effect);
    HRESULT GetBltStatus(DWORD flags);

    HRESULT GetPalette(DIRECTDRAWPALETTE **palette);
    HRESULT SetPalette(DIRECTDRAWPALETTE *palette);

    HRESULT GetCaps(DDSCAPS *caps);

    HRESULT Release();
};
typedef DIRECTDRAWSURFACE IDirectDrawSurface;
typedef DIRECTDRAWSURFACE *LPDIRECTDRAWSURFACE;

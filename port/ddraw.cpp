#include <stdio.h>
#include "ddraw.h"


HRESULT DIRECTDRAW::SetDisplayMode(DWORD width, DWORD height, DWORD bpp)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAW::CreateSurface(DDSURFACEDESC *desc, DIRECTDRAWSURFACE **surf, void *)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAW::GetCaps(DDCAPS *hwCaps, DDCAPS *helCaps)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAWPALETTE::Release()
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAWSURFACE::Blt(RECT *dstRect, DIRECTDRAWSURFACE *src, RECT *srcRect, DWORD flags, DDBLTFX *effect)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAWSURFACE::GetBltStatus(DWORD flags)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAWSURFACE::GetPalette(DIRECTDRAWPALETTE **palette)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAWSURFACE::SetPalette(DIRECTDRAWPALETTE *palette)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAWSURFACE::GetCaps(DDSCAPS *caps)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

HRESULT DIRECTDRAWSURFACE::Release()
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

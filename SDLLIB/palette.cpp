#include <stdio.h>

#include "gbuffer.h"

void Set_Palette(void *palette)
{
    if(WindowBuffer)
        WindowBuffer->Update_Palette((uint8_t *)palette);
}
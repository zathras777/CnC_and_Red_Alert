#pragma once

extern "C" unsigned char  CurrentPalette[];

void Set_Palette(void *palette);
void Fade_Palette_To(unsigned char *palette, int fade, void (*callback)());
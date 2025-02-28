// this should exist in CODE/ ?
#pragma once

#include <stdint.h>

struct __attribute__((packed)) RGB
{
    uint8_t red, green, blue;
};

struct __attribute__((packed)) PCX_HEADER
{
    uint8_t header;
    uint8_t version;
    uint8_t encoding;
    uint8_t bpp;
    int16_t min_x;
    int16_t min_y;
    int16_t max_x;
    int16_t max_y;
    int16_t width;
    int16_t height;
    RGB ega_pal[16];
    uint8_t reserved;
    uint8_t num_planes;
    int16_t byte_per_line;
    int16_t palette_mode;
    uint8_t res2[58];
};

int Write_PCX_File(FileClass & file, GraphicBufferClass & pic, PaletteClass * palette);
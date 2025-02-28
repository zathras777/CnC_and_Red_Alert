#pragma once

#define _HARDERR_FAIL 3

struct find_t {
    char reserved[21];
    char attrib;
    unsigned wr_time;
    unsigned wr_date;
    long size;
    char name[13];
};

unsigned _dos_findfirst(char *, unsigned, struct find_t *);
#pragma once

#define _HARDERR_FAIL 3

#define _A_NORMAL 0x00

struct find_t
{
    char reserved[21];
    char attrib;
    unsigned wr_time;
    unsigned wr_date;
    long size;
    char name[13];
};

unsigned _dos_findfirst(char *, unsigned, struct find_t *);
unsigned _dos_findnext(struct find_t *);

struct diskfree_t
{
    unsigned total_clusters;
    unsigned avail_clusters;
    unsigned sectors_per_cluster;
    unsigned bytes_per_sector;
};

void _dos_getdrive(unsigned *drive);
void _dos_setdrive(unsigned, unsigned *);
unsigned _dos_getdiskfree(unsigned, struct diskfree_t *);
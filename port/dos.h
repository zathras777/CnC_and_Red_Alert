#pragma once

#define _HARDERR_FAIL 3

#define _A_NORMAL 0x00
#define _A_SUBDIR 0x10

struct find_t
{
    unsigned wr_time;
    unsigned wr_date;
    const char *name;

    void *data;
    int off;
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
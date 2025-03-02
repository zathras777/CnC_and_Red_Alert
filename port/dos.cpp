#include <stdio.h>
#include "dos.h"

unsigned _dos_findfirst(char *, unsigned, struct find_t *)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 2;
}

unsigned _dos_findnext(struct find_t *)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 2;
}

void _dos_getdrive(unsigned *drive)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    *drive = 0;
}

void _dos_setdrive(unsigned drive, unsigned *drives)
{
    *drives = 1;
    printf("%s\n", __PRETTY_FUNCTION__);
}

unsigned _dos_getdiskfree(unsigned drive, struct diskfree_t *diskspace)
{
    diskspace->total_clusters = diskspace->avail_clusters = 8 * 1024;
    diskspace->sectors_per_cluster = 2;
    diskspace->bytes_per_sector = 512;
    return 0;
}
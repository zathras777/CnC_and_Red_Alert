#include <glob.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include "dos.h"

static bool update_find_result(find_t *result)
{
    auto glob_buf = (glob_t *)result->data;

    struct stat stat_buf;

    // skip any dirs
    while(result->off < glob_buf->gl_pathc && stat(glob_buf->gl_pathv[result->off], &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
        result->off++;

    if(result->off == glob_buf->gl_pathc)
        return false;

    // convert time
    auto tm = localtime(&stat_buf.st_mtime);

    result->wr_date = tm->tm_mday | (tm->tm_mon + 1) << 5 | (tm->tm_year - 80) << 9;
    result->wr_time = (tm->tm_sec / 2) | tm->tm_min << 5 | tm->tm_hour << 11;

    result->name = glob_buf->gl_pathv[result->off];
    return true;
}

unsigned _dos_findfirst(char *name, unsigned attr, struct find_t *result)
{
    auto glob_buf = new glob_t;
    int ret = glob(name, GLOB_MARK, NULL, glob_buf);

    if(ret)
    {
        delete glob_buf;
        return 2; // not found
    }

    result->off = 0;
    result->data = glob_buf;

    if(!update_find_result(result))
    {
        globfree(glob_buf);
        delete glob_buf;
        return 2;
    }

    return 0;
}

unsigned _dos_findnext(struct find_t *result)
{
    // increment offset
    result->off++;
    auto glob_buf = (glob_t *)result->data;

    if(!glob_buf)
        return 2;

    if(!update_find_result(result))
    {
        globfree(glob_buf);
        delete glob_buf;
        result->data = NULL;
        return 2; // not found
    }

    return 0;
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
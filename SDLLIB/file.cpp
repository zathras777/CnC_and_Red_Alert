#include <glob.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statvfs.h>

#include "file.h"

void *IO_Open_File(const char *filename, int mode)
{
    const char *mode_str;

    if(mode == READ)
        mode_str = "rb";
    else if(mode == WRITE)
        mode_str = "wb";
    else if(mode == (READ | WRITE))
        mode_str = "w+b";
    else
        return NULL;

    return fopen(filename, mode_str);
}

void IO_Close_File(void *handle)
{
    auto file = (FILE *)handle;
    fclose(file);
}

bool IO_Read_File(void *handle, void *buffer, size_t count, size_t &actual_read)
{
    auto file = (FILE *)handle;
    actual_read = fread(buffer, 1, count, file);
    return ferror(file) == 0;
}

bool IO_Write_File(void *handle, const void *buffer, size_t count, size_t &actual_written)
{
    auto file = (FILE *)handle;
    actual_written = fwrite(buffer, 1, count, file);
    return ferror(file) == 0;
}

size_t IO_Seek_File(void *handle, size_t offset, int origin)
{
    auto file = (FILE *)handle;
    fseek(file, offset, origin);
    return ftell(file);
}

size_t IO_Get_File_Size(void *handle)
{
    auto file = (FILE *)handle;
    long pos = ftell(file);

    fseek(file, 0, SEEK_END);

    long length = ftell(file);

    fseek(file, pos, SEEK_SET);

    return length;
}

bool IO_Delete_File(const char *filename)
{
    return unlink(filename) == 0;
}

static bool Update_Find_Result(FindFileState &state)
{
    auto glob_buf = (glob_t *)state.data;

    struct stat stat_buf;

    // skip any dirs
    while(state.off < glob_buf->gl_pathc && stat(glob_buf->gl_pathv[state.off], &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
        state.off++;

    if(state.off == glob_buf->gl_pathc)
        return false;

    state.mod_time = stat_buf.st_mtime;

    state.name = glob_buf->gl_pathv[state.off];
    return true;
}

bool Find_First_File(const char *path_glob, FindFileState &state)
{
    auto glob_buf = new glob_t;
    int ret = glob(path_glob, GLOB_MARK, NULL, glob_buf);

    if(ret)
    {
        delete glob_buf;
        return false;
    }

    state.off = 0;
    state.data = glob_buf;

    if(!Update_Find_Result(state))
    {
        globfree(glob_buf);
        delete glob_buf;
        return false;
    }

    return true;
}

bool Find_Next_File(FindFileState &state)
{
    // increment offset
    state.off++;
    auto glob_buf = (glob_t *)state.data;

    if(!glob_buf)
        return 2;

    if(!Update_Find_Result(state))
    {
        globfree(glob_buf);
        delete glob_buf;
        state.data = NULL;
        return false;
    }

    return true;
}

void End_Find_File(FindFileState &state)
{
    if(state.data)
    {
        auto glob_buf = (glob_t *)state.data;
        globfree(glob_buf);
        delete glob_buf;
        state.data = NULL;
    }
}

uint64_t Disk_Space_Available()
{
    struct statvfs fsbuf;
    char path[1024];
    if(!getcwd(path, 1000))
        return 0;

    if(statvfs(path, &fsbuf) < 0)
        return 0;

    return fsbuf.f_bavail * fsbuf.f_bsize;
}
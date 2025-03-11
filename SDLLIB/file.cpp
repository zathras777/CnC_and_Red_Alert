#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <glob.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#endif

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

#ifdef _WIN32
static bool Update_Find_Result(FindFileState &state, WIN32_FIND_DATA &data)
{
    // skip hidden/system/dir

    bool success = true;
    while(success && (data.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)))
        success = FindNextFile((HANDLE)state.data, &data);

    if(!success)
        return false;

    state.name = strdup(data.cFileName);

    ULARGE_INTEGER big;
    big.LowPart = data.ftLastWriteTime.dwLowDateTime;
    big.HighPart = data.ftLastWriteTime.dwHighDateTime;
    state.mod_time = big.QuadPart / 10000000ULL - 11644473600ULL;

    return true;
}

bool Find_First_File(const char *path_glob, FindFileState &state)
{
    WIN32_FIND_DATA data;
    auto handle = FindFirstFile(path_glob, &data);

    if(handle == INVALID_HANDLE_VALUE)
        return false;

    state.data = handle;

    if(!Update_Find_Result(state, data))
    {
        FindClose(handle);
        state.data = NULL;
        return false;
    }

    return true;
}

bool Find_Next_File(FindFileState &state)
{
    WIN32_FIND_DATA data;

    // free old filename
    free((char *)state.name);
    state.name = NULL;

    if(!FindNextFile((HANDLE)state.data, &data) || !Update_Find_Result(state, data))
    {
        FindClose((HANDLE)state.data);
        state.data = NULL;
        return false;
    }
    return true;
}

void End_Find_File(FindFileState &state)
{
    if(state.name)
    {
        free((char *)state.name);
        state.name = NULL;
    }

    if(state.data)
    {
        FindClose((HANDLE)state.data);
        state.data = NULL;
    }
}

uint64_t Disk_Space_Available()
{
    ULARGE_INTEGER space;
    if(GetDiskFreeSpaceEx(NULL, &space, NULL, NULL))
        return space.QuadPart;

    return 0;
}
#else
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
#endif
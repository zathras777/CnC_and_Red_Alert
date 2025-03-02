#include <cassert>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
{
    // whoops no drive letters
    if(drive)
        drive[0] = 0;

    const char *fwd = strrchr(path, '/');
    const char *back = strrchr(path, '\\');
    const char *last_slash = fwd > back ? fwd : back;
    const char *dot = strrchr(last_slash ? last_slash : path, '.');

    if(dir)
    {
        if(!last_slash)
            dir[0] = 0;
        else
        {
            strncpy(dir, path, last_slash - path + 1);
            dir[last_slash - path + 1] = 0;
        }
    }

    if(fname)
    {
        const char *start = last_slash ? last_slash + 1 : path;
        const char *end = dot ? dot : path + strlen(path);
        strncpy(fname, start, end - start);
        fname[end - start] = 0;
    }

    if(ext)
    {
        if(!dot)
            ext[0] = 0;
        else
            strcpy(ext, dot);
    }
}

void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext)
{
    const char *pre_sep = "";
    const char *post_sep = "";
    const char *dot = "";

    if(!dir)
        dir = "";
    else if(strlen(dir))
    {
        if(dir[0] != '/' && dir[0] != '\\')
            pre_sep = "/";
        char dir_end = dir[strlen(dir) - 1];
        if(dir_end != '/' && dir_end != '\\')
            post_sep = "/";
    }

    if(!fname)
        fname = "";

    if(!ext)
        ext = "";
    else if(strlen(ext) && ext[0] != '.')
        dot = ".";

    sprintf(path, "%s%s%s%s%s%s", pre_sep, dir, post_sep, fname, dot, ext);
}

char *itoa(int value, char *buffer, int radix)
{
    // all the cases we care about
    assert(radix == 10);
    sprintf(buffer, "%i", value);
    return buffer;
}

int stricmp(const char *string1, const char *string2)
{
    while(*string1 && tolower(*string1) == tolower(*string2))
    {
        string1++;
        string2++;
    }
    return (unsigned char)tolower(*string1) - (unsigned char)tolower(*string2);
}

int strnicmp(const char *string1, const char *string2, size_t count)
{
    while(count-- && *string1 && tolower(*string1) == tolower(*string2))
    {
        string1++;
        string2++;
    }

    if(count == 0)
        return 0;

    return (unsigned char)tolower(*string1) - (unsigned char)tolower(*string2);
}

int memicmp(const void *buffer1, const void *buffer2, size_t count)
{
    const char *cbuffer1 = (const char *)buffer1;
    const char *cbuffer2 = (const char *)buffer2;
    while(count-- && tolower(*cbuffer1) == tolower(*cbuffer2))
    {
        cbuffer1++;
        cbuffer2++;
    }

    if(count == 0)
        return 0;

    return (unsigned char)tolower(*cbuffer1) - (unsigned char)tolower(*cbuffer2);
}

char *strupr(char *str)
{
    for(char *p = str; *p; p++)
        *p = toupper(*p);
    
    return str;
}

char *strlwr(char *str)
{
    for(char *p = str; *p; p++)
        *p = tolower(*p);
    
    return str;
}

char *strrev(char *str)
{
    int len = strlen(str);
    if(len < 2)
        return str;

    char *start = str;
    char *end = str + len - 1;
    
    while(end > start)
    {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }

    return str;
}
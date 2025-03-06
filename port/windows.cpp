#include <stdio.h>

#include "windows.h"

bool CloseHandle(HANDLE object)
{
    // potentially not a file, but nothing else is implemented
    if(object)
        fclose((FILE *)object);
    return true;
}

UINT SetErrorMode(UINT mode)
{
    // only used around calls to ReadFile
    return 0;
}

DWORD GetLastError()
{
    return 0; // this is fine
}

bool DosDateTimeToFileTime(WORD fatDate, WORD fatTime, FILETIME *fileTime)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool FileTimeToDosDateTime(const FILETIME *fileTime, WORD *fatDate, WORD *fatTime)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

void GetSystemTime(SYSTEMTIME *time)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

DWORD GetVersion()
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void GlobalMemoryStatus(MEMORYSTATUS *buffer)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    buffer->dwTotalPhys = 16 * 1024 * 1024;
}

DWORD GetModuleFileName(HMODULE module, char *filename, DWORD size)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    filename[0] = 0;
    return 0;
}

int ShowCursor(bool show)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

bool SetCommBreak(HANDLE file)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool ClearCommBreak(HANDLE file)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool EscapeCommFunction(HANDLE file, DWORD func)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool SetForegroundWindow(HWND wnd)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

bool ShowWindow(HWND wnd, int cmdShow)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

HWND FindWindow(const char *className, const char *windowName)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

int MessageBox(HWND wnd, const char *text, const char *caption, UINT type)
{
    printf("MessageBox %s/%s (%x)\n", text, caption, type);
    return MB_OK;
}

HANDLE CreateFile(const char *fileName, DWORD access, DWORD shareMode, void/*SECURITY_ATTRIBUTES*/ *security, DWORD creationDisposition, DWORD flags, HANDLE templ)
{
    const char *mode;

    if(access == GENERIC_READ && creationDisposition == OPEN_EXISTING)
        mode = "rb";
    else if(access == GENERIC_WRITE && creationDisposition == CREATE_ALWAYS)
        mode = "wb";
    else if(access == (GENERIC_READ | GENERIC_WRITE) && creationDisposition == CREATE_ALWAYS)
        mode = "w+b";
    else
    {
        printf("CreateFile %s %x %x %p %x %x %p\n", fileName, access, shareMode, security, creationDisposition, flags, templ);
        return NULL;
    }

    // may need to tag...
    return fopen(fileName, mode);
}

bool ReadFile(HANDLE file, void *buffer, DWORD bytesToRead, DWORD *bytesRead, void/*OVERLAPPED*/ *overlapped)
{
    size_t read = fread(buffer, 1, bytesToRead, (FILE *)file);

    if(bytesRead)
        *bytesRead = read;

    return ferror((FILE *)file) == 0;
}

bool WriteFile(HANDLE file, const void *buffer, DWORD bytesToWrite, DWORD *bytesWritten, void/*OVERLAPPED*/ *overlapped)
{
    size_t written = fwrite(buffer, 1, bytesToWrite, (FILE *)file);

    if(bytesWritten)
        *bytesWritten = written;

    return ferror((FILE *)file) == 0;
}

DWORD SetFilePointer(HANDLE file, LONG distance, LONG *distHigh, DWORD method)
{
    // defined the methods to SEEK_x
    fseek((FILE *)file, distance, method);
    return ftell((FILE *)file);
}

DWORD GetFileSize(HANDLE file, DWORD *fileSizeHigh)
{
    long pos = ftell((FILE *)file);

    fseek((FILE *)file, 0, SEEK_END);

    long length = ftell((FILE *)file);

    fseek((FILE *)file, pos, SEEK_SET);

    return length;
}

bool DeleteFile(const char *fileName)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool GetFileInformationByHandle(HANDLE file, BY_HANDLE_FILE_INFORMATION *information)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool GetFileTime(HANDLE hFile, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool SetFileTime(HANDLE file, const FILETIME *creationTime, const FILETIME *lastAccessTime, const FILETIME *lastWriteTime)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

HANDLE FindFirstFile(const char *fileName, WIN32_FIND_DATA *findData)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

bool FindNextFile(HANDLE findFile, WIN32_FIND_DATA *findData)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}
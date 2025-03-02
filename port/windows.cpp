#include <stdio.h>

#include "windows.h"

bool CloseHandle(HANDLE object)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

UINT SetErrorMode(UINT mode)
{
    printf("%s\n", __PRETTY_FUNCTION__);
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

bool PostMessage(HWND wnd, UINT msg, UINT *wParam, LONG *lParam)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return true;
}

int MessageBox(HWND wnd, const char *text, const char *caption, UINT type)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return MB_OK;
}

HANDLE CreateFile(const char *fileName, DWORD access, DWORD shareMode, void/*SECURITY_ATTRIBUTES*/ *security, DWORD creationDisposition, DWORD flags, HANDLE templ)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

bool ReadFile(HANDLE file, void *buffer, DWORD bytesToRead, DWORD *bytesRead, void/*OVERLAPPED*/ *overlapped)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

bool WriteFile(HANDLE file, const void *buffer, DWORD bytesToWrite, DWORD *bytesWritten, void/*OVERLAPPED*/ *overlapped)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

DWORD SetFilePointer(HANDLE file, LONG distance, LONG *distHigh, DWORD method)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

DWORD GetFileSize(HANDLE file, DWORD *fileSizeHigh)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
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

bool GetVolumeInformation(const char *rootPath, char *volumeNameBuf, DWORD volumeNameSize, DWORD *volumeSerialNo, DWORD *maxComponentLen, DWORD *fileSystemFlags, char *fileSystemNameBuf, DWORD fileSystemNameLen)
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
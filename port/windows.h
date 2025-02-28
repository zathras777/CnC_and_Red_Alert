#pragma once
#include <stdint.h>

#include "netinet/in.h"

#define _MAX_PATH 260
#define _MAX_FNAME 256
#define _MAX_EXT 256

#ifndef FALSE
#define FALSE 0
#endif

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint32_t UINT;
typedef int32_t INT;
typedef int32_t LONG;

#define INVALID_HANDLE_VALUE NULL
typedef void *HANDLE;
typedef HANDLE HWND;

typedef LONG HRESULT;

struct CRITICAL_SECTION
{

};

struct RECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
};

struct FILETIME
{
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
};

#define SEM_FAILCRITICALERRORS 0x0001

bool CloseHandle(HANDLE object);

UINT SetErrorMode(UINT mode);
DWORD GetLastError();

bool DosDateTimeToFileTime(WORD fatDate, WORD fatTime, FILETIME *fileTime);
bool FileTimeToDosDateTime(const FILETIME *fileTime, WORD *fatDate, WORD *fatTime);

// fileapi
#define GENERIC_WRITE 0x40000000
#define GENERIC_READ 0x80000000
#define FILE_SHARE_READ 0x00000001
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_NORMAL 0x80
#define FILE_BEGIN SEEK_SET
#define FILE_CURRENT SEEK_CUR
#define FILE_END SEEK_END

struct BY_HANDLE_FILE_INFORMATION
{
    FILETIME ftCreationTime;
    FILETIME ftLastWriteTime;
};

HANDLE CreateFile(const char *fileName, DWORD access, DWORD shareMode, void/*SECURITY_ATTRIBUTES*/ *security, DWORD creationDisposition, DWORD flags, HANDLE templ);
bool ReadFile(HANDLE file, void *buffer, DWORD bytesToRead, DWORD *bytesRead, void/*OVERLAPPED*/ *overlapped);
bool WriteFile(HANDLE file, const void *buffer, DWORD bytesToWrite, DWORD *bytesWritten, void/*OVERLAPPED*/ *overlapped);
DWORD GetFileSize(HANDLE file, DWORD *fileSizeHigh);
bool DeleteFile(const char *fileName);
bool GetFileInformationByHandle(HANDLE file, BY_HANDLE_FILE_INFORMATION *information);
bool SetFileTime(HANDLE file, const FILETIME *creationTime, const FILETIME *lastAccessTime, const FILETIME *lastWriteTime);
DWORD SetFilePointer(HANDLE file, LONG distance, LONG *distHigh, DWORD method);

// winsock
#define MAXGETHOSTSTRUCT 1024
struct WSADATA
{

};
typedef int SOCKET;
typedef in_addr IN_ADDR;

// technically defined in MS stdlib.h
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext);
char *itoa(int value, char *buffer, int radix);
char *ltoa(long value, char *buffer, int radix);
// ... string.h
int stricmp(const char *string1, const char *string2);
char *strupr(char *str);
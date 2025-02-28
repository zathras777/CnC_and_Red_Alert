#pragma once
#include <stdint.h>

//#include <arpa/inet.h>
#include <netinet/in.h>
//#include <netdb.h>
//#include <sys/socket.h>

#define _MAX_PATH 260
#define MAX_PATH _MAX_PATH
#define _MAX_FNAME 256
#define _MAX_EXT 256
#define _MAX_DRIVE 3

#ifndef FALSE
#define FALSE 0
#endif

#define FAR
#define PASCAL

typedef void VOID;
typedef int BOOL;
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint32_t UINT;
typedef uint32_t ULONG;
typedef int32_t INT;
typedef int32_t LONG;

typedef void *LPVOID;
typedef BYTE *LPBYTE;
typedef DWORD *LPDWORD;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef LPCSTR LPCTSTR;

#define INVALID_HANDLE_VALUE NULL
typedef void *HANDLE;
typedef HANDLE HWND;
typedef HANDLE HSZ;
typedef HANDLE HDDEDATA;
typedef HANDLE HCONV;
typedef HANDLE HBITMAP;
typedef HANDLE HPALETTE;
typedef HANDLE HDC;
typedef HANDLE HINSTANCE;
typedef HANDLE HCURSOR;
typedef HANDLE HMODULE;

typedef LONG HRESULT;
#define FAILED(hr) ((hr) < 0)

#define CALLBACK

struct CRITICAL_SECTION
{

};

struct OVERLAPPED
{

};

struct RECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
};
typedef RECT *LPRECT;

struct FILETIME
{
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
};
struct SYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
};

struct MEMORYSTATUS
{
    DWORD dwLength;
    //...
    size_t dwTotalPhys;
};

#define SEM_FAILCRITICALERRORS 0x0001

bool CloseHandle(HANDLE object);

UINT SetErrorMode(UINT mode);
DWORD GetLastError();

bool DosDateTimeToFileTime(WORD fatDate, WORD fatTime, FILETIME *fileTime);
bool FileTimeToDosDateTime(const FILETIME *fileTime, WORD *fatDate, WORD *fatTime);

void GetSystemTime(SYSTEMTIME *time);

DWORD GetVersion();

void GlobalMemoryStatus(MEMORYSTATUS *buffer);

DWORD GetModuleFileName(HMODULE module, char *filename, DWORD size);

// cursor
int ShowCursor(bool show);

// com ports
#define CLRDTR 6
bool SetCommBreak(HANDLE file);
bool ClearCommBreak(HANDLE file);
bool EscapeCommFunction(HANDLE file, DWORD func);

// window related
#define SW_SHOWMAXIMIZED 3
#define SW_RESTORE 9

#define MB_OK 0x00000000
#define MB_YESNO 0x00000004
#define MB_ICONQUESTION 0x00000020
#define MB_ICONEXCLAMATION 0x00000030

#define IDNO 7

#define WM_DESTROY 0x0002
#define WM_USER 0x400

bool SetForegroundWindow(HWND wnd);
bool ShowWindow(HWND wnd, int cmdShow);
HWND FindWindow(const char *className, const char *windowName);
bool PostMessage(HWND wnd, UINT msg, UINT *wParam, LONG *lParam);

int MessageBox(HWND wnd, const char *text, const char *caption, UINT type);

// fileapi
#define GENERIC_WRITE 0x40000000
#define GENERIC_READ 0x80000000
#define FILE_SHARE_READ 0x00000001
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_HIDDEN 0x02
#define FILE_ATTRIBUTE_SYSTEM 0x04
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_NORMAL 0x80
#define FILE_ATTRIBUTE_TEMPORARY 0x100
#define FILE_BEGIN SEEK_SET
#define FILE_CURRENT SEEK_CUR
#define FILE_END SEEK_END

struct BY_HANDLE_FILE_INFORMATION
{
    FILETIME ftCreationTime;
    FILETIME ftLastWriteTime;
};

struct WIN32_FIND_DATA
{
    DWORD dwFileAttributes;
    //...
    char cFileName[MAX_PATH];
    char cAlternateFileName[14];
    //...
};


HANDLE CreateFile(const char *fileName, DWORD access, DWORD shareMode, void/*SECURITY_ATTRIBUTES*/ *security, DWORD creationDisposition, DWORD flags, HANDLE templ);
bool ReadFile(HANDLE file, void *buffer, DWORD bytesToRead, DWORD *bytesRead, void/*OVERLAPPED*/ *overlapped);
bool WriteFile(HANDLE file, const void *buffer, DWORD bytesToWrite, DWORD *bytesWritten, void/*OVERLAPPED*/ *overlapped);
DWORD GetFileSize(HANDLE file, DWORD *fileSizeHigh);
bool DeleteFile(const char *fileName);
bool GetFileInformationByHandle(HANDLE file, BY_HANDLE_FILE_INFORMATION *information);
bool GetFileTime(HANDLE hFile, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime);
bool SetFileTime(HANDLE file, const FILETIME *creationTime, const FILETIME *lastAccessTime, const FILETIME *lastWriteTime);
DWORD SetFilePointer(HANDLE file, LONG distance, LONG *distHigh, DWORD method);
bool GetVolumeInformation(const char *rootPath, char *volumeNameBuf, DWORD volumeNameSize, DWORD *volumeSerialNo, DWORD *maxComponentLen, DWORD *fileSystemFlags, char *fileSystemNameBuf, DWORD fileSystemNameLen);
HANDLE FindFirstFile(const char *fileName, WIN32_FIND_DATA *findData);
bool FindNextFile(HANDLE findFile, WIN32_FIND_DATA *findData);

// winsock
#define MAXGETHOSTSTRUCT 1024
struct WSADATA
{

};
typedef int SOCKET;
typedef in_addr IN_ADDR;
#define SOCKET_ERROR -1

// technically defined in MS stdlib.h
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext);
char *itoa(int value, char *buffer, int radix);
char *ltoa(long value, char *buffer, int radix);
// ... string.h
int stricmp(const char *string1, const char *string2);
#define _stricmp stricmp
#define strcmpi stricmp
int strnicmp(const char *string1, const char *string2, size_t count);
int memicmp(const void *buffer1, const void *buffer2, size_t count);
char *strupr(char *str);
char *strlwr(char *str);
#define _strlwr strlwr
char *strrev(char *str);
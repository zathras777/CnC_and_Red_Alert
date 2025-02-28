#pragma once

// stolen from WinModemClass
enum
{
    CTS_SET  = 0x10,
    DSR_SET  = 0x20,
    RI_SET   = 0x40,
    CD_SET   = 0x80
};

#define ASSUCCESS 0
#define ASUSERABORT -16 //COMMUSERABORT in wincomm.h

void HMWaitForOK(int, void *);
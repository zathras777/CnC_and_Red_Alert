#include <stddef.h>
#include <stdio.h>

#include "wincomm.h"
#include "modemreg.h"

WinModemClass *SerialPort;

WinModemClass::WinModemClass(void)
{

}

WinModemClass::~WinModemClass(void)
{

}

HANDLE WinModemClass::Serial_Port_Open(char *device_name, int baud, int parity, int wordlen, int stopbits, int flowcontrol)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

void WinModemClass::Serial_Port_Close(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int	WinModemClass::Read_From_Serial_Port(unsigned char *dest_ptr, int buffer_len)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void WinModemClass::Write_To_Serial_Port(unsigned char *buffer, int length)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WinModemClass::Set_Modem_Dial_Type(WinCommDialMethodType method)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

unsigned WinModemClass::Get_Modem_Status(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void WinModemClass::Set_Serial_DTR(bool state)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int WinModemClass::Get_Modem_Result(int delay, char *buffer, int buffer_len)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void WinModemClass::Dial_Modem(char *dial_number)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int WinModemClass::Send_Command_To_Modem(char *command, char terminator, char *buffer, int buflen, int delay, int retries)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void WinModemClass::Set_Echo_Function(void(*func)(char c))
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void WinModemClass::Set_Abort_Function(int (*func)(void))
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

HANDLE WinModemClass::Get_Port_Handle(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

ModemRegistryEntryClass::ModemRegistryEntryClass(int modem_number)
{

}

ModemRegistryEntryClass::~ModemRegistryEntryClass()
{

}
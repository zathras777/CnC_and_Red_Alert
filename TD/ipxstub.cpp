#include "ipx95.h"

bool IPX_Initialise(void)
{
    return false;
}

bool IPX_Get_Outstanding_Buffer95(unsigned char *buffer)
{
    return false;
}

void IPX_Shut_Down95(void)
{

}

int  IPX_Send_Packet95(unsigned char *, unsigned char *, int, unsigned char*, unsigned char*)
{
    return 0;
}

int  IPX_Broadcast_Packet95(unsigned char *, int)
{
    return 0;
}

bool IPX_Start_Listening95(void)
{
    return false;
}

int  IPX_Open_Socket95(int socket)
{
    return 0;
}

void IPX_Close_Socket95(int socket)
{

}

int  IPX_Get_Connection_Number95(void)
{
    return 0;
}

int  IPX_Get_Local_Target95(unsigned char *, unsigned char*, unsigned short, unsigned char*)
{
    return 0;
}
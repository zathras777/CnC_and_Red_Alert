#include <algorithm>
#include <stdio.h>
#include <forward_list>

#include "net_select.h"

#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/select.h>
#endif

struct SocketInfo
{
    int socket;
    SocketCallback callback;
    void *data;
    bool check_write;
};

static std::forward_list<SocketInfo> Sockets;

static std::forward_list<SocketInfo>::iterator Find_Socket(int socket)
{
    return std::find_if(Sockets.begin(), Sockets.end(), [socket](SocketInfo &s) {return s.socket == socket;});
}

bool Socket_Register_Select(int socket, SocketCallback callback, void *data)
{
    if(!callback)
        return false;

    if(Find_Socket(socket) != Sockets.end())
        return false;

    // add to list
    SocketInfo info;
    info.socket = socket;
    info.callback = callback;
    info.data = data;
    info.check_write = false;
    Sockets.push_front(info);

    return true;
}

void Socket_Unregister_Select(int socket)
{
    Sockets.remove_if([socket](SocketInfo &s){return s.socket == socket;});
}

void Socket_Check_Write(int socket, bool check)
{
    auto it = Find_Socket(socket);
    if(it != Sockets.end())
        it->check_write = check;
}

void Socket_Select()
{
    // something something poll something

    fd_set read_set, write_set, err_set;
    int max_fd = -1;
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    FD_ZERO(&err_set);

    for(auto &sock : Sockets)
    {
        FD_SET(sock.socket, &read_set);
        if(sock.check_write)
            FD_SET(sock.socket, &write_set);
        FD_SET(sock.socket, &err_set);
        if(sock.socket > max_fd)
            max_fd = sock.socket;
    }

    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    int ready = select(max_fd + 1, &read_set, &write_set, &err_set, &timeout);

    if(ready)
    {
        for(auto &sock : Sockets)
        {
            if(FD_ISSET(sock.socket, &read_set))
                sock.callback(sock.socket, SOCKEV_READ, sock.data);
            if(FD_ISSET(sock.socket, &write_set))
                sock.callback(sock.socket, SOCKEV_WRITE, sock.data);
            if(FD_ISSET(sock.socket, &err_set))
                sock.callback(sock.socket, SOCKEV_ERROR, sock.data);
        }
    }
}
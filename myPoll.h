#ifndef _MYPOLL_H
#define _MYPOLL_H

#if defined (_WIN32) || (_WIN64)
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <poll.h>
#endif

int mypoll(struct pollfd*, int, int);

#endif
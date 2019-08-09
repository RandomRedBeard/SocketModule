/*
 * s_io.h
 *
 *  Created on: Oct 3, 2017
 *      Author: thomasjansen
 */

#ifndef IO_H_
#define IO_H_

#if defined (_WIN32) || (_WIN64)
#include <WinSock2.h>
#include <Windows.h>
#define poll WSAPoll
#pragma comment(lib,"ws2_32.lib")
#else
#include <poll.h>
#include <sys/socket.h>
#endif

#include <stdio.h>
#include <errno.h>

int writeStream(const int, const char*, int, int);

int readStream(const int, char*, int, int);

int readln(const int, char*, int, int, char);

#endif /* IO_H_ */

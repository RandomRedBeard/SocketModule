/*
 * s_io.h
 *
 *  Created on: Oct 3, 2017
 *      Author: thomasjansen
 */

#ifndef IO_H_
#define IO_H_

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#else
#include <sys/socket.h>
#endif

#if defined _WIN32
  #ifdef BUILDING_DLL
      #define DLL_PUBLIC __declspec(dllexport)
  #else
      #define DLL_PUBLIC __declspec(dllimport)
  #endif
#else
#define DLL_PUBLIC
#endif

#include <stdio.h>
#include <errno.h>

#include "myPoll.h"

DLL_PUBLIC int writeStream(const int, const char*, int, int);

DLL_PUBLIC int readStream(const int, char*, int, int);

DLL_PUBLIC int readln(const int, char*, int, int, char);

DLL_PUBLIC int printHello();

#endif /* IO_H_ */

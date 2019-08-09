/*
 * Socket.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: thomasjansen
 */

#include "Socket.h"

Socket::Socket(int f) : fd(f)
{
}

Socket::Socket()
{
	fd = -1;
}

Socket::Socket(std::string addr, int port)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(addr.c_str());
	serv.sin_port = htons(port);
	serv_len = sizeof(serv);

	int portLen = snprintf(nullptr,0,"%d", port);
	char* portBuffer = (char*)malloc(portLen + 1);

	snprintf(portBuffer, portLen, "%d", port);

	struct addrinfo hints , *taddr;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(addr.c_str(), portBuffer, &hints, &taddr);

	connect(fd, (sockaddr*)taddr->ai_addr, taddr->ai_addrlen);

	free(portBuffer);
}

Socket::~Socket()
{
	closeSocket();
}

void Socket::setPollWait(int pollWait)
{
	poll_wait = pollWait;
}

void Socket::setOpSep(char opSep)
{
	op_sep = opSep;
}

int Socket::read(char *buffer, int len)
{
	return readln(fd, buffer, len, poll_wait, op_sep);
}

int Socket::write(const char *buffer, int len)
{
	return writeStream(fd, buffer, len, poll_wait);
}

int Socket::closeSocket()
{
#if defined(_WIN32) || (_WIN64)
	return closesocket(fd);
#else
	return close(fd);
#endif
}

int Socket::shutdownSocket()
{
	return shutdown(fd, 2);
}

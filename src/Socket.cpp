/*
 * Socket.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: thomasjansen
 */

#include <Socket.h>

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

	// u_long iMode=1;

	// int iResult = ioctlsocket(fd, FIONBIO, &iMode);
	// if (iResult != NO_ERROR)
	// 	printf("ioctlsocket failed with error: %ld\n", iResult);

	int portLen = snprintf(nullptr,0,"%d", port);
	char* portBuffer = (char*)malloc(portLen + 1);

	// snprintf length arg includes \0 so true length
	snprintf(portBuffer, portLen + 1, "%d", port);

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

int Socket::rawRead(char* buffer, int len) {
	return readStream(fd, buffer, len, poll_wait);
}

int Socket::write(const char *buffer, int len)
{
	return writeStream(fd, buffer, len, poll_wait);
}

int Socket::closeSocket()
{
	return close(fd);
}

int Socket::shutdownSocket()
{
	return shutdown(fd, 2);
}

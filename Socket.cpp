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

Socket::Socket(const char *addr, const char *port)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);

	// u_long iMode=1;

	// int iResult = ioctlsocket(fd, FIONBIO, &iMode);
	// if (iResult != NO_ERROR)
	// 	printf("ioctlsocket failed with error: %ld\n", iResult);

	struct addrinfo hints, *taddr;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(addr, port, &hints, &taddr);

	int i = connect(fd, (sockaddr *)taddr->ai_addr, taddr->ai_addrlen);
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
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;

	int n, pollerr;

	pollerr = POLLNVAL | POLLERR;

	n = poll(&pfd, 1, poll_wait);

	if (n < 0)
	{
		return -1;
	}

	if (pfd.revents & pollerr)
	{ //CLOSED Socket
		return -1;
	}

	// Recieved hangup and no bytes to read
	if (pfd.revents & POLLHUP && !(pfd.revents & POLLIN))
	{
		return 0;
	}

	if ((n = recv(fd, buffer, len, 0)) < 0)
	{
		return -1;
	}

	*(buffer + n) = '\0';
	return n;
}

int Socket::readln(char *buffer, int len)
{
	int ntaken = 0, n;
	while (ntaken < len)
	{
		n = read((buffer + ntaken), 1);
		if (n == 0)
			break;
		if (n == -1)
			return n;
		if (*(buffer + ntaken) == op_sep)
			break;
		ntaken += n;
	}
	*(buffer + ntaken) = '\0';
	return ntaken;
}

int Socket::write(const char *buffer, int len)
{
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLOUT;
	int nwritten = 0, pollerr, n;

	pollerr = POLLHUP | POLLNVAL | POLLERR;

	do
	{
		if (poll(&pfd, 1, poll_wait) < 0)
		{
			return -1;
		}

		if (pfd.revents & pollerr)
		{
			return -1;
		}

		if ((n = send(fd, (buffer + nwritten), len, 0)) < 0)
		{
			return -1;
		}

		if (n == 0)
			break;

		len -= n;
		nwritten += n;

	} while (len > 0);

	return nwritten;
}

int Socket::closeSocket()
{
	return close(fd);
}

int Socket::shutdownSocket()
{
	return shutdown(fd, 2);
}

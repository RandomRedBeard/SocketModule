/*
 * ServerSocket.cpp
 *
 *  Created on: Oct 3, 2017
 *      Author: thomasjansen
 */

#include <Socket.h>

ServerSocket::ServerSocket( int port ) {
	sock = socket( AF_INET , SOCK_STREAM , 0 );
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons( port );
	serv_len = sizeof( serv );
}

ServerSocket::~ServerSocket() {
	close( sock );
}

int ServerSocket::bindSocket() {
	return bind( sock , ( struct sockaddr* )&serv , serv_len );
}

int ServerSocket::listenSocket( int n ) {
	return listen( sock , n );
}

Socket* ServerSocket::acceptSocket() {
	int f;
	f = accept(sock, nullptr, nullptr);

	if (f < 0) {
		return (Socket*) nullptr;
	}

	return new Socket(f);
}

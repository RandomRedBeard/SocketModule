#include <Socket.h>

int main() {
#if defined (_WIN32) || (_WIN64)
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

    Socket s("chaim-in.com", 80);

	const char* get = "GET /\r\n";
	s.write(get, strlen(get));

	char buffer[128];

	s.read(buffer, 127);

	printf("%s\n", buffer);
}
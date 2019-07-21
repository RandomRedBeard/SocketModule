CC = gcc
CFLAG = -Wall -c -fPIC
LFLAG = -std=c++17 -lstdc++ -lpthread -lm

OBJS = ServerSocket.o Socket.o io.o myPoll.o

ServerSocket.o:
	$(CC) $(CFLAG) ServerSocket.cpp -o ServerSocket.o
Socket.o:
	$(CC) $(CFLAG) Socket.cpp -o Socket.o
io.o:
	$(CC) $(CFLAG) io.cpp -o io.o
myPoll.o:
	$(CC) $(CFLAG) myPoll.cpp -o myPoll.o

TARGET = libsocket.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -shared $(LFLAG) $(OBJS) -o $(TARGET)
clean:
	rm -f $(OBJS)

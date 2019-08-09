CC = gcc
CFLAG = -Wall -c -fPIC
LFLAG = 

OBJS = ServerSocket.o Socket.o io.o

OUT=./

ServerSocket.o:
	$(CC) $(CFLAG) ServerSocket.cpp -o ServerSocket.o
Socket.o:
	$(CC) $(CFLAG) Socket.cpp -o Socket.o
io.o:
	$(CC) $(CFLAG) io.cpp -o io.o

TARGET = $(OUT)/libsocket.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -shared $(LFLAG) $(OBJS) -o $(TARGET)
	cp *.h $(OUT)
clean:
	rm -f $(OBJS)

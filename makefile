CC = gcc
CFLAG = -Wall -c -fPIC
LFLAG = 
INCLUDES = -I include
OBJS = src/ServerSocket.o src/Socket.o src/io.o

OUT=./

src/ServerSocket.o:
	$(CC) $(CFLAG) $(INCLUDES) src/ServerSocket.cpp -o src/ServerSocket.o
src/Socket.o:
	$(CC) $(CFLAG) $(INCLUDES) src/Socket.cpp -o src/Socket.o
src/io.o:
	$(CC) $(CFLAG) $(INCLUDES) src/io.cpp -o src/io.o

TARGET = $(OUT)/libsocket.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -shared $(LFLAG) $(OBJS) -o $(TARGET)
	cp *.h $(OUT)
clean:
	rm -f $(OBJS)

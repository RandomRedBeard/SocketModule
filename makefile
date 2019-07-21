CC = gcc
CFLAG = -Wall -c
LFLAG = -std=c++17 -lstdc++ -lpthread -lm

OBJS = 

TARGET = libsocket.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -shared -fPIC -o $(TARGET) *.cpp
clean:
	rm -f $(OBJS)

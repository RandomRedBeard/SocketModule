CC = gcc
CFLAG = -Wall -c
LFLAG = -lstdc++ -std=c++15
TARGET = libsocket.so

OBJS = *.o

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) -shared -o -fPIC $(TARGET) $(OBJS)
CC = gcc
CFLAG = -Wall -c -fPIC
LFLAG = -std=c++17 -lstdc++ -lpthread -lm

OBJS = *.o 

TARGET = libsocket.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) *.cpp
	$(CC) -shared $(LFLAG) $(OBJS) -o $(TARGET)
clean:
	rm -f $(OBJS)

CC=gcc
CFLAGS=-pthread -Wall
TARGET=hello_threads

all: $(TARGET)

$(TARGET): hello_threads.c
	$(CC) $(CFLAGS) -o $(TARGET) hello_threads.c

clean:
	rm -f $(TARGET)

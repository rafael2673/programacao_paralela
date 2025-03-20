CC=gcc
CFLAGS=-pthread -Wall
TARGET=mutex_example

all: $(TARGET)

$(TARGET): mutex_example.c
	$(CC) $(CFLAGS) -o $(TARGET) mutex_example.c

clean:
	rm -f $(TARGET)

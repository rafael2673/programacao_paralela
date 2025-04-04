CFLAGS = -fopenmp

memoryBound: memoryBound.c
	gcc $(CFLAGS) -o memoryBound memoryBound.c

cpuBound: cpuBound.c
	gcc $(CFLAGS) -o cpuBound cpuBound.c -lm

all: memoryBound cpuBound

.PHONY: clean
clean:
	rm -f memoryBound cpuBound

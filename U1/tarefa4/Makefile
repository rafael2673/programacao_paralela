
CFLAGS = -fopenmp

memoryBound: memoryBound.c
	gcc $(CFLAGS) -o memoryBound memoryBound.c

cpuBound: cpuBound.c
	gcc $(CFLAGS) -lm -o cpuBound cpuBound.c

all: memoryBound cpuBound

.PHONY: clean
clean:
	rm -f memoryBound cpuBound

CFLAGS = -fopenmp

2criticalList: 2criticalList.c
	gcc $(CFLAGS) -o 2criticalList 2criticalList.c

nCriticalList: nCriticalList.c
	gcc $(CFLAGS) -o nCriticalList nCriticalList.c -lm

all: 2criticalList nCriticalList

.PHONY: clean
clean:
	rm -f 2criticalList nCriticalList

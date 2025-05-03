CFLAGS = -fopenmp

piEstimation: piEstimation.c
	gcc $(CFLAGS) -o piEstimation piEstimation.c -lm

piEstimation2: piEstimation2.c
	gcc $(CFLAGS) -o piEstimation2 piEstimation2.c -lm

piEstimation3: piEstimation3.c
	gcc $(CFLAGS) -o piEstimation3 piEstimation3.c -lm

all: piEstimation piEstimation2 piEstimation3

.PHONY: clean
clean:
	rm -f piEstimation piEstimation2 piEstimation3

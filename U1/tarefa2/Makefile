CFLAGS = -fopenmp

pipeline: pipeline.c
	gcc $(CFLAGS) -o pipeline pipeline.c

pipeline_O0: pipeline.c
	gcc $(CFLAGS) -O0 -o pipeline_O0 pipeline.c

pipeline_O2: pipeline.c
	gcc $(CFLAGS) -O2 -o pipeline_O2 pipeline.c

pipeline_O3: pipeline.c
	gcc $(CFLAGS) -O3 -o pipeline_O3 pipeline.c

all: pipeline pipeline_O0 pipeline_O2 pipeline_O3

.PHONY: clean
clean:
	rm -f pipeline pipeline_O0 pipeline_O2 pipeline_O3

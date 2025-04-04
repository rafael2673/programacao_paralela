#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

#define ITERATIONS 500000000

int main(int argc, char *argv[]) {
    int threads = argc > 1 ? atoi(argv[1]) : 1;
    omp_set_num_threads(threads);

    double sum = 0.0;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    #pragma omp parallel for reduction(+:sum)
    for (long i = 1; i < ITERATIONS; i++) {
        sum += log(i) * sin(i) * sqrt(i);
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("CPU-bound com %d threads: %.3f segundos\n", threads, elapsed);
    return 0;
}

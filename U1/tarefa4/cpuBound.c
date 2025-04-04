#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

#define DEFAULT_ITERATIONS 100000000

int main(int argc, char *argv[]) {
    int threads = 1;
    long iterations = DEFAULT_ITERATIONS;

    
    if (argc > 1) threads = atoi(argv[1]);
    if (argc > 2) iterations = atol(argv[2]);

    omp_set_num_threads(threads);

    printf("Executando CPU-bound com %d threads e %ld iterações...\n", threads, iterations);

    double sum = 0.0;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    #pragma omp parallel for reduction(+:sum)
    for (long i = 1; i < iterations; i++) {
        sum += log(i) * sin(i) * sqrt(i);
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("CPU-bound com %d threads e %ld iterações: %.3f segundos (soma final = %.2f)\n", threads, iterations, elapsed, sum);
    return 0;
}

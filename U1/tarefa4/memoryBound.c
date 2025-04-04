#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define SIZE 500000000
float *a, *b, *c;

int main(int argc, char *argv[]) {
    int threads = argc > 1 ? atoi(argv[1]) : 1;
    omp_set_num_threads(threads);

    a = malloc(SIZE * sizeof(float));
    b = malloc(SIZE * sizeof(float));
    c = malloc(SIZE * sizeof(float));

    for (long i = 0; i < SIZE; i++) {
        a[i] = i * 0.5f;
        b[i] = i * 1.5f;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    #pragma omp parallel for
    for (long i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Memory-bound com %d threads: %.3f segundos\n", threads, elapsed);

    free(a); free(b); free(c);
    return 0;
}

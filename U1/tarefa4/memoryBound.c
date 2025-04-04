#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>


#define DEFAULT_SIZE 100000000

float *a, *b, *c;

int main(int argc, char *argv[]) {
    int threads = 1;
    long size = DEFAULT_SIZE;

    
    if (argc > 1) threads = atoi(argv[1]);
    if (argc > 2) size = atol(argv[2]);

    omp_set_num_threads(threads);

    printf("Alocando vetores com %ld elementos...\n", size);

    a = malloc(size * sizeof(float));
    b = malloc(size * sizeof(float));
    c = malloc(size * sizeof(float));

    if (a == NULL || b == NULL || c == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return 1;
    }

    for (long i = 0; i < size; i++) {
        a[i] = i * 0.5f;
        b[i] = i * 1.5f;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    #pragma omp parallel for
    for (long i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Memory-bound com %d threads e %ld elementos: %.3f segundos\n", threads, size, elapsed);

    free(a); free(b); free(c);
    return 0;
}

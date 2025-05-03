#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

#define NUM_POINTS 100000000

int main() {
    struct timeval start, end;
    gettimeofday(&start, NULL);

    int num_threads;
    #pragma omp parallel
    {
        #pragma omp single
        num_threads = omp_get_num_threads();
    }

    int *hits = calloc(num_threads, sizeof(int));

    #pragma omp parallel firstprivate(num_threads)
    {
        int tid = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ tid;

        #pragma omp for
        for (int i = 0; i < NUM_POINTS; i++) {
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;
            if (x * x + y * y <= 1.0)
                hits[tid]++;
        }
    }

    int inside_circle = 0;
    for (int i = 0; i < num_threads; i++) {
        inside_circle += hits[i];
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    double pi = 4.0 * inside_circle / NUM_POINTS;

    printf("Estimativa de pi (rand versão 2): %.6f\n", pi);
    printf("Tempo (rand versão 2): %.6f segundos\n", elapsed);
    free(hits);
    return 0;
}

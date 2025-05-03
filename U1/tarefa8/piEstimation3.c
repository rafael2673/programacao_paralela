#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define NUM_POINTS 100000000

int main() {
    int inside_circle = 0;
    struct timeval start, end;
    unsigned int seed; // Necessário para private()

    gettimeofday(&start, NULL);

    #pragma omp parallel private(seed)
    {
        seed = omp_get_thread_num(); // Inicialização específica por thread
        int local_hits = 0;

        #pragma omp for
        for (int i = 0; i < NUM_POINTS; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0)
                local_hits++;
        }

        #pragma omp critical
        inside_circle += local_hits;
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    double pi = 4.0 * inside_circle / NUM_POINTS;

    printf("Estimativa de pi (rand_r versão 1): %.6f\n", pi);
    printf("Tempo (rand_r versão 1): %.6f segundos\n", elapsed);
    return 0;
}

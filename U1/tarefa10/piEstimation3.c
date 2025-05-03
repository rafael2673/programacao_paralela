#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define NUM_POINTS 100000000

int main() {
    int inside_circle = 0;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    #pragma omp parallel reduction(+:inside_circle)
    {
        unsigned int seed = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < NUM_POINTS; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x*x + y*y <= 1.0)
                inside_circle++;
        }
    }

    gettimeofday(&end, NULL);
    double pi = 4.0 * inside_circle / NUM_POINTS;
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1e6;
    printf("Reduction→ π = %.6f, tempo = %.3fs\n", pi, elapsed);
    return 0;
}

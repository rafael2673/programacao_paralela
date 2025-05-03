#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

#define NUM_POINTS 100000000

int main() {
    int inside_circle = 0;
    struct timeval start, end;
    unsigned int seed; 

    gettimeofday(&start, NULL);

    #pragma omp parallel private(seed)
    {
        seed = time(NULL) ^ omp_get_thread_num();
        int local_hits = 0;

        #pragma omp for
        for (int i = 0; i < NUM_POINTS; i++) {
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;
            if (x * x + y * y <= 1.0)
                local_hits++;
        }

        #pragma omp atomic
        inside_circle += local_hits;
    }

    gettimeofday(&end, NULL);
    double pi = 4.0 * inside_circle / NUM_POINTS;
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1e6;
    printf("Atomic → π = %.6f, tempo = %.3fs\n", pi, elapsed);
    return 0;
}

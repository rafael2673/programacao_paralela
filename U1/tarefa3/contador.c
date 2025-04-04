#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define PI_REAL 3.14159265358979323846

int main() {
    int n;
    double pi_approx = 0.0;
    struct timeval start, end;

    printf("Digite o número de iterações: ");
    if (scanf("%d", &n) != 1) {
        printf("Erro na leitura do número de iterações.\n");
        return 1;
    }

    gettimeofday(&start, NULL);
    for (int k = 0; k < n; k++) {
        pi_approx += (k % 2 == 0 ? 1.0 : -1.0) / (2 * k + 1); // Substitui pow(-1, k) por operação mais eficiente
    }
    pi_approx *= 4;
    gettimeofday(&end, NULL);

    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    printf("Aproximação de π: %.15f\n", pi_approx);
    printf("Erro absoluto: %.15f\n", fabs(PI_REAL - pi_approx));
    printf("Tempo de execução: %.6f segundos\n", time_taken);

    return 0;
}
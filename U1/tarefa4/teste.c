#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define PI_REAL 3.14159265358979323846

// Função para calcular a aproximação de PI usando a série de Leibniz
double calculate_pi_leibniz(long iterations) {
    double pi = 0.0;
    for (long i = 0; i < iterations; i++) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
        pi += term;
    }
    return pi * 4;
}

int main() {
    long iterations;
    struct timeval start, stop;

    printf("Digite o número de iterações: ");
    scanf("%ld", &iterations);

    gettimeofday(&start, NULL);
    double pi_approx = calculate_pi_leibniz(iterations);
    gettimeofday(&stop, NULL);

    double elapsed_time = (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;

    printf("Aproximação de PI: %.15f\n", pi_approx);
    printf("Erro absoluto: %.15f\n", fabs(pi_approx - PI_REAL));
    printf("Tempo de execução: %.3f ms\n", elapsed_time);

    return 0;
}


/*

Fazer um gráfico de quantidade de iterações x o número de dígitos corretos de pi

Fazer uma tabela com os resultados obtidos a partir desse código.

*/
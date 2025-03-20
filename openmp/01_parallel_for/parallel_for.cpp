/**
 * Exemplo de paralelização de loops usando OpenMP
 * Este programa calcula a soma dos elementos de um array
 */

#include <iostream>
#include <omp.h>
#include <vector>

#define ARRAY_SIZE 100000000

int main() {
    std::vector<int> numbers(ARRAY_SIZE);
    long long sum = 0;

    // Inicializar o array
    #pragma omp parallel for
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = i + 1;
    }

    // Medir tempo de execução
    double start_time = omp_get_wtime();

    // Calcular a soma em paralelo
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += numbers[i];
    }

    double end_time = omp_get_wtime();

    std::cout << "Soma total: " << sum << std::endl;
    std::cout << "Tempo de execução: " << end_time - start_time << " segundos" << std::endl;

    return 0;
}

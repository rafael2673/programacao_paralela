/**
 * Exemplo de seções paralelas usando OpenMP
 * Este programa demonstra como executar diferentes tarefas em paralelo
 */

#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>

void task_a(std::vector<double>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = std::sin(i);
    }
}

void task_b(std::vector<double>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = std::cos(i);
    }
}

void task_c(std::vector<double>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = std::tan(i);
    }
}

int main() {
    const int SIZE = 1000000;
    std::vector<double> data_a(SIZE);
    std::vector<double> data_b(SIZE);
    std::vector<double> data_c(SIZE);

    double start_time = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            std::cout << "Executando task_a na thread " << omp_get_thread_num() << std::endl;
            task_a(data_a);
        }

        #pragma omp section
        {
            std::cout << "Executando task_b na thread " << omp_get_thread_num() << std::endl;
            task_b(data_b);
        }

        #pragma omp section
        {
            std::cout << "Executando task_c na thread " << omp_get_thread_num() << std::endl;
            task_c(data_c);
        }
    }

    double end_time = omp_get_wtime();

    std::cout << "Todas as tarefas completadas em " << end_time - start_time << " segundos" << std::endl;

    return 0;
}

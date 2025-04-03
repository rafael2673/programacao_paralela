#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <sys/time.h>

using namespace std;

int main() {
    int n, target, count1 = 0, count2 = 0; // count1 e count2 inicializados corretamente

    cout << "Digite a quantidade de números aleatórios a serem gerados: ";
    cin >> n;
    cout << "Digite o número que deseja contar: ";
    cin >> target;

    struct timeval start1, stop1, start2, stop2;

    vector<int> numbers(n, 0); // Inicializa todo o vetor com 0

    srand(time(0));

    // Gerar números aleatórios
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        numbers[i] = rand() % 100; // Números de 0 a 99
    }


    gettimeofday(&start1, NULL); 
    // Contagem sem OpenMP (sequencial)
    for (int i = 0; i < n; i++) {
        if (numbers[i] == target) {
            count1++; // Contagem normal
        }
    }
    cout << "O número " << target << " aparece (sem OpenMP) " << count1 << " vezes.\n";
    gettimeofday(&stop1, NULL);


    gettimeofday(&start2, NULL);
    // Contagem com OpenMP
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (numbers[i] == target) {
            #pragma omp critical
            count2++; // Não precisa de #pragma omp critical
        }
    }
    cout << "O número " << target << " aparece (com OpenMP) " << count2 << " vezes.\n";

    gettimeofday(&stop2, NULL); // Finaliza a contagem do tempo

    int num_threads = omp_get_num_threads();
    cout << "A quantidade de threads é: " << num_threads << endl;
    double elapsed_time1 = (stop1.tv_sec - start1.tv_sec) * 1000.0 + (stop1.tv_usec - start1.tv_usec) / 1000.0;
    cout << "Tempo total de execução (sem OpenMP): " << elapsed_time1 << " ms" << endl;
    
    double elapsed_time2 = (stop2.tv_sec - start2.tv_sec) * 1000.0 + (stop2.tv_usec - start2.tv_usec) / 1000.0;
    
    cout << "Tempo total de execução (com OpenMP): " << elapsed_time2 << " ms" << endl;

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>


double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main() {
    int64_t N;
    printf("Digite o tamanho do vetor: ");
    scanf("%ld", &N);

    int64_t *vetor = (int64_t *)malloc(N * sizeof(int64_t));
    if (vetor == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }
    double inicio, fim;

    // Inicialização do vetor
    inicio = get_time();
    for (int64_t i = 0; i < N; i++) {
        vetor[i] = i;
    }
    fim = get_time();
    printf("Tempo de inicialização: %f s\n", fim - inicio);

    // Soma acumulativa com dependência
    int64_t soma = 0;
    inicio = get_time();
    for (int64_t i = 0; i < N; i++) {
        soma += vetor[i];
    }
    fim = get_time();
    printf("Tempo da soma acumulativa: %f s\n", fim - inicio);
    printf("Resultado da soma acumulativa: %ld\n", soma);

    // Soma sem dependência (uso de variáveis intermediárias)
    int64_t soma1 = 0, soma2 = 0;
    inicio = get_time();
    for (int64_t i = 0; i < N; i += 2) {
        soma1 += vetor[i];
        if (i + 1 < N) soma2 += vetor[i + 1];
    }
    soma = soma1 + soma2;
    fim = get_time();
    printf("Tempo da soma paralela: %f s\n", fim - inicio);
    printf("Resultado da soma paralela: %ld\n", soma);

    free(vetor);
    return 0;
}
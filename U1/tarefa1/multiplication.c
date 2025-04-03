#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Função para multiplicação de matriz por vetor (acesso por linhas)
void multiplyMatrixVectorRows(int m, int n, double **matrix, double *vector, double *result) {
    for (int i = 0; i < m; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

// Função para multiplicação de matriz por vetor (acesso por colunas)
void multiplyMatrixVectorCols(int m, int n, double **matrix, double *vector, double *result) {
    for (int i = 0; i < m; i++) {
        result[i] = 0.0;
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
int m, n;
struct timeval start, stop;
    printf("Digite o número de linhas da matriz: ");
    scanf("%d", &m);
    printf("Digite o número de colunas da matriz: ");
    scanf("%d", &n);

    // Alocar matriz e vetor
    double **matrix = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    double *vector = (double *)malloc(n * sizeof(double));
    double *result = (double *)malloc(m * sizeof(double));

    // Inicializar matriz e vetor
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < n; i++) {
        vector[i] = rand() % 10;
    }

    // Multiplicação com acesso por linhas
    gettimeofday(&start, NULL);
    multiplyMatrixVectorRows(m, n, matrix, vector, result);
    gettimeofday(&stop, NULL);
    double elapsed_rows = (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;
    printf("Tempo (Acesso por linhas): %.3f ms\n", elapsed_rows);

    // Multiplicação com acesso por colunas
    gettimeofday(&start, NULL);
    multiplyMatrixVectorCols(m, n, matrix, vector, result);
    gettimeofday(&stop, NULL);
    double elapsed_cols = (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;
    printf("Tempo (Acesso por colunas): %.3f ms\n", elapsed_cols);

    // Liberar memória
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}
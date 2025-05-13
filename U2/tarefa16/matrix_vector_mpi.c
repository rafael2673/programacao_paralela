#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void fill_matrix(double *A, int M, int N) {
    for (int i = 0; i < M * N; ++i) {
        A[i] = 1.0;  
    }
}

void fill_vector(double *x, int N) {
    for (int i = 0; i < N; ++i) {
        x[i] = 1.0;  
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int M = 8;  
    int N = 4;  

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (M % size != 0) {
        if (rank == 0) {
            printf("Erro: M deve ser divisível por número de processos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int local_rows = M / size;
    double *A = NULL;
    double *x = (double *)malloc(N * sizeof(double));
    double *local_A = (double *)malloc(local_rows * N * sizeof(double));
    double *local_y = (double *)malloc(local_rows * sizeof(double));
    double *y = NULL;

    if (rank == 0) {
        A = (double *)malloc(M * N * sizeof(double));
        y = (double *)malloc(M * sizeof(double));
        fill_matrix(A, M, N);
        fill_vector(x, N);
    }

    double start_time = MPI_Wtime();

    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, local_rows * N, MPI_DOUBLE, local_A, local_rows * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_rows; ++i) {
        local_y[i] = 0.0;
        for (int j = 0; j < N; ++j) {
            local_y[i] += local_A[i * N + j] * x[j];
        }
    }

    MPI_Gather(local_y, local_rows, MPI_DOUBLE, y, local_rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Resultado y = A*x:\n");
        for (int i = 0; i < M; ++i) {
            printf("%f ", y[i]);
        }
        printf("\nTempo de execução: %f segundos\n", end_time - start_time);
    }

    free(x);
    free(local_A);
    free(local_y);
    if (rank == 0) {
        free(A);
        free(y);
    }

    MPI_Finalize();
    return 0;
}

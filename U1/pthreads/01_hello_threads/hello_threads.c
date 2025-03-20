/**
 * Exemplo básico de criação de threads usando pthreads
 * Este programa cria múltiplas threads que imprimem uma mensagem
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

// Estrutura para passar dados para a thread
typedef struct {
    int thread_id;
} thread_data_t;

// Função que será executada por cada thread
void* print_hello(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    printf("Olá da thread %d!\n", data->thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int rc;

    // Criar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        printf("Criando thread %d\n", i);
        rc = pthread_create(&threads[i], NULL, print_hello, (void*)&thread_data[i]);
        
        if (rc) {
            printf("ERRO: código de retorno de pthread_create() é %d\n", rc);
            exit(-1);
        }
    }

    // Aguardar todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Todas as threads terminaram!\n");
    pthread_exit(NULL);
}

/**
 * Exemplo de uso de mutex para proteção de recursos compartilhados
 * Este programa demonstra como proteger uma variável compartilhada
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 1000000

// Variável compartilhada
long long shared_counter = 0;

// Mutex para proteger a variável compartilhada
pthread_mutex_t counter_mutex;

void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        // Início da seção crítica
        pthread_mutex_lock(&counter_mutex);
        shared_counter++;
        pthread_mutex_unlock(&counter_mutex);
        // Fim da seção crítica
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;

    // Inicializar o mutex
    pthread_mutex_init(&counter_mutex, NULL);

    // Criar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Criando thread %d\n", i);
        rc = pthread_create(&threads[i], NULL, increment_counter, NULL);
        if (rc) {
            printf("ERRO: código de retorno de pthread_create() é %d\n", rc);
            exit(-1);
        }
    }

    // Aguardar todas as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor final do contador: %lld\n", shared_counter);
    printf("Valor esperado: %lld\n", (long long)NUM_THREADS * NUM_INCREMENTS);

    // Destruir o mutex
    pthread_mutex_destroy(&counter_mutex);
    pthread_exit(NULL);
}

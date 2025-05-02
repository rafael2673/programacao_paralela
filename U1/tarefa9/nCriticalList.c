#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void insert(Node** head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

void print_list(Node* head) {
    while (head) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int num_lists, num_insertions;

    printf("Número de listas: ");
    scanf("%d", &num_lists);
    printf("Número de inserções: ");
    scanf("%d", &num_insertions);

    // Inicializa listas e locks
    Node** lists = malloc(num_lists * sizeof(Node*));
    omp_lock_t* locks = malloc(num_lists * sizeof(omp_lock_t));
    for (int i = 0; i < num_lists; i++) {
        lists[i] = NULL;
        omp_init_lock(&locks[i]);
    }

    srand(time(NULL));

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < num_insertions; i++) {
                #pragma omp task firstprivate(i)
                {
                    int value = rand() % 1000;
                    int index = rand() % num_lists;

                    omp_set_lock(&locks[index]);
                    insert(&lists[index], value);
                    omp_unset_lock(&locks[index]);
                }
            }
        }
    }

    // Exibe o conteúdo de cada lista
    for (int i = 0; i < num_lists; i++) {
        printf("Lista %d:\n", i + 1);
        print_list(lists[i]);
    }

    // Libera os locks
    for (int i = 0; i < num_lists; i++) {
        omp_destroy_lock(&locks[i]);
    }

    free(lists);
    free(locks);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
    Node* list1 = NULL;
    Node* list2 = NULL;
    int N = 100;

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < N; i++) {
                #pragma omp task firstprivate(i)
                {
                    int value = rand() % 1000;
                    int choice = rand() % 2;

                    if (choice == 0) {
                        #pragma omp critical(list1)
                        insert(&list1, value);
                    } else {
                        #pragma omp critical(list2)
                        insert(&list2, value);
                    }
                }
            }
        }
    }

    printf("List 1:\n");
    print_list(list1);
    printf("List 2:\n");
    print_list(list2);

    return 0;
}

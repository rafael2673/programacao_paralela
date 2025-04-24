#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct Node {
    char filename[50];
    struct Node* next;
} Node;

Node* create_list(int n) {
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        sprintf(new_node->filename, "file_%d.txt", i);
        new_node->next = head;
        head = new_node;
    }
    return head;
}

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = create_list(10);

    #pragma omp parallel
    {
        #pragma omp single
        {
            Node* current = head;
            while (current) {
                #pragma omp task firstprivate(current)
                {
                    int tid = omp_get_thread_num();
                    printf("Processing %s by thread %d\n", current->filename, tid);
                }
                current = current->next;
            }
        }
    }

    free_list(head);
    return 0;
}

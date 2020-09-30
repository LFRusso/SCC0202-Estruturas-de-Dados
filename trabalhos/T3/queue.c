#include "queue.h"

// Construtor da fila
pQueue* queueBuild(int max_size) {
    pQueue* q = malloc(sizeof(pQueue));
    q->max_size = max_size;
    q->size = 0;

    q->elements = calloc(max_size,sizeof(Node));
    q->elements[0].priority=-1;
    return q;
}

// Insere um elemento na fila de prioridade, caso ela não esteja cheia
int queueInsert(pQueue* q, Node elem, int priority) {
    if (queueIsFull(q)) return 0;
    
    int n=q->size -1;
    while (n >= 0 && q->elements[n].priority >= priority) {
        q->elements[n+1] = q->elements[n];
        n--;
    }

    strcpy(q->elements[n+1].name, elem.name);
    q->elements[n+1].age = elem.age;
    q->elements[n+1].condition = elem.condition;
    q->elements[n+1].priority = priority;
    q->size++;
    return 1;
}

// Remove elemento que está em primeiro na fila, caso ela não esteja vazia
int queuePop(pQueue* q) {
    if (queueIsEmpty(q)) return 0;
    Node elem = q->elements[q->size-1];
    printf("%s %d %d\n", elem.name, elem.age, elem.condition);

    q->size--; 
    return 1;
}

// Libera memória
void queueDestroy(pQueue* q) { 
    free(q->elements);
    free(q);
    return;
}

// Checa se a fila está cheia
int queueIsFull(pQueue* q) {
    if (q->size == q->max_size) {
        printf("FILA CHEIA\n");
        return 1;
    }
    return 0;
}

// Checa se a fila está vazia
int queueIsEmpty(pQueue* q) {
    if (q->size == 0) {
        printf("FILA VAZIA\n");
        return 1;
    }
    return 0;
}

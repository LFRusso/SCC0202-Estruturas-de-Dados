#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[30];
    int age;
    int condition;
    int priority;
} Node;

typedef struct prioroty_queue {
   int max_size;
   int size;
   Node* elements;
} pQueue;


pQueue* queueBuild(int max_size);
int queueInsert(pQueue* q, Node pacient, int priority);
int queuePop(pQueue* q);
void queueDestroy(pQueue* q);
int queueIsEmpty(pQueue* q);
int queueIsFull(pQueue* q);

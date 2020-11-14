#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    struct Node* prox;
    struct Node* back;
    int chave;
    int tempo;
} Node;

typedef struct Backwardlist {
    struct Node* ini;
    struct Node* fim;
    int tempo;
    int tamanho;
} Backwardlist;


Backwardlist* listBuild();
int listInsert(Backwardlist* list, int n, int j);
int listRemove(Backwardlist* list, int n);
int listDestroy(Backwardlist* list);
int listPrint(Backwardlist* list);
int listIdxOfElem(Backwardlist* list, Node* elem);

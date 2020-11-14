#include "backwardlist.h"

// Inicializa uma lista backward
Backwardlist* listBuild() {
    Backwardlist* list = malloc(sizeof(Backwardlist));
    list->ini = NULL;
    list->fim = NULL;
    list->tempo = 0;
    list->tamanho = 0;

    return list;
}


// Insere elemento na lista
int listInsert(Backwardlist* list, int n, int j) {
    
    Node* new_node = malloc(sizeof(Node));
    new_node->tempo = list->tempo;
    new_node->chave = n;
    new_node->prox = NULL;
    list->tamanho++;
    list->tempo++;
    
    
    // Inserindo elemento na lista vazia
    if (list->tamanho == 1) {
        new_node->prox = NULL;
        new_node->back = NULL;
        list->ini = new_node;
        list->fim = new_node;
        return 1;
    }
    
    // Caso em que já existem outros elementos nela
    if (j==0) {
        new_node->back = NULL;
    } else  {
        Node* aux = list->ini;
        for (int i=1; i < list->tamanho - j; i++) {
            aux = aux->prox;
        }
        new_node->back = aux;
    }

    list->fim->prox = new_node;
    list->fim = new_node;
    return 1;
}


// Remove um elemento com a chave especificada da lista 
int listRemove(Backwardlist* list, int n) {
    if (list->tamanho == 0) return 0;
    list->tamanho--;
    list->tempo++;
    
    // Buscando elemento com a chave solicitada
    Node* query_node = list->ini;
    while(query_node->chave != n && query_node != list->fim) {
        query_node = query_node->prox;
    }
    if (query_node->chave != n) {
        printf("Chave não encontrada\n");
        return 0;
    }

    // Fazendo com que elementos que apontavam para ele
    // agora apontem para NULL
    Node* aux = query_node;
    while(aux != NULL) {
        if (aux->back == query_node) {
            aux->back = NULL;
        }
        aux = aux->prox;
    }


    // Fazendo com que elemento anterior ao removido aponte
    // para o próximo
    if (query_node == list->ini) {
        list->ini = query_node->prox;
    } else {
        aux = list->ini;
        Node* prev = aux;
        while (aux != NULL) {
            if (aux == query_node) {
                prev->prox  = query_node->prox;
            }
            prev = aux;
            aux = aux->prox;
        }
    }
    
    free(query_node);
    return 1;
}   


// Encontra o índice de um dado elemento da lista
int listIdxOfElem(Backwardlist* list, Node* elem) {
    Node* aux = list->ini;
    int idx = 0;
    while (aux != NULL) {
        if (aux == elem) {
            return idx;
        }
        aux = aux->prox;
        idx++;
    }

    return -1;
}


// Imprime a lista no formato solicitado
int listPrint(Backwardlist* list) {
    if (list->tamanho == 0) {
        printf("-1\n");
        return 0;
    }

    int idx;
    Node* aux = list->ini;
    while (aux != NULL) {
        printf("[%d,%d", aux->chave, aux->tempo);    
        if (aux->back != NULL) {
            idx = listIdxOfElem(list, aux->back);
            printf(",%d", idx);
        }
        printf("] ");

        aux = aux->prox;
    }
    printf("\n");
    return 1;
}


// Desaloca memória
int listDestroy(Backwardlist* list) {
    if (list->tamanho == 0){
        free(list);
        return 1;
    }
    
    Node* aux1 = list->ini;
    Node* aux2 = list->ini;
    while (aux2 != NULL) {
        aux1 = aux2;
        aux2 = aux1->prox;
        free(aux1);
    }
    free(list);
    return 1;
}

// Luiz Fernando S E Santos - 10892680

#include "c_list.h"


// Criação da lista
c_list* listBuild() {
    c_list* list = malloc(sizeof(c_list)); 
    *list = NULL;
    return list;
}

// Insere um elemento na lista, com seu respectivo ID
int listInsert(c_list* list, int elem_id) {
    elem* new_elem = malloc(sizeof(elem));

    if (*list==NULL) {
        *list = new_elem;
    }
    
    new_elem->next = *list;
    new_elem->id = elem_id;
    
    elem* node = *list;
    while(node->next != *list) {
        node = node->next;
    }
    node->next = new_elem;
    return 1;
}  

// Imprime os elementos da lista por ordem que foram inseridos
void listPrint(c_list* list) {
    if (list==NULL || *list==NULL)
        return;

    elem* node = *list;
    int i=0;
    do{
        printf("Elem %d: %d\n", i, node->id);
        i++;
        node = node->next;
    }while(node != *list);

    return;
}

// Remove o último elemento inserido na lista
int listPop(c_list* list) {
    if (list==NULL || *list==NULL)
        return 0;

    elem* aux = *list;
    elem* last = aux->next;

    while (last->next != *list) {
        aux = aux->next;
        last = aux->next;
    }
    aux->next = *list;
    
    last->next = NULL;
    free(last);
    return 1;
}


// Remove o elemento com dado ID da lista
int listDelId(c_list* list, int id) {
    if (list==NULL || *list==NULL)
        return 0;

    elem* aux = *list;
    elem* prev = *list;
    while (aux->next != *list) {
        prev = aux;
        aux = aux->next;
        if (aux->id == id) {
            // Checando cada elemento para ver se é o com o ID desejado
            prev->next = aux->next;
            aux->next = NULL;
            free(aux);
            return 1;
        }
    }
    
    // Caso de borda: lista com apenas um elemento
    if (aux->id == id) {
        *list = NULL;
        list = NULL;
        free(aux);
        return 1;
    }

    return 0;
}



// Deleta determinado índice da lista circular
int listDelIdx(c_list* list, int idx) {
    if (list==NULL || *list==NULL)
        return -1;
    
    idx==0 ? idx=listSize(list) : idx;
    elem* aux = *list;
    elem* prev = *list;
    for (int i=0; i<idx; i++) {
        prev = aux;
        aux = aux->next;
    }

    prev->next = aux->next;
    if(aux == *list) {
        *list = aux->next;
    }

    int next_id = aux->next->id;
    free(aux);
    return next_id;
}


// Recebe uma lista circular e retorna o número de elementos
int listSize(c_list* list) {
    if (list==NULL || *list==NULL)
        return 0;
    
    elem* node = *list;
    int size=0;
    do {
        size++;
        node = node->next;
    } while(node != *list);
    return size;
}


// Desaloca list e todos seus elementos
int listDestroy(c_list* list) {
    if (list==NULL || *list==NULL) {
        free(list);
        return 0;
    }
    elem* node = *list;
    elem* aux = *list;
    while((*list) != node->next) {
        aux = node;
        node = node->next;
        free(aux);
    }

    free(node);
    free(list);
    return 1;
}


// Retorna primeira ocorrência de um id dentro da lista
// se não encontrado, retorna -1
int findId(c_list* list, int id) {
    if (list==NULL || *list==NULL) 
        return -1;

    elem* node = *list;
    int idx=0;
    do {
        if (node->id == id) {
            return idx;
        }
        idx++;
        node = node->next;
    } while (node != *list);


    return -1;
}

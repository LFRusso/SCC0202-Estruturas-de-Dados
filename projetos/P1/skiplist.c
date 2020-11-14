#include "skiplist.h"

// Cria um novo nó para a skiplist
node* newNode(char* value, info* data, int level) {
    node* new_node = malloc(sizeof(node));
    
    new_node->data = data;
    new_node->value = value;
    new_node->next = malloc((level+1)*sizeof(node*));
    for (int i=0; i<(level+1); i++) {
        new_node->next[i] = NULL;
    }
    return new_node;
}

// Criação da skiplist
skiplist* slCreate(int maxlevel) {
    skiplist* sl = malloc(sizeof(skiplist));
    sl->maxlevel = maxlevel;
    sl->level = 0;

    sl->head = newNode("0", NULL, maxlevel);

    return sl;
}

// Busca um valor dentro da skiplist e imprime a descriçaõ armazenada dos dados
int slSearch(skiplist* sl, char* value) {
    if (sl==NULL) return 0;
    
    node* current = sl->head;

    for (int i=sl->level; i>=0; i--) {
        while (current->next[i] != NULL && 
               strcmp(current->next[i]->value, value) < 0)
            current = current->next[i];
    }

    current = current->next[0];
    if (current != NULL && strcmp(current->value,value)==0) {
        printf("%s %s\n", current->value, current->data->desc);
        return 1;
    };

    printf("OPERACAO INVALIDA\n");
    return 0;
}

// Busca um valor dentro da skiplist e altera sua descrição
int slChange(skiplist* sl, char* value, char* new_desc) {
    if (sl==NULL) return 0;
    
    node* current = sl->head;

    for (int i=sl->level; i>=0; i--) {
        while (current->next[i] != NULL && 
               strcmp(current->next[i]->value, value) < 0)
            current = current->next[i];
    }

    if (current->next[0] != NULL && strcmp(current->next[0]->value,value)==0) {
        free(current->next[0]->data->desc); 
        current->next[0]->data->desc = new_desc; 
        return 1;
    }

    printf("OPERACAO INVALIDA\n");
    return 0;
}


// Imprime todas as palavras começando com o caractére start_ch 
int slPrint(skiplist* sl, char* start_ch) {
    if (sl==NULL) return 0;
    
    node* current = sl->head;

    for (int i=sl->level; i>=0; i--) {
        while (current->next[i] != NULL && 
               strcmp(current->next[i]->value, start_ch) < 0)
            current = current->next[i];
    }
    current = current->next[0];
    
    if (current->next[0] != NULL && start_ch[0] == current->next[0]->value[0]) {
        // Obtém letra seguinte do alfabeto à solicitada
        char* next_ch = calloc(2, sizeof(char));
        next_ch[0] = start_ch[0]+1;

        // Buscando e imprimindo todas as entradas encontradas que começam com a letra solicitada
        do {
            printf("%s %s\n", current->data->word, current->data->desc);
            current = current->next[0];
        } while (current != NULL && current->value[0] == start_ch[0]);
        
        free(next_ch);
        return 1;
    }

    printf("NAO HA PALAVRAS INICIADAS POR %s\n", start_ch);
    return 0;
}


// Seleciona um nível aleatório abaixo do máximo
int randLvL(int max) {
    float p = (float) rand()/RAND_MAX;
    int lvl = 0;
    while (p < 0.5 && lvl<max) {
        lvl++;
        p = (float) rand()/RAND_MAX;
    }

    return lvl;
}


// Insere um novo nó na skiplist
int slInsert(skiplist* sl, info* data) {
    if (sl==NULL) return 0;

    node* current = sl->head;
    node** aux_insert = malloc((sl->maxlevel+1)*sizeof(node*));
    for (int i=0; i<=sl->maxlevel; i++) {
        aux_insert[i] = NULL;
    }
   
    char* value = data->word;
    for (int i=sl->level; i>=0; i--) {
        while (current->next[i] != NULL && 
                strcmp(current->next[i]->value, value)< 0) {
            current = current->next[i];
        }
        aux_insert[i] = current;
    }

    current = current->next[0];

    if (current == NULL || strcmp(current->value,value) != 0) {
        int new_level = randLvL(sl->maxlevel);

        node* new_node = newNode(value, data, new_level);
        if (new_node == NULL) {
            free(aux_insert);
            return 0;
        }

        if (new_level > sl->level) {
            for (int i=sl->level+1; i<=new_level; i++) {
                aux_insert[i] = sl->head;
            }
            sl->level = new_level;
        }

        for (int i=0; i<=new_level; i++) {
            new_node->next[i] = aux_insert[i]->next[i];
            aux_insert[i]->next[i] = new_node;
        }
        free(aux_insert);
        
        return 1;
    }

    printf("OPERACAO INVALIDA\n");
    return 0;
}


// Remove o nó contendo um valor da lista
int slRemove(skiplist* sl, char* value) {
    if (sl==NULL) return 0;

    node* current = sl->head;
    node** aux_remove = malloc((sl->maxlevel+1)*sizeof(node*));
    for (int i=0; i<=sl->maxlevel; i++) {
        aux_remove[i] = NULL;
    }
    
    for (int i=sl->level; i>=0; i--) {
        while (current->next[i] != NULL && 
                strcmp(current->next[i]->value,value) < 0) {
            current = current->next[i];
        }
        aux_remove[i] = current;
    }

    current = current->next[0];

    if (current != NULL && strcmp(current->value, value)==0) {
        
        for (int i=0; i<=sl->level; i++) {
            if (aux_remove[i]->next[i] != current) break;
            aux_remove[i]->next[i] = current->next[i];
        }
        
        while (sl->level > 0 && sl->head->next[sl->level] == NULL) {
            sl->level--;
        }


        if (current->data != NULL) {
            free(current->data->word);
            free(current->data->desc);
            free(current->data);
        }

        free(current->next);
        free(current);
        free(aux_remove);
        return 1;
    }

    printf("OPERACAO INVALIDA\n");
    free(aux_remove);
    return 0;
}

// Libera memória referente à skiplist
int slDelete(skiplist* sl) {
    if (sl==NULL) return 0;
    
    node* aux_free;
    node* current = sl->head->next[0];
    while (current != NULL) {
        aux_free = current;
        current = current->next[0];

        
        if (aux_free->data != NULL) {
            free(aux_free->data->word);
            free(aux_free->data->desc);
            free(aux_free->data);
        }
        
        free(aux_free->next);
        free(aux_free);
    }

    free(sl->head->next);
    free(sl->head);
    free(sl);
    return 1;
}

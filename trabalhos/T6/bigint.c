#include "bigint.h"


Bigint* create() {
    Bigint* number = malloc(sizeof(Bigint));
    number->head = NULL;
    number->tail = NULL;
    number->size = 0;
    number->negative = 0;
    return number;
}


// Remove os zeros à esquerda
int format(Bigint* number) {
    Node* node = number->head;
    Node* node_aux = node;
    while (node->n == 0) {
        node_aux = node;
        node = node->next;
        free(node_aux);
        number->size--;
    }
    number->head = node;
    return 1;
}

// Lê um Bigint
int read(Bigint* number, FILE* input) {
    if (number == NULL) return 0;
    
    Node* first_node = malloc(sizeof(Node));
    first_node->prev = NULL;
    Node* aux1 = first_node;
    Node* aux2 = aux1;

    char ch;
    int n = 0;
    ch = getc(input);
    if (ch == '-') {
        number->negative = 1;
        ch = getc(input);
    } else {
        number->negative = 0;
    }
    while (ch != ' ' && ch != '\n' && ch != EOF && ch != '\r') {
        aux1 = aux2;
        number->size++;
        aux1->n = atoi(&ch);
        n++;

        aux1->next = (Node*) malloc(sizeof(Node));
        aux2 = aux1->next;
        aux2->prev = aux1;
        ch = getc(input);
    }
    free(aux2);
    
    number->head = first_node;
    number->tail = aux1;
    format(number);
    return 1;
}



// Checa se a == b
int eql(Bigint* a, Bigint* b) {
    if (a->negative != b->negative) return 0;
    if (a->size != b->size) return 0;
    
    int n = a->size;
    Node* node_a = a->head;    
    Node* node_b = b->head;
    
    for (int i=0; i<n; i++) {
        if (node_a->n != node_b->n) return 0;
        
        node_b = node_b->next;
        node_a = node_a->next;
    }

    return 1;
}


// Checa se a < b
int sml(Bigint* a, Bigint* b) {
    if (a->negative && !b->negative) return 1;
    if (b->negative && !a->negative) return 0;
    if (eql(a, b)) return 0;

    if (!a->negative && !b->negative) {
        if (a->size > b->size) return 0;
        if (a->size < b->size) return 1;
        
        int n = a->size;
        Node* node_a = a->head;
        Node* node_b = b->head;
        for (int i=0; i<n; i++) {
            if (node_a->n < node_b->n) return 1;
            if (node_a->n > node_b->n) return 0;
            node_a = node_a->next;
            node_b = node_b->next;
        }
        return 0;
    }

    if (a->negative && b->negative) {
        if (a->size > b->size) return 1;
        if (a->size < b->size) return 0;
        
        int n = a->size;
        Node* node_a = a->head;
        Node* node_b = b->head;
        for (int i=0; i<n; i++) {
            if (node_a->n < node_b->n) return 0;
            if (node_a->n > node_b->n) return 1;
            node_a = node_a->next;
            node_b = node_b->next;
        }
        return 1;
    } 
    
    return 0;
}


// Checa se a < b
int big(Bigint* a, Bigint* b) {
    if (eql(a, b)) return 0;
    return !sml(a, b);
}


// Obtém o valor absoluto de um bigint
Bigint* absolute(Bigint* number) {
    Bigint* absolute = create();
    absolute->size = number->size;
    absolute->negative = 0;
    Node* copy = number->head;
    Node* paste = malloc(sizeof(Node));
    Node* paste_aux = paste;
    paste->prev = NULL;
    absolute->head = paste;
    for (int i=0; i<number->size; i++) {
        paste = paste_aux;
        paste->n = copy->n;
        copy = copy->next;
        paste->next = malloc(sizeof(Node));
        paste_aux = paste->next;
        paste_aux->prev = paste;
    }
    free(paste_aux);
    paste->next = NULL;
    absolute->tail = paste;

    return absolute;
}

// Soma dos numeros Bigint a e b
Bigint* sum(Bigint* a, Bigint* b) {
    Bigint* result = create();
    int negative = 0;
    int neg_a = 0;
    int neg_b = 0;

    // Casos em que o resultado será negativo
    if (a->negative && b->negative){
        negative = 1;
    } 
    if (!a->negative && b->negative) {
        Bigint* tmp1 = absolute(b);
        if (big(tmp1, a)) {
            neg_a = 1;
            negative = 1;
        } else {
            neg_b = 1;
        }
        dealloc(tmp1);
    }
    if (a->negative && !b->negative) {
        Bigint* tmp2 = absolute(a);
        if (big(tmp2, b)) {
            neg_b = 1;
            negative = 1;
        } else {
            neg_a = 1;
        }
        dealloc(tmp2);
    }


    Node* aux_node = malloc(sizeof(Node));
    aux_node->next = NULL;
    result->tail = aux_node;
    Node* aux2 = aux_node;

    Node* node_a = a->tail;
    Node* node_b = b->tail;
    int next_ten=0;
    int sum;
    int num_a;
    int num_b;

    // Somando termos do menor número com do maior
    int n = a->size < b->size ? a->size : b->size;
    for (int i=0; i<n; i++) {
        aux_node = aux2;
        num_a = neg_a ? -node_a->n : node_a->n;
        num_b = neg_b ? -node_b->n : node_b->n;
        sum = num_a + num_b + next_ten;
        
        if (sum < 0 && node_a->prev != NULL) {
            sum = 10+sum;
            next_ten = -1;
        } else {
            next_ten = sum / 10;
        }

        aux_node->n = abs(sum % 10);
        aux_node->prev = malloc(sizeof(Node));
        aux2 = aux_node->prev;
        aux2->next = aux_node;

        node_a = node_a->prev;
        node_b = node_b->prev;
    }

    // Somando demais termos do maior número
    int N;
    int neg;
    int num;
    Node* node_rest;
    if (a->size > b->size) {
        N = a->size;
        node_rest = node_a;
        neg = neg_a;
    } else {
        N = b->size;
        node_rest = node_b;
        neg = neg_b;
    }
    for (int i=n; i<N; i++) {
        aux_node = aux2;
        num = neg ? -node_rest->n : node_rest->n;
        sum = num + next_ten;

        next_ten = sum / 10;
        
        aux_node->n = abs(sum % 10);
        aux_node->prev = malloc(sizeof(Node));
        aux2 = aux_node->prev;
        aux2->next = aux_node;
        
        node_rest = node_rest->prev;
    }  

    
    // Adicionando termo com próxima ordem de grandeza, caso necessário
    if (next_ten != 0) {
        aux_node = aux2;
        aux_node->n = abs(next_ten);
        result->size = N+1;
    } else {
        result->size = N;
        free(aux2);
    }

    result->negative = negative;
    result->head = aux_node;
    result->head->prev = NULL;
    format(result);
    return result;
}


// Libera memória
int dealloc(Bigint* number) {
    Node* aux1 = number->head;
    Node* aux2 = NULL;
    for (int i=0; i<number->size; i++) {
        aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
    free(number);

    return 1;
}


// Imprime um número Bigint
int printNumber(Bigint* number) {
    Node* aux = number->head;
    
    if (number->negative == 1) {
        printf("-");
    }
    for (int i=0; i<number->size; i++) {
        printf("%d", aux->n);
        aux = aux->next;
    }
    printf("\n");

    return 1;
}

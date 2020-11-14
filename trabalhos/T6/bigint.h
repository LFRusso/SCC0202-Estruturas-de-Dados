#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    unsigned n;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Bigint {
    Node* tail;
    Node* head;
    int size;
    int negative;
} Bigint;


Bigint* create();
int dealloc(Bigint* number);
int read(Bigint* number, FILE* input);
int printNumber(Bigint* number);
Bigint* absolute(Bigint* number);
Bigint* sum(Bigint* a, Bigint* b);
int sml(Bigint* a, Bigint* b);
int big(Bigint* a, Bigint* b);
int eql(Bigint* a, Bigint* b);

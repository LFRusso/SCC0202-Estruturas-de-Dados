#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
    int max_size;
    int size;
    int elem_size;
    void** elements;
} stack_t;

stack_t* stackBuild(int max_size);

void stackDestroy(stack_t* mystack);

void stackPush(stack_t* mystack, void* elem);

void* stackPop(stack_t* mystack);

void stackPrint(stack_t* mystack);

void stackDump(stack_t* dest, stack_t* src);
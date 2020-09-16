#include "stack.h"

// Builds the stack with an specified size
stack_t* stackBuild(int max_size){
    stack_t* mystack = malloc(sizeof(stack_t));
    mystack->max_size = max_size;
    mystack->size = 0;

    mystack->elements = (void*) malloc(max_size*8);

    return mystack;
}

// Pushes element to the stack
void stackPush(stack_t* mystack, void* elem){
    void* insertion = malloc(sizeof(void*));
    memcpy(insertion, elem, sizeof(void*));

    mystack->elements[mystack->size] = insertion;
    mystack->size += 1;
    return;
}

// Removes the top element from the stack
void* stackPop(stack_t* mystack){
    void* elem = malloc(sizeof(void*));
    mystack->size -= 1;
    memcpy(elem,mystack->elements[mystack->size], sizeof(void*));

    free(mystack->elements[mystack->size]);
    return elem;
}

// Prints all the elements inside of the stack
void stackPrint(stack_t* mystack){
    for(int i=0; i<mystack->size; i++){
        printf("%d ", *(int*) mystack->elements[i]);
    }
    printf("\n");
    return;
}


// Dealocates memory stored on a stack
void stackDestroy(stack_t* mystack){
    for(int i=0; i<mystack->size; i++){
        free(mystack->elements[i]);
    }
    free(mystack->elements);
    free(mystack);
    mystack = NULL;

    return; 
}

// Dumps the elements of a stack into another, inverting it
void stackDump(stack_t* dest, stack_t* src){
    void* elem;
    while(src->size > 0){
        elem = stackPop(src);
        stackPush(dest, elem);
        free(elem);
    }
    return;
}
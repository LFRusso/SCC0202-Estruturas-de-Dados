#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info {
    char* word;
    char* desc;
} info;

typedef struct node {
    char* value;
    struct node** next;
    
    info* data;
} node;

typedef struct skiplist {
    node* head;
    int maxlevel;
    int level;
} skiplist;


info* readInfo(FILE* input);

// Skiplist related
skiplist* slCreate();
int slRemove(skiplist* sl, char* value);
int slInsert(skiplist* sl, info* data);
int slSearch(skiplist* sl, char* value);
int slChange(skiplist* sl, char* value, char* desc);
int slPrint(skiplist* sl, char* start_ch);
int slDelete(skiplist* sl);

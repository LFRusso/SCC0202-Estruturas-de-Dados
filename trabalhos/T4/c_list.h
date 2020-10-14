// Luiz Fernando S E Santos - 10892680

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
    int id;
    struct elem* next;
} elem;
typedef elem* c_list;

c_list* listBuild();
void listPrint(c_list* list);
int listPop(c_list* list);
int listDelId(c_list* list, int id);
int listDelIdx(c_list* list, int idx);
int listInsert(c_list* list, int element);
int listSize(c_list* list);
int listDestroy(c_list* list);

int findId(c_list* list, int id);

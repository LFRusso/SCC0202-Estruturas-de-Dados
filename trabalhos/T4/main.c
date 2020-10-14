#include <stdio.h>
#include "c_list.h"

// Encontra o Josefo
void findJoseph(c_list* list, int k) {
    int next_id = 1;
    int next_idx;
    while (listSize(list) > 1) {
        next_idx = findId(list, next_id);
        next_id = listDelIdx(list, next_idx+k-1);
    }
    return;
}

int main() {
    int T;
    int n, k;
    c_list* list;

    if(scanf("%d", &T) != 1) return 1;
    for (int i=0; i<T; i++) {
        if(scanf("%d", &n) != 1) return 1;
        if(scanf("%d", &k) != 1) return 1;
        
        // Inserindo pessoas na lista circular
        list = listBuild();
        for (int j=0; j<n; j++) {
            listInsert(list, j+1);
        }
        
        findJoseph(list, k);
        printf("Caso %d: %d\n", i+1, (*list)->id);
        listDestroy(list);
    }

    return 0;
}

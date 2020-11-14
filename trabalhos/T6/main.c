#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"


int main() {
    int n = 0;
    if (scanf("%d", &n) != 1) return 1;
    char* op = calloc(4, sizeof(char));
    Bigint* a;
    Bigint* b;
    Bigint* c;

    for (int i=1; i<=n; i++) {
        a = create();
        b = create(); 
        
        if (scanf("%s", op) != 1) return 1;
        getchar();
        read(a, stdin);    
        read(b, stdin);    

        if (strcmp(op, "sum") == 0) {
            c = sum(a, b);
            printf("Resultado %d: ", i);
            printNumber(c);
            dealloc(c);
        }
        if (strcmp(op, "eql") == 0) {
            printf("Resultado %d: %d\n", i, eql(a, b));
        }
        if (strcmp(op, "sml") == 0) {
            printf("Resultado %d: %d\n", i, sml(a, b));
        }
        if (strcmp(op, "big") == 0) {
            printf("Resultado %d: %d\n", i, big(a, b));
        }

        dealloc(a);
        dealloc(b);
    }
    
    free(op);
    return 0;
}

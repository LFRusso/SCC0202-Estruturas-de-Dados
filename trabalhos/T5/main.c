#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backwardlist.h"

char* readline(FILE* input){
    char* str = calloc(1, sizeof(char));
    char ch;
    
    ch = getc(input);
    while (ch != '\n' && ch != EOF){
        str = realloc(str, strlen(str)*sizeof(char) + 2*sizeof(char));
        strncat(str, &ch, 1);
        ch = getc(input);
    }
    strncat(str, "\0", 1);

    return str;
}

int main() {
    Backwardlist* lista = listBuild();

    char operacao;
    int n;
    int j;
    do {
        if(scanf("%c", &operacao) != 1) return 1;

        switch (operacao) {
            case 'i':
                if(scanf("%d", &n) != 1) return 1;
                if(scanf("%d", &j) != 1) return 1;
                
                listInsert(lista, n, j);
                break;

            case 'r':
                if(scanf("%d", &n) != 1) return 1;
                
                listRemove(lista, n);
                break;

            case 'f':
                listPrint(lista);
                break;

            default:
                break;
        }

    } while (operacao != 'f');

    
    listDestroy(lista);
    return 0;
}

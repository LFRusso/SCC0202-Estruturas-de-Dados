#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"

// Leitura da palavra
char* readword(FILE* input){
    char* str = calloc(1, sizeof(char));
    char ch;
    
    ch = getc(input);
    while (ch != ' ' && ch != EOF && ch != '\n'){
        if (ch != '\r') {
            str = realloc(str, strlen(str)*sizeof(char) + 2*sizeof(char));
            strncat(str, &ch, 1);
        }
        ch = getc(input);
    }
    strncat(str, "\0", 1);

    return str;
}

// Leitura da descrição
char* readdesc(FILE* input){
    char* str = calloc(1, sizeof(char));
    char ch;
    
    ch = getc(input);
    while (ch != '\n' && ch != EOF){
        if (ch != '\r') {
            str = realloc(str, strlen(str)*sizeof(char) + 2*sizeof(char));
            strncat(str, &ch, 1);
        }
        ch = getc(input);
    }
    strncat(str, "\0", 1);

    return str;
}

int main() {
    skiplist* sl = slCreate(10);
    
    char* operation;
    char* word;
    char* desc;
    info* data;

    operation = readword(stdin);
    while (operation[0] != 0) {
        
        if (strcmp(operation, "insercao")==0) {
            word = readword(stdin);
            desc = readdesc(stdin);
            
            data = malloc(sizeof(info));
            data->word = word;
            data->desc = desc;

            slInsert(sl, data);
        }
        if (strcmp(operation,"alteracao")==0) {
            word = readword(stdin);
            desc = readdesc(stdin);
            
            slChange(sl, word, desc);
            free(word);
        }
        if (strcmp(operation, "remocao")==0) {
            word = readword(stdin);
            slRemove(sl, word);
            free(word);
        }
        if (strcmp(operation, "busca")==0) {
            word = readword(stdin);
            slSearch(sl, word);
            free(word);
        }
        if (strcmp(operation, "impressao")==0) {
            word = readword(stdin);
            slPrint(sl, word);
            free(word);
        }

        free(operation);
        operation = readword(stdin);
    }
    free(operation);

    slDelete(sl);
    return 0;
}

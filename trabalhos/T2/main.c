#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main(){
    int n_cards;
    if(scanf("%d", &n_cards) != 1) return 1;;
    
    stack_t* compra = stackBuild(n_cards);
    stack_t* compra_aux = stackBuild(n_cards);
    stack_t* descarte = stackBuild(n_cards);
    stack_t* morto = stackBuild(n_cards);

    // Lendo entradas
    int card;
    for (int i=0; i < n_cards; i++) {
        if(scanf("%d", &card) != 1) return 1;
        stackPush(compra_aux, (void*) &card);
    }

    // Invertenndo stack com as cartas para comprar
    stackDump(compra, compra_aux);

    int i = 0;
    void* elem;
    while (morto->size < n_cards){
        for (int i=0; compra->size > 0; i++) {
            elem = stackPop(compra);

            // Checando se elemento deve ser colocado no Morto ou descartado
            if(*(int*) elem == morto->size + 1){
                stackPush(morto, elem);
            } else {
                stackPush(descarte, elem);
            }
            free(elem);
        } 
        i++;

        // Voltando descarte para a compra
        stackDump(compra, descarte);
    }
    printf("%d\n", i);


    // Liberando memória
    stackDestroy(compra);
    stackDestroy(descarte);
    stackDestroy(morto);
    return 0;
}

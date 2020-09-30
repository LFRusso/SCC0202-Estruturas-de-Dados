#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// Retorna a prioridade do paciente baseado na ideade e se tem alguma doença
int getPriority(int age, int condition) {
    int priority=0;
    priority = age>=60 ? priority+1 : priority;
    priority = condition==1 ? priority+2 : priority;
    return priority;
}

int main(){
    int operations;
    if(scanf("%d", &operations) != 1) return 1;
    // Estou partindo do pressuposto que não podemos colocar mais pacients que o número de operações
    pQueue* q = queueBuild(operations);
    
    int priority;
    Node pacient;
    char operation[30];
    for (int i=0; i<operations; i++) {
        if(scanf("%s", operation) != 1) return 1;
        switch(operation[0]) {
            // Operação ENTRA
            case 'E':
                // Inserindo paciente 
                if(scanf("%s", pacient.name) != 1) return 1;    
                if(scanf("%d", &pacient.age) != 1) return 1;
                if(scanf("%d", &pacient.condition) != 1) return 1;
                priority = getPriority(pacient.age, pacient.condition);
                queueInsert(q, pacient, priority);
                break;

            // Operação SAI
            case 'S':
                queuePop(q);
                break;

            default:
                break;
        }
    }
    
    queueDestroy(q);
    return 0;
}

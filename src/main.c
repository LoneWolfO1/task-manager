#include <stdio.h> 
#include <stdlib.h> 
#include "tarefa.h"
#include "pasta.h"
#include "ui.h"

Pasta *head_pastas = NULL;

void imprime_tarefas(Tarefa *head){
    while (head != NULL){
        printf("Id: %d \n",head->id);
        head = head->nextTarefa;
    }
    
}

int main(){
    Pasta *head_pastas = NULL;
    menu_principal(&head_pastas);

    return 0;
}

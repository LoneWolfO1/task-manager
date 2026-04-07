#include "tarefa.h"
#include <string.h> 
#include <stdlib.h>
#include "pasta.h"

static int proximo_id = 1;

Tarefa *cria_tarefa(char *titulo ,Data data ){
    Tarefa *t = malloc(sizeof(Tarefa));
    t->nextTarefa = NULL; 
    t->id = proximo_id++;
    strcpy(t->titulo, titulo);
    t->data = data;
    return t;
}

void check_tarefa(Tarefa *t){
    t->estado = 1;
}

void apaga_tarefa(Tarefa **head, int id){
    Tarefa *atual = *head;
    Tarefa *anterior = NULL;
    while(atual != NULL){
        if(atual->id == id){
            if(anterior == NULL) {
                *head = atual->nextTarefa;
            }else if (anterior != NULL){
                anterior->nextTarefa = atual->nextTarefa;
            }
            free(atual);
            break;
        }else{
            anterior = atual;
            atual = atual->nextTarefa;
        }
    }
}


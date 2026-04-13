#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "pasta.h"
#include "tarefa.h"

Pasta *cria_pasta(char *nome){
    Pasta *p = malloc(sizeof(Pasta));
    p->nextPasta = NULL;
    p->head = NULL;
    p->size = 0;
    strcpy(p->nome,nome);
    return p;
}

void apaga_pasta(Pasta **head,char *nome){
    Pasta *atual = *head;
    Pasta *anterior = NULL;
    while (atual != NULL){
       if(strcmp(atual->nome,nome)==0){
            if(anterior == NULL){
                *head = atual->nextPasta;
            }else if (anterior != NULL){
                anterior->nextPasta = atual->nextPasta;
            }
            free(atual);
            break;
       }else{
        anterior = atual;
        atual = atual->nextPasta;
       }
    }
}

void insere_pasta(Pasta **head,char *nome){
    Pasta *nova_p = cria_pasta(nome);
    nova_p->nextPasta = *head;
    *head = nova_p;
}

void insere_tarefa_na_pasta(Pasta *p ,char *titulo ,Data d ,char *desc){
    Tarefa *nova_t = cria_tarefa(titulo,d,desc);
    nova_t->nextTarefa = p->head;
    p->head = nova_t;
    p->size++;
}

int conta_pastas(Pasta *head){
    int count = 0;
    while (head != NULL){
        count++;
        head = head->nextPasta;
    }
    return count;
}
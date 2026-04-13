#ifndef PASTA_H
#define PASTA_H

#include "tarefa.h" 

typedef struct Pasta {
    struct Pasta *nextPasta;
    char nome[tamanho];        
    Tarefa *head;    
    int size ;
}Pasta;

Pasta *cria_pasta(char *nome);
void apaga_pasta(Pasta **head,char *nome);
void insere_pasta(Pasta **head,char *nome);
void insere_tarefa_na_pasta(Pasta *p ,char *titulo ,Data d , char *desc);
int conta_pastas(Pasta *head);


#endif

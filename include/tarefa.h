#ifndef TAREFA_H
#define TAREFA_H


#define tamanho 256


typedef struct {
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Tarefa{
    struct Tarefa *nextTarefa;
    int  id;
    char titulo[tamanho];
    Data data;
    int  estado;
}Tarefa;

Tarefa *cria_tarefa(char *titulo, Data data);
void check_tarefa(Tarefa *t);
void apaga_tarefa(Tarefa **head, int id);

#endif

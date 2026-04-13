#ifndef UI_H
#define UI_H 

#include <ncurses.h>
#include "pasta.h"


void draw_wrapped_text();
void tarefa_ui(int linha , int coluna, int largura, int altura , char nome[], Data data, char descricao[]);
int task_manager_titulo();
void menu_principal(Pasta **head_pastas);
void menu_pasta(Pasta *pasta);

#endif 

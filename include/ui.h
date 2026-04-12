#ifndef UI_H
#define UI_H 

#include <ncurses.h>
#include "pasta.h"



void imprime_pastas(Pasta *head,int indices);
int task_manager_titulo();
void menu_principal(Pasta **head_pastas);
void menu_pasta(Pasta *pasta);

#endif 

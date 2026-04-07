#ifndef UI_H
#define UI_H 

#include <ncurses.h>
#include "pasta.h"



void imprime_Pastas(Pasta *head,int indices);
void task_manager_titulo();
void menu_principal(Pasta **head_pastas);


#endif 

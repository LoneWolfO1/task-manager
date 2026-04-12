#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "pasta.h"
#include "tarefa.h"
#include "ui.h"


int task_manager_titulo(){
    int ui_indice = 0;
    mvprintw(ui_indice++, 0, " _____          _                                               ");
    mvprintw(ui_indice++, 0, "/__   \\__ _ ___| | __   /\\/\\   __ _ _ __   __ _  __ _  ___ _ __ ");
    mvprintw(ui_indice++, 0, "  / /\\/ _` / __| |/ /  /    \\ / _` | '_ \\ / _` |/ _` |/ _ \\ '__|");
    mvprintw(ui_indice++, 0, " / / | (_| \\__ \\   <  / /\\/\\ \\ (_| | | | | (_| | (_| |  __/ |   ");
    mvprintw(ui_indice++, 0, " \\/   \\__,_|___/_|\\_\\ \\/    \\/\\__,_|_| |_|\\__,_|\\__, |\\___|_|   ");
    mvprintw(ui_indice++, 0, "                                                |___/           ");
    mvprintw(ui_indice++, 0, "________________________________________________________________");
    mvprintw(ui_indice++, 0, "________________________________________________________________");
    ui_indice++;
    return ui_indice;
}

void prompt_criar_tarefa(Pasta *pasta) {
    int win_altura = 10;
    int win_largura = 40;
    int win_y = (LINES - win_altura) / 2;
    int win_x = (COLS - win_largura) / 2;
    WINDOW *prompt = newwin(win_altura, win_largura, win_y, win_x);
    
    char titulo[32];
    int dia, mes, ano;
    
    echo();
    curs_set(1);
    box(prompt, 0, 0);
    
    // pede título
    mvwprintw(prompt, 2, 1, " Task Name: ");
    wrefresh(prompt);
    wgetnstr(prompt, titulo, 31);
    
    // pede data
    mvwprintw(prompt, 3, 1, " Day: ");
    wrefresh(prompt);
    wscanw(prompt, "%d", &dia);
    
    mvwprintw(prompt, 4, 1, " Month: ");
    wrefresh(prompt);
    wscanw(prompt, "%d", &mes);
    
    mvwprintw(prompt, 5, 1, " Year: ");
    wrefresh(prompt);
    wscanw(prompt, "%d", &ano);
    
    Data d = {dia, mes, ano};
    insere_tarefa_na_pasta(pasta, titulo, d);
    
    noecho();
    curs_set(0);
    delwin(prompt);
}

void menu_pasta(Pasta *pasta){


    char *opcoes[] = {"Create Task "};
    int selecionado = 0;

    while (1){
        clear(); // limpa o ecrã
        int num_tarefas = 0;
        Tarefa *tarefas_arr[100];
        Tarefa *atual = pasta->head;
        while (atual != NULL) {
            tarefas_arr[num_tarefas++] = atual;
            atual = atual->nextTarefa;
        }
        

        int ui_indice = task_manager_titulo();
        int msg_len = strlen("Esc to exit");
        mvprintw(ui_indice, COLS - msg_len - 5, "Esc to exit");
        mvprintw(ui_indice, 0, "[ %s ]", pasta->nome);
        ui_indice++;
        
        int num_opcoes = num_tarefas + 1;
        
        FILE *log = fopen("debug2.log", "a");
        fprintf(log, "num_tarefas: %d, num_opcoes: %d, selecionado: %d\n"
        , num_tarefas, num_opcoes, selecionado);
        fclose(log);
        
        for (int i = 0; i < num_opcoes; i++) {
            if (i < num_tarefas) {
                if (i == selecionado)
                    mvprintw(i + ui_indice,1, " > %s", tarefas_arr[i]->titulo);
                else
                    mvprintw(i + ui_indice,1, " %s", tarefas_arr[i]->titulo);
            } else {
                if (i == selecionado)
                    mvprintw(i + ui_indice,1, " > %s", opcoes[i - num_tarefas]);
                else
                    mvprintw(i + ui_indice,1, " %s", opcoes[i - num_tarefas]);
            } 
        }
        refresh(); // atualiza o ecrã (como um flush)
        //wrefresh(win);

        int tecla = getch();
        if (tecla == KEY_UP && selecionado > 0) {
            selecionado--;
        } else if (tecla == KEY_DOWN && selecionado < num_opcoes - 1) {
            selecionado++;
        } else if (tecla == 27) { // ESC para voltar
            break;
        } else if(tecla == '\n' && selecionado == num_tarefas){
            prompt_criar_tarefa(pasta);
        }
    }
    
}

void menu_principal(Pasta **head_pastas){
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    char *opcoes[] = {"Create Folder", "Exit"};
    int selecionado = 0;

    while (1) {
        clear(); // limpa o ecrã
        int num_pastas = 0;
        Pasta *pastas_arr[100];
        Pasta *atual = *head_pastas;
        while (atual != NULL) {
            pastas_arr[num_pastas++] = atual;
            atual = atual->nextPasta;
        }
        int num_opcoes = num_pastas + 2;
        
        FILE *log = fopen("debug.log", "a");
        fprintf(log, "num_pastas: %d, num_opcoes: %d, selecionado: %d\n"
        , num_pastas, num_opcoes, selecionado);
        fclose(log);
        //mvprintw(0, 0, "Task Manager");  // linha 0, coluna 0
        //ui_indice = 0;
        int ui_indice = task_manager_titulo();
        
        

        int box_altura = num_opcoes + 2; // +2 para as bordas
        int box_largura = 40;
        int box_y = ui_indice ;
        int box_x = 0;

        WINDOW *win = newwin(box_altura, box_largura, box_y, box_x);
        box(win, 0, 0);
        
        
        // desenha cada opção
        for (int i = 0; i < num_opcoes; i++) {
            if (i < num_pastas) {
                if (i == selecionado)
                    mvwprintw(win,i + 1,1, " > %s", pastas_arr[i]->nome);
                else
                    mvwprintw(win,i + 1,1, " %s", pastas_arr[i]->nome);
            } else {
                if (i == selecionado)
                    mvwprintw(win,i + 1,1, " > %s", opcoes[i - num_pastas]);
                else
                    mvwprintw(win,i + 1,1, " %s", opcoes[i - num_pastas]);
            }
        }
        
        refresh(); // atualiza o ecrã (como um flush)
        wrefresh(win);
        int tecla = getch(); // espera input

        if (tecla == KEY_UP && selecionado > 0) {
            selecionado--;
        } else if (tecla == KEY_DOWN && selecionado < num_opcoes - 1) {
            selecionado++;
        } else if (tecla == '\n') {
            if (selecionado == 1 + num_pastas) {
                break;
            }else if (selecionado == num_pastas){
                int win_altura = 5;
                int win_largura = 40;
                int win_y = (LINES - win_altura) / 2;
                int win_x = (COLS - win_largura) / 2;
                WINDOW *prompt = newwin(win_altura, win_largura, win_y, win_x);
                box(prompt, 0, 0);

                char nome[32];
                echo();           // mostra o que o utilizador escreve
                curs_set(1);      // mostra o cursor
                clear();
                //ui_indice = 0;
                task_manager_titulo();
                
                mvwprintw(prompt,2, 1, " Folder Name: ");
                
                refresh();
                wrefresh(prompt);
                wgetnstr(prompt,nome, 23); // lê a string
                
                insere_pasta(head_pastas,nome);
                noecho();         // volta a esconder
                curs_set(0);
                delwin(prompt);
            }else if (selecionado < num_pastas){
                menu_pasta(pastas_arr[selecionado]);
                
            }
        }

    }

    endwin(); // fecha o ncurses
}

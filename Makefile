taskmanager : main.o pasta.o ui.o tarefa.o
	gcc main.o pasta.o ui.o tarefa.o -o taskmanager -lncurses

main.o : src/main.c
	gcc -c src/main.c -Iinclude -o main.o

pasta.o : src/pasta.c
	gcc -c src/pasta.c -Iinclude -o pasta.o

ui.o : src/ui.c
	gcc -c src/ui.c -Iinclude -o ui.o

tarefa.o : src/tarefa.c
	gcc -c src/tarefa.c -Iinclude -o tarefa.o

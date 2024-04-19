CC = gcc

main : main.o fila.o
	gcc bin/main.o bin/fila.o -g -Wall -o main

main.o : src/main.c
	gcc src/main.c -g -Wall -o  bin/main.o

fila.o : lib/fila.c
	gcc lib/fila.c -g -Wall -o bin/fila.o

clean :
	rm bin/main
	rm bin/main.o
	rm bin/fila.o

# o '!=' permite chamar um shell function e definir o retorno dessa função para à variavel
objects = main.o binary_tree.o 
TARGET = main

clean : default
	rm -f *.o

default : $(objects) 
	cc -g $(objects) -o binaries/main

binary_tree.o : libs/binary_tree.c
	cc -g -c libs/binary_tree.c -o binary_tree.o
 
main.o : codes/main.c
	cc -g -c codes/main.c -o main.o	
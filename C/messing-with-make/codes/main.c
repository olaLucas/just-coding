#ifndef INCLUDES
#define INCLUDES

    #include <stdio.h>
    #include <stdlib.h>

#endif

#define ARRAY_SIZE 10
#define GRANDEZA 1000

#include "../libs/binary_tree.h"

void init_array(int array[])
{
    for (int i = 0; i < ARRAY_SIZE; i++)
        array[i] = rand() % GRANDEZA;
}

void exibir_array(int array[])
{
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d ", array[i]);
}

int main(int argc, char * argv[])
{
    if (argc <= 0)
    {
        puts("Nenhum valor foi passado.\n");
        exit(0);
    }
    else
    {
        int target = 0;
        ptr_node inicio = NULL;

        int array_rand[ARRAY_SIZE];

        init_array(array_rand);
        
        for (int i = 0; i < ARRAY_SIZE; i++)
            inicio = inserir(inicio, array_rand[i]);

        
        printf("ARRAY: "); exibir_array(array_rand);
        printf("\nINICIO: "); exibir_node(inicio);
        printf("ARVORE: "); exibir_emOrdem(inicio);

        puts("\n");

        puts("Insira um número à ser excluido: ");
        printf(">>> "); scanf("%d", &target);

        excluir(inicio, target);

        printf("ARVORE: "); exibir_emOrdem(inicio);

        exit(0);
    }
}
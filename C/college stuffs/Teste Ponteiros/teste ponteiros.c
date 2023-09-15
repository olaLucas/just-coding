#include <stdio.h>
#include <stdlib.h>

int * allocate(int tamanho)
{   
    return (int *)malloc(tamanho * sizeof(int));
}

int main(void)
{
    int **pointer;
    int linhas = 3;
    int colunas = 3;
    int counter = 0;

    pointer = (int **)malloc(3 * sizeof(int));

    for (int i = 0; i < 3; i++)
    {
        pointer[i] = allocate(colunas);
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            pointer[i][j] = counter;
            counter++;
        }
    }
    
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            printf("Valor: %d \n", pointer[i][j]);
        }
        printf("\n\n");
    }

    return 0;
}
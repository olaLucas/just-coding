#include <stdio.h>
#include <stdlib.h>

int *function(int x[], int size, int newSize)
{
    int *pointer = (int *)malloc(sizeof(int) * newSize);
    for (int i = 0; i < size; i++)
    {
        pointer[i] = x[i];
    }
    
    free(x);

    return pointer;
}

int main(void)
{
    int sizeArray = 10;
    int newSize = 20;
    int *pointer = (int *)malloc(sizeof(int) * sizeArray);

    for (int i = 0; i < 10; i++)
    {
        pointer[i] = i;
    }

    for (int i = 0; i < sizeArray; i++)
    {
        printf("sizeArray: %d \n\n", pointer[i]);
    }
    
    pointer = function(pointer, sizeArray, newSize);

    printf("\t -------------- \n\n");

    for (int i = 10; i < newSize; i++)
    {
        pointer[i] = i;
    }

    for (int i = 0; i < newSize; i++)
    {
        printf("newSize: %d \n\n", pointer[i]);
    }

    return 0;
}
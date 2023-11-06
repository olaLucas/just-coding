#include <stdio.h>
#include <stdlib.h>

#define SIZE_ARRAY 10
#define NEW_SIZE 20

int *function(int x[], int size, int NEW_SIZE)
{
    int *pointer = (int *)malloc(sizeof(int) * NEW_SIZE);
    for (int i = 0; i < size; i++)
    {
        pointer[i] = x[i];
    }
    
    free(x);

    return pointer;
}

int main(void)
{
    int *pointer = (int *)malloc(sizeof(int) * SIZE_ARRAY);

    for (int i = 0; i < 10; i++)
    {
        pointer[i] = i;
    }

    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        printf("SIZE_ARRAY: %d \n\n", pointer[i]);
    }
    
    pointer = function(pointer, SIZE_ARRAY, NEW_SIZE);

    printf("\t -------------- \n\n");

    for (int i = 10; i < NEW_SIZE; i++)
    {
        pointer[i] = i;
    }

    for (int i = 0; i < NEW_SIZE; i++)
    {
        printf("newSize: %d \n\n", pointer[i]);
    }

    return 0;
}
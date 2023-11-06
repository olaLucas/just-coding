#include <stdio.h>
#include <stdlib.h>

#define RAND_GRANDEZA 20
#define ARRAY_SIZE 10

typedef void (*CallbackFunction)(int);

void processNumbers(int array[], CallbackFunction function)
{
    for (int i = 0; i < 10; i++) {
        function(array[i]);
    }
}

void printNumbers(int n)
{
    printf("Number: %d\n", n);
}

void printSquare(int n)
{
    unsigned int result = n * n;
    printf("Square: %d | Number: %d\n", result, n);
}

int main(void)
{
    int array[10];

    for (int i = 0; i < 10; i++) {
        array[i] = rand() % RAND_GRANDEZA;
    }

    puts("Printing array: ");
    processNumbers(array, printNumbers);


    puts("Printing square");
    processNumbers(array, printSquare);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    void * ptr;

    char hello[] = "Hello, World!";
    const int arraySize = sizeof(hello) / sizeof(hello[0]);

    printf("arraySize: %d\n", arraySize);

    int x = 10;
    float y = 1.94;

    ptr = &x;
    printf("x: %d\n", *(int *)ptr);

    ptr = &y;
    printf("y: %f\n", *(float *)ptr);

    ptr = hello;
    printf("%c", *(char *)ptr);

    for (int i = 0; i < arraySize; i++)
    {
        ptr = ptr + sizeof(char);
        printf("%c", *(char *)ptr);
    }
    puts("");

    return 0;
}
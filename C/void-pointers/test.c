#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING "Hello, World!"

int main(void)
{   
    void * s = malloc(sizeof(STRING));

    memcpy(s, STRING, sizeof(STRING));

    printf("string: %s\n", (char *)s);
    
    int * ptrINT = (int *)s;
    char * ptrCHAR = (char *)s;

    char H = 'o';

    printf("%d\n", H);

    printf("%ld\n", strlen(STRING));
    
    for (int i = 0; i < strlen(STRING); i++)
    {
        printf("%c ", *ptrCHAR);
        ptrCHAR++;
    }

    printf("\nint: ");

    for (int i = 0; i < strlen(STRING); i++)
    {   

        printf("%d ", *ptrINT);
        ptrINT++;
    }

    puts("\n");
    

    free(s);

    return 0;
}
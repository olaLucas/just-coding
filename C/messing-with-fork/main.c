#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define HELLO "Hello, World!\n"

int main(void)
{
    __pid_t pid = fork();

    if(pid < 0)
        printf("fork failed!\n");
    
    if (pid == 0)
        printf("Sou processo filho : %d\n", getpid());
    
    else
        printf("Sou processo pai : %d\n", getpid());

    return 0;
}
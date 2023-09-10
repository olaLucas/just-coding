#include <stdio.h>

int function(int x)
{
    if(x <= 0)
	    return 1;

    return function(x-1) + function(x-2);
}

int main(void)
{
    int x = 10;
    printf("Value = %d \n", function(x)); 

    return 0;
}

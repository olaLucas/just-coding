#include <iostream>

int raizQuadrada(int n)
{
    int x = 0;
    int result = 0;
    while ((result = x * x) != n)
    {
        x++;
        std::cout << "Result value: " << result << std::endl;
        std::cout << "X value: " << result << std::endl;

        if (result > n)
            return -1;
    }
    
    if (result == n)
        return x;
    
    else
        return -1;
    
}
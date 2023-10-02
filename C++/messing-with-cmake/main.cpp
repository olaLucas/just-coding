#include <iostream>
#include "libs/raizQuadrada.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        int num = std::stoi(argv[1]);
        std::cout << "Result: " << raizQuadrada(num) << std::endl;
    }
    else
    {
        std::cout << "Nenhum valor foi informado." << std::endl;
    }
    
    return 0;
}
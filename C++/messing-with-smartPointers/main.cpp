#if !defined(INCLUDES)
#define INCLUDES

    #include <iostream>
    #include <memory>

#endif // INCLUDES

#include "libs/stack.hh"

#define SIZE_ARRAY 10
#define RAND_GRANDEZA 1000

void init_array(int array[])
{
    for (int i = 0; i < SIZE_ARRAY; i++)
        array[i] = rand() % RAND_GRANDEZA;
}

int main(void)
{
    int array_rand[SIZE_ARRAY]; init_array(array_rand);
    pilha::pilha_struct p;

    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        p = pilha::inserir(p, array_rand[i]);
    }

    pilha::exibir(p);

    pilha::excluir(p);

    pilha::exibir(p);

    return 0;
}
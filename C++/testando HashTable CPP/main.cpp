#if !defined(MAIN_INCLUDES)
#define MAIN_INCLUDES

#include <iostream>
#include <array>

#define ARRAY_TAM 20

#endif // MAIN_INCLUDES

#include "menu.h"

/* 
using std::string;
using std::endl;
using std::cout;
using std::array;
*/


int main(void)
{
    hashtable hash;
    menu::mainPrompt(hash);

    return 0;
}
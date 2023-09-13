#include <iostream>
#include <tuple>

using std::cout;
using std::cin;
using std::endl;
using std::tuple; 

enum {CHAR = 0, INT, FLOAT};

void display(tuple<char, int, float> x)
{
    cout << "Tuple Size: " << std::tuple_size<decltype(x)>::value << endl;
    cout << "Char: " << std::get<0>(x) << endl;
    cout << "Int: " << std::get<1>(x) << endl; // imprimindo
    cout << "Float: " << std::get<2>(x) << endl;
    cout << endl;
}

void change(tuple <char, int, float> * tup, char c, int i, float f)
{
    std::get<CHAR>(*tup) = c;
    std::get<INT>(*tup) = i;
    std::get<FLOAT>(*tup) = f;
}

int main(void)
{
    tuple <char, int , float> x('b', 11, 0.5); // constructor 

    display(x);

    x = std::make_tuple('a', 10, 5.5); // função para construir a tuple

    display(x);
    change(&x, 'b', 20, 11);
    display(x);

    cout << "Size: " << std::tuple_size<decltype(x)>::value << endl; // pegando o tamanho da tuple    

    return 0;
}
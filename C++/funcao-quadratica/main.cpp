#include <iostream>
#include <type_traits>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

void clean()
{
    int c = 0;
    while((c = getchar()) != '\n');
}

template <class data_type>
void display(data_type a, data_type b, data_type c, data_type delta, data_type x1, data_type x2)
{
    cout << "A:     " << a << endl;
    cout << "B:     " << b << endl;
    cout << "C:     " << c << endl;
    cout << "Delta: " << delta << endl;
    cout << "x1:    " << x1 << endl;
    cout << "x2:    " << x2 << endl;
}

template <class data_type>
data_type power(data_type b, int n = 0)
{
    if (n == 0)
    {
        cout << "expoente == 0." << endl;
        return 1;
    }

    if (std::is_arithmetic<data_type>::value == true)
    {
        data_type result = 0;
        for (int i = 0; i < n; i++)
        {
            result = result * b;
        }

        return result;
    }
    else
    {
        cout << "Not arithmetical" << endl;
    }
}

template <class data_type>
data_type raizQuadrada(data_type b, data_type delta)
{
    if (std::is_integral<data_type>::value == true)
    {
        if (b < 2)
        {
            return b;
        }
            
        int pwr = 1;
        int b_pwr = power(b, 2);

        while ((pwr * pwr) != b) // deixa lento, eu sei.
        {
            pwr++;
        }
            
        return pwr;
    }
    else if (std::is_floating_point<data_type>::value == true)
    {
        if (b < 2)
        {
            return b;
        }
        
        float x = b;
        float y = (x + (b / x)) / 2;

        while (fabs(x - y) >= 0.00001)
        {
            x = y;
            y = (x + (b / y)) / 2;
        }

        return y;
    }
}

template <class data_type>
void defineDelta(data_type a, data_type b, data_type c, data_type * delta)
{
    if (std::is_arithmetic<data_type>::value == true)
    {
        auto temp = (b * b) - (4 * a * c) / (2 * a);
        *delta = raizQuadrada(temp, *delta);
    }
    else
    {
        cout << "Not arithmetical" << endl;
    }    
}

template <class data_type>
void defineRaiz(data_type a, data_type b, data_type c, data_type delta, data_type * x1, data_type * x2)
{
    if (std::is_arithmetic<data_type>::value == true)
    {
        *x1 = (-b + delta)/(2 * a);
        *x2 = (-b - delta)/(2 * a);
    }
    else
    {
        cout << "Not arithmetical." << endl;
    }
}

int main(void)
{
    auto a = 0; 
    auto b = 0;
    auto c = 0;

    cout << "Coeficiente A: " << endl;
    cout << ">>> "; cin >> a;
    clean();

    if (fabs(a) < 0)
    {
        cout << "A == 0, não caracteriza uma função quadrática." << endl << endl;
        exit(0);
    }

    cout << "Coeficiente B " << endl;
    cout << ">>> "; cin >> b;
    clean();

    cout << "Coeficiente C " << endl;
    cout << ">>> "; cin >> c;
    clean();

    if (a == std::floor(a) && b == std::floor(b) && c == std::floor(c))
    {
        int x1 = 0, x2 = 0, delta = 0;

        defineDelta(a, b, c, &delta);
        defineRaiz(a, b, c, delta, &x1, &x2);
        display(a, b, c, delta, x1, x2);
    }
    else
    {
        int x1 = 0, x2 = 0, delta = 0;

        defineDelta(a, b, c, &delta);
        defineRaiz(a, b, c, delta, &x1, &x2);
        display(a, b, c, delta, x1, x2);
    }


    return 0;
}
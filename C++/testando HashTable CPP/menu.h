#if !defined(MENU_INCLUDES)
    #define MENU_INCLUDES

    #include <iostream>
    #include <string>
    #include <array>

    #include "hashtable.h"

    #define ARRAY_TAM 20

#endif // MENU_INCLUDES

using std::string;
using std::array;
using std::cout;
using std::cin;
using std::endl;

namespace menu
{
    void cleanStdout();

    void mainPrompt(hashtable hash);
    unsigned long int getInput();

    void inserir_dados(hashtable hash);
    void visualizar_array(hashtable hash);
    void excluir_array(hashtable hash);
}

void menu::cleanStdout()
{
    while (int c = getchar() != '\n');
}

void menu::mainPrompt(hashtable hash)
{
    while (true)
    {
        cout << "Bem vindo!" << endl;
        cout << "Selecione uma opção: " << endl << endl;
        cout << "0. Sair" << endl;
        cout << "1. Inserir dados" << endl;
        cout << "2. Visualizar array" << endl;
        cout << "3. Excluir dados" << endl << endl;

        cout << "Insira sua opção: ";

        switch (menu::getInput())
        {
        case 0:
            cout << "saindo..." << endl;
            exit(0);
            break;
        
        case 1:
            menu::inserir_dados(hash);
            break;
        
        case 2:
            menu::visualizar_array(hash);
            break;

        case 3:
            menu::excluir_array(hash);
            break;
        
        default:
            break;
        }
    }   
}

unsigned long int menu::getInput()
{
    unsigned int seletor;
    cout << endl;
    cout << ">>> "; cin >> seletor;

    menu::cleanStdout();

    return seletor; 
}

void menu::inserir_dados(hashtable hash)
{
    int n;

    do
    {
        cout << "Insira um número para inserção: (-1. Cancelar, 0. rand())" << endl;
        n = menu::getInput();

        if (n > 0) 
        { 
            hash.inserir_dados(n); 
            return;
        }
        else if (n == 0) 
        { 
            hash.inserir_dados(rand() % 100);
            return; 
        }
        else if (n == -1)
        {
            return;
        }
        else 
        { 
            cout << "Insira um número entre -1 e > 0" << endl; 
        }
    
    } while (true);
}

void menu::visualizar_array(hashtable hash)
{
    hash.display_array();
}

void menu::excluir_array(hashtable hash)
{
    unsigned long int n;

    do
    {
        cout << "Insira o número para exclusão: ";
        n = menu::getInput();

        if (n > 0) 
        {
            hash.excluir_dados(n);
            return; 
        }
        else 
        { 
            cout << "Insira um número entre -1 e > 0" << endl; 
        }

    } while (true);
}
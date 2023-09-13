#include <iostream>
#include <queue>

using std::cout;
using std::cin;
using std::endl;
using std::queue;

void display(queue<int> fila);

namespace menu
{
    void mainPrompt(queue<int> fila);
    unsigned int getInput();
    void clean();
}

void menu::mainPrompt(queue<int> fila)
{
    while (true)
    {
        system("clear");

        cout << "Bem vindo!" << endl;
        
        display(fila);
        
        cout << "Selecione uma opção: " << endl << endl;
        cout << "0. Sair" << endl;
        cout << "1. Inserir dados" << endl;
        cout << "2. Excluir dados" << endl << endl;

        cout << "Insira sua opção: ";

        switch (getInput())
        {
        case 0:
            cout << "saindo..." << endl;
            exit(0);
            break;
        
        case 1:
            cout << "Insira um número > 0:";
            fila.emplace(getInput());
            break;

        case 2:
            if (fila.empty())
                cout << "Pilha vazia!" << endl;
            else
                fila.pop();                
            break;
        
        default:
            break;
        }
    }   
}

unsigned int menu::getInput()
{
    unsigned int seletor;
    cout << endl;
    cout << ">>> "; cin >> seletor;

    menu::clean();

    return seletor; 
}

void menu::clean()
{
    int c = 0;
    while ((c = getchar()) != '\n');
}

void display(queue<int> fila)
{
    if (fila.empty())
    {
        cout << "Fila vazia!" << endl;
        return;
    }
    else
    {
        cout << "Primeiro elemento: " << fila.front() << endl;
        cout << "Ultimo elemento: " << fila.back() << endl;

        unsigned int i = 0;
        while (!fila.empty())
        {
            cout << "ID: " << i << " Valor: "<< fila.front() << endl;
            fila.pop();
            i++;
        }

        cout << endl;
    }
}

int main(void)
{
    queue<int> fila;
    menu::mainPrompt(fila);

    return 0;
}
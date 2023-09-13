#include <iostream>
#include <stack>

using std::cout;
using std::cin;
using std::endl;
using std::stack;

void display(stack<int> pilha);

namespace menu
{
    void mainPrompt(stack<int> pilha);
    unsigned int getInput();
    void clean();
}

void menu::mainPrompt(stack<int> pilha)
{
    while (true)
    {
        system("clear");

        cout << "Bem vindo!" << endl;
        
        display(pilha);
        
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
            pilha.push(getInput());
            break;

        case 2:
            if (pilha.empty())
                cout << "Pilha vazia!" << endl;
            else
                pilha.pop();
            
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

void display(stack<int> pilha)
{
    if (pilha.empty())
    {
        cout << "Pilha vazia!" << endl;
        return;
    }
    else
    {
        unsigned int i = pilha.size();
        while (!pilha.empty())
        {
            cout << "ID: " << i << " Valor: "<< pilha.top() << " ";
            pilha.pop();
            i--;
        }

        cout << endl;
    }   
}

int main(void)
{
    stack<int> pilha;
    menu::mainPrompt(pilha);

    return 0;
}
#include <iostream>
#include <unordered_map>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;

struct pessoa
{
    string nome;
    string CPF;
    unsigned int idade;

    bool operator == (const pessoa & p) const
    {
        return nome == p.nome && CPF == p.CPF && idade == p.idade;
    }
};


struct std::hash<pessoa>
{
    std::size_t operator () (pessoa const & p) const noexcept
    {
        std::size_t h1 = std::hash<string>{} (p.nome);
        std::size_t h2 = std::hash<string>{} (p.CPF);

        return h1 ^ h2;
    }
};


namespace menu
{
    void mainPrompt();
    unsigned int getInput();
    void clean();
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


int main()
{   
    unordered_map<> umap;   
}
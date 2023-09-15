#include <iostream>
#include <unordered_map>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;

typedef struct pessoa
{
    string nome;
    string CPF;
    unsigned int idade;

    bool operator == (const pessoa & p) const
    {
        return nome == p.nome && CPF == p.CPF && idade == p.idade;
    }

} pessoa;


/* 
namespace std
{
    template <>
    struct hash<pessoa>
    {
        std::size_t operator () (const pessoa & p) const noexcept
        {
            std::size_t CPF_Hash = hash<string> {} (p.CPF);
            return CPF_Hash;
        }
    };
    
} // namespace std
*/

namespace menu
{
    void mainPrompt(unordered_map<string, pessoa> * hash_table);
    unsigned int getInput();
    void clean();
    void pause();
}

namespace umap
{
    void inserir_dados(unordered_map <string, pessoa> * umap);
    void percorre_map(unordered_map<string, pessoa> umap);
    void exibir_dado(const pessoa p);
    void pesquisar_map(unordered_map<string, pessoa> umap);
    void excluir_map(unordered_map<string, pessoa> * umap);
} // namespace umap


unsigned int menu::getInput()
{
    unsigned int seletor;
    cout << endl;
    cout << ">>> "; cin >> seletor;

    menu::clean();

    return seletor; 
}

void menu::mainPrompt(unordered_map<string, pessoa> * hash_table)
{
    while (true)
    {
        system("clear");

        cout << "Bem vindo!" << endl;
        
        cout << "Selecione uma opção: " << endl << endl;
        cout << "0. Sair" << endl;
        cout << "1. Inserir dados" << endl;
        cout << "2. Visualizar dados" << endl;
        cout << "3. Pesquisar dados" << endl;
        cout << "4. Excluir dados" << endl << endl;

        cout << "Insira sua opção: ";

        switch (menu::getInput())
        {
        case 0:
            cout << "saindo..." << endl;
            exit(0);
            break;
        
        case 1:
            umap::inserir_dados(hash_table);
            break;

        case 2:
            umap::percorre_map(*hash_table);
            break;

        case 3:
            umap::pesquisar_map(*hash_table);
            break;

        case 4:
            umap::excluir_map(hash_table);
            break;
        
        default:
            break;
        }
    }  
}

void menu::clean()
{
    int c = 0;
    while ((c = getchar()) != '\n');
}

void menu::pause()
{
    clean();
    getchar();
}


void umap::inserir_dados(unordered_map <string, pessoa> * umap)
{
    pessoa temp;

    cout << endl;

    cout << "Nome: ";
    getline(cin, temp.nome);

    cout << "Idade: ";
    cin >> temp.idade;
    menu::clean();

    cout << "CPF: ";
    getline(cin, temp.CPF);
    
    umap->insert({temp.CPF, temp});
}

void umap::percorre_map(unordered_map <string, pessoa> umap)
{
    if (umap.empty())
    {
        cout << "Table vazia." << endl;
        menu::pause();
    }
    else
    {
        cout << "-----------------------------" << endl;

        unsigned int ID = 0;
        for (auto i = umap.begin(); i != umap.end(); i++)
        {
            cout << "ID: " << ++ID << endl;
            exibir_dado(i->second);   
        }

        cout << "-----------------------------" << endl;

        menu::pause();
    }
}

void umap::pesquisar_map(unordered_map <string, pessoa> umap)
{
    if (umap.empty())
    {
        cout << "Table vazia." << endl;
        menu::pause();
    }
    else
    {
        string CPF_Key;
        cout << "Insira o CPF do individuo: "; getline(cin, CPF_Key);
        cout << endl;

        auto result = umap.find(CPF_Key);
        if (result != umap.end())
        {
            exibir_dado(result->second);
            menu::pause();
        }
        else
        {
            cout << "Não encontrado." << endl;
            menu::pause();
        }
    }
}

void umap::exibir_dado(const pessoa p)
{
    cout << "Nome: " << p.nome << endl;
    cout << "Idade: " << p.idade << endl;
    cout << "CPF: " << p.CPF << endl;
}

void umap::excluir_map(unordered_map <string, pessoa> *umap)
{
    if (umap->empty())
    {
        cout << "Table vazia." << endl;
        return;
    }
    else
    {
        string CPF_Key;

        cout << "Insira o CPF do individuo: "; getline(cin, CPF_Key);
        cout << endl;

        if (auto result = umap->find(CPF_Key); result != umap->end())
        {
            umap->erase(CPF_Key);
            cout << "Individuo apagado." << endl;
        }
        else
        {
            cout << "Individuo não foi encontrado." << endl;
        }
    }
}

int main()
{   
    unordered_map<string, pessoa> hash_table;
    menu::mainPrompt(&hash_table);
       
    return 0;
}
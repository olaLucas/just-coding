#include <iostream>
#include <unordered_set>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::unordered_set;
using std::string;

typedef struct pessoa
{
    string nome;
    string CPF;
    unsigned int idade;

    bool operator == (const pessoa & p) const
    {
        return (this->CPF == p.CPF);
    }

} pessoa;

pessoa init_pessoa();

/* 

struct PairHash {
  template <typename T1, typename T2>
  auto operator()(const pair<T1, T2> &p) const -> size_t {
    return hash<T1>{}(p.first) ^ hash<T2>{}(p.second);
  }
};

ler: https://ianyepan.github.io/posts/cpp-custom-hash/

*/

namespace std
{
    template <>
    struct hash<pessoa>
    {
        std::size_t operator () (pessoa const & p) const noexcept
        {
            //std::size_t h1 = std::hash<string>{} (p.nome);
            std::size_t h2 = hash<string>{} (p.CPF);
            return h2;
        }
    };

} // namespace std

namespace menu
{
    void mainPrompt(unordered_set<pessoa> * hash_table);
    unsigned int getInput();
    void clean();
    void pause();
}

namespace uset
{
    void percorre_set(unordered_set<pessoa> hash_table);
    void display_elementos(const pessoa temp);
    void pesquisar_dados(unordered_set<pessoa> hash_table);
    void inserir_dados(unordered_set<pessoa> hash_table);
    void excluir_dados(unordered_set<pessoa> * hash_table);
} // namespace uset

void menu::mainPrompt(unordered_set<pessoa> * hash_table)
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
            hash_table->insert(init_pessoa());
            break;

        case 2:
            uset::percorre_set(*hash_table);
            break;

        case 3:
            uset::pesquisar_dados(*hash_table);
            break;

        case 4:
            uset::excluir_dados(hash_table);
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

void menu::pause()
{
    clean();
    getchar();
}

void uset::percorre_set(unordered_set<pessoa> hash_table)
{
    if (hash_table.empty())
    {
        cout << "Set vazia." << endl;
    }
    else
    {
        cout << "-----------------------" << endl;
        unsigned int count = 0;
        for (auto i = hash_table.begin(); i != hash_table.end(); i++)
        {
            count++;
            display_elementos(*i);
        }

        cout << "-----------------------" << endl;

        menu::pause();
    }
}

void uset::display_elementos(const pessoa temp)
{
    cout << "Nome: " << temp.nome << endl;
    cout << "Idade: " << temp.idade << endl;
    cout << "CPF: " << temp.CPF << endl;
}

void uset::pesquisar_dados(unordered_set<pessoa> hash_table)
{
    if (hash_table.empty())
    {
        cout << "Set vazia." << endl;
    }
    else
    {
        pessoa temp;
        const auto & copy = hash_table;

        cout << "Informe o CPF da pessoa: " << endl;
        getline(cin, temp.CPF);

        if (auto found = copy.find(temp); found == copy.end()) 
        {
            cout << "Não encontrado.";
        } 
        else 
        {
            display_elementos(*found);
            menu::pause();
        } 
    }
}

void uset::excluir_dados(unordered_set<pessoa> * hash_table)
{
    if (hash_table->empty())
    {
        cout << "Set vazia." << endl;
    }
    else
    {
        pessoa temp;

        cout << "Insira o CPF da pessoa: " << endl;
        cout << ">>> ";
        getline(cin, temp.CPF);

        if (hash_table->find(temp) == hash_table->end())
        {
            cout << "Não encontrado!" << endl;
        }
        else
        {
            hash_table->erase(temp);
        }
    }
}

pessoa init_pessoa()
{
    pessoa temp;

    cout << "Nome: ";
    getline(cin, temp.nome);

    cout << "Idade: ";
    cin >> temp.idade;

    menu::clean();

    cout << "CPF: ";
    getline(cin, temp.CPF);

    return temp;
}

int main(void)
{
    unordered_set<pessoa> hash_table;
    menu::mainPrompt(&hash_table);

    return 0;
}
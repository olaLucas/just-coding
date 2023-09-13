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
}

namespace uset
{
    void display_dados(unordered_set<pessoa> hash_table);
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
            uset::display_dados(*hash_table);
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



void uset::display_dados(unordered_set<pessoa> hash_table)
{
    if (hash_table.empty())
    {
        cout << "Set vazia." << endl;
    }
    else
    {
        cout << "-----------------------" << endl;
        unsigned int count = 0;
        for (auto i : hash_table)
        {
            count++;
            cout << "ID: " << count << endl;
            cout << "Nome: " << i.nome << endl;
            cout << "Idade: " << i.idade << endl;
            cout << "CPF: " << i.CPF << endl;
        }

        cout << "-----------------------" << endl;
    }
}

void uset::pesquisar_dados(unordered_set<pessoa> hash_table)
{
    if (hash_table.empty())
    {
        cout << "Set vazia." << endl;
    }
    else
    {
        string CPF_TEMP;
        const auto & copy = hash_table;

        cout << "Informe o CPF da pessoa: " << endl;
        getline(cin, CPF_TEMP);

        pessoa temp;
        temp.CPF = CPF_TEMP;

        auto found = copy.find(temp);

        if (found == copy.end()) 
        {
            cout << "Não encontrado.";
        } 
        else 
        {
            cout << "Nome: " << found->nome;
            cout << "Idade: " << found->idade;
            cout << "CPF: " << found->CPF;
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
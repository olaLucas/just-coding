#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "libs/json.hpp"

#define DUMP_INDENTATION 4
#define FILE_PATH "json-files/file.json"

using json = nlohmann::json;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

namespace pessoa
{
    typedef struct pessoa_struct
    {
        string hash;
        string nome;
        unsigned int idade;
        std::hash <string> hashFunction;

        pessoa_struct(
                string nomePARAM = "", 
                unsigned int idadePARAM = 0
            ) : nome(nomePARAM), idade(idadePARAM) 
        {
            hash_nome();
        };

        bool operator == (const pessoa_struct & p) const
        {
            return nome == p.nome && idade == p.idade;
        }

        void hash_nome()
        {
            if (nome.empty())
                return;
            else
                hash = std::to_string(hashFunction(nome));
        }

    } pessoa_struct;

    // funções necessárias para converter JSON -> struct | struct -> JSON
    void to_json(json &j, const pessoa_struct &p)
    {
        j = json {
            {"hash", p.hash},
            {"nome", p.nome},
            {"idade", p.idade}
        };
    }

    void from_json(const json &j, pessoa_struct &p)
    {
        j.at("hash").get_to(p.hash);
        j.at("nome").get_to(p.nome);
        j.at("idade").get_to(p.idade);
    }

} // namespace pessoa


template<>
struct std::hash <pessoa::pessoa_struct>
{
    std::size_t operator () (const pessoa::pessoa_struct & p) const noexcept
    {
        std::size_t nome_hash = hash <string> {} (p.nome);
        return nome_hash; 
    }
};

void insert_umap(
        unordered_map <string, pessoa::pessoa_struct> * umap, 
        pessoa::pessoa_struct p
    )
{
    if (p.nome == "" && p.idade == 0)
    {
        cout << "struct vazia" << endl;
        return;
    }
    
    umap->insert({p.hash, p});
}

void read_data(unordered_map <string, pessoa::pessoa_struct> * umap)
{
    json j;
    std::ifstream file(FILE_PATH);
    pessoa::pessoa_struct p;

    j = json::parse(file);
    if (j.empty())
    {
        cout << "File empty." << endl;
        return;
    }
    
    for (auto& i : j)
    {
        p = i;
        umap->insert({p.hash, p});
    }
    
    for (auto& [key, value] : *umap)
    {
        cout << "HASH: " << value.hash << endl;
        cout << "NOME: " << value.nome << endl;
        cout << "IDADE: " << value.idade << endl;
    }
}

void store_data(unordered_map <string, pessoa::pessoa_struct> * umap)
{
    json j;
    std::ofstream file(FILE_PATH);
    for (auto& [key, value] : *umap)
    {
        j[value.nome] = {
            
            {"hash", key},
            {"nome", value.nome},
            {"idade", value.idade}
            
        };
    }
    
    file << j.dump(DUMP_INDENTATION);
    file.close();
}

int main(void)
{
    unordered_map <string, pessoa::pessoa_struct> umap;
    insert_umap(&umap, {"Lucas Santos", 20});
    insert_umap(&umap, {"Leoanardo Peixoto", 19});
    insert_umap(&umap, {"Rafael Silva", 20});

    store_data(&umap);
    read_data(&umap);

    return 0;
}
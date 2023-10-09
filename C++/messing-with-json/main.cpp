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
        string HASH;
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
                cout << "Campo nome vazio." << endl;
            else
                HASH = std::to_string(hashFunction(nome));
        }

    } pessoa_struct;

    void to_json(json &j, const pessoa_struct &p)
    {
        j = json {
            {"hash", p.HASH},
            {"nome", p.nome},
            {"idade", p.idade}
        };
    }

    void from_json(const json &j, pessoa_struct &p)
    {
        j.at("hash").get_to(p.HASH);
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

void inserir_umap(
        unordered_map <string, pessoa::pessoa_struct> * umap, 
        string nomePARAM, unsigned int idadePARAM
    )
{
    pessoa::pessoa_struct temp {nomePARAM, idadePARAM};
    
    // temp.hash_nome();

    umap->insert({temp.HASH, temp});
}

void read_data(unordered_map <string, pessoa::pessoa_struct> * umap)
{
    json j;
    std::ifstream file(FILE_PATH);

    j = json::parse(file);
    if (j.empty())
    {
        cout << "File empty." << endl;
    }
    else
    {
        for (auto i = umap->begin(); i != umap->end(); i++)
        {
            // umap->insert({j.get});
        }
    }
    
}

void store_data(unordered_map <string, pessoa::pessoa_struct> * umap)
{
    json j;
    pessoa::pessoa_struct p;
    std::ofstream file(FILE_PATH);
    for (auto i = umap->begin(); i != umap->end(); i++)
    {
        j["pessoa"][i->first] = {
            {"nome", i->second.nome}, 
            {"idade", i->second.idade}
        };
    }
    
    file << j.dump(DUMP_INDENTATION);
    file.close();
}

int main(void)
{
    unordered_map <string, pessoa::pessoa_struct> umap;
    inserir_umap(&umap, "luc", 20);
    inserir_umap(&umap, "rafael", 30);
    inserir_umap(&umap, "leonardo", 40);

    store_data(&umap);
    return 0;
}
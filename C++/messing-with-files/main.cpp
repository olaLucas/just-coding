#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

#define FILE_PATH "files/pessoas.txt"

typedef struct pessoa
{
    string nome;
    int idade;
    float altura;

    pessoa(
        string nomePARAM = "", 
        int idadePARAM = 0, 
        float alturaPARAM = 0.0f
    ) : nome(nomePARAM), idade(idadePARAM), altura(alturaPARAM) 
    {
    }

} pessoa;

void insert_file(pessoa p, const string FILE_NAME)
{
    ofstream file (FILE_NAME, std::ios::app);
    if (!file.is_open())
    {
        cout << "Error while opening file." << endl;
        return;
    }
    
    
    file << p.nome << '\n'
         << p.idade << '\n'
         << p.altura << '\n';

    file.close();
}

vector <pessoa> read_file(const string FILE_NAME)
{
    ifstream file(FILE_NAME);
    vector <pessoa> tempArray;
    if (!file.is_open())
    {
        cout << "File doesn't exist." << endl;
        return tempArray;
    }

    string nome;
    string idade;
    string altura;

    while (!file.eof())
    {
        std::getline(file, nome);
        std::getline(file, idade);
        std::getline(file, altura);

        tempArray.push_back({nome, std::stoi(idade), std::stof(altura)});
    }
    
    file.close();
    
    return tempArray;
}

void display_pessoa(pessoa & p)
{

    if (p.nome == "" || p.idade == 0 || p.altura == 0.0f)
    {
        cout << "Nothing to display." << endl;
        return;
    }

    cout << "NOME: " << p.nome << endl;
    cout << "IDADE: " << p.idade << endl;
    cout << "ALTURA: " << p.altura << endl;
}

int main(void)
{
    // creating / cleaning the file
    ofstream file (FILE_PATH, std::ios::trunc);
    file.close();

    vector <pessoa> arrayWrite, arrayRead;

    arrayWrite.push_back({"Lucas Santos", 20, 1.94});
    arrayWrite.push_back({"Leonardo Peixoto", 19, 1.90});
    arrayWrite.push_back({"Rafael Silva", 20, 1.91});

    for (auto i : arrayWrite)
        insert_file(i, FILE_PATH);

    arrayRead = read_file(FILE_PATH);

    for (auto i : arrayRead)
        display_pessoa(i);
    
    return 0;
}
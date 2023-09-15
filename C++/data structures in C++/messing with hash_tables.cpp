#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;
using std::unordered_set;

typedef struct pessoa
{
	string nome = "";
	unsigned int idade = 0;
	string CPF = "";

	bool operator == (const pessoa & p) const
	{
		return nome == p.nome && idade == p.idade && CPF == p.CPF;
	}

} pessoa;

template<>
struct std::hash<pessoa>
{
	std::size_t operator () (const pessoa & p) const noexcept
	{
		return std::hash<string> {} (p.CPF);
	}
};

int main(void)
{
	unordered_map<string, pessoa> umap;
	unordered_set<pessoa> uset;

	pessoa lusca = {"Lucas", 20, "123"};

	umap["Lucas"] = {"Lusca", 20, "123"};

	uset.insert(lusca);


	auto result_map = umap.find(lusca.nome);
	auto result_set = uset.find(lusca);

	cout << "Map: " << endl;
	cout << result_map->second.nome << endl;
	cout << result_map->second.idade << endl;
	cout << result_map->second.CPF << endl;

	cout << endl << endl;

	cout << "Set: " << endl;
	cout << result_set->nome << endl;
	cout << result_set->idade << endl;
	cout << result_set->CPF << endl;

	return 0;
}
#include <iostream>
#include <ostream>
#include <string>
#include "lib/map.cpp"

int main(void) {
  map m;
  
  m.insert(Pessoa {"Lucas", "Masculino", 21});
  auto r = m.remove("Lucas");

  std::cout << "Nome:" << r.nome << std::endl; 
  std::cout << "Genero: " << r.genero << std::endl; 
  std::cout << "Idade: " << r.idade << std::endl;

  return 0;
}

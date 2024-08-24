#include <cmath>
#include <iostream>
#include <ostream>
#include <strstream>
#include <string>
#define ARRAY_LENGTH 1024  

struct Pessoa {
  std::string nome = "";
  std::string sexualidade = "";
  int idade = 0;

  bool operator==(const struct Pessoa& p) const {
    return (nome == p.nome) && (idade == p.idade) && (sexualidade == p.sexualidade);
  }

  std::ostream& operator<<(std::ostrstream& os, const struct Pessoa& p) {
  return os << "Nome: " << p.nome << std::endl 
            << "Gênero: " << p.sexualidade << std::endl
            << "Idade: " << p.idade << std::endl;
  }
};

struct Node {
  struct Pessoa data;
  struct Node * prox = nullptr;

  std::ostream& operator<<(std::ostrstream& os, const struct Node& n) {
  return os << "data: " << &n.data << std::endl
            << "prox: " << n.prox << std:: endl;
  }
};

class map {
public:
  map();
  map(map &&) = default;
  map(const map &) = default;
  map &operator=(map &&) = default;
  map &operator=(const map &) = default;
  ~map();

  void show();
  void insert(const struct Pessoa p);
  struct Pessoa remove(const std::string x);
  bool has(const std::string x);
  long int hash(const std::string x);
  void clear();

private:
  int len = 0;
  struct Node content[ARRAY_LENGTH];
};

map::map() {
}

map::~map() {
}

void map::show() {
  if (len < 1) {
    std::cout << "map::show() > the map is empty" << std::endl;
    return;
  }

  for (int i = 0; i < len; i++) {
    std::cout << i << " " << &content[i] << std::endl;
  }
}

void map::insert(const struct Pessoa x) {
  const int h = hash(x.nome);
  if (content[h].data != x && content[h].prox == nullptr) {
    content[h].data = x;
  } else if (content[h].data != x) { 
    if (content[h].prox != nullptr) {
      Node * nav = nullptr;
      while (nav->prox != nullptr) {
        nav = nav->prox;
      }

      nav->prox = new Node {x, nullptr};
    } else {
      content[h].prox = new Node {x, nullptr};  
    }
  }

  len++;
}

std::string map::remove(const std::string x) {
  if (len < 1) {
    std::cout << "map::remove() > map is empty." << std::endl;
    return "";
  }

  const int h = hash(x);
  
  if (content[h].data == x) {
    
  }
}

long int map::hash(const std::string x) {
  if (x.empty()) {
    std::cout << "map::hash() > string empty." << std::endl;
    return -1;
  }

  long int h = 1;
  for (int i = 0; i < x.length(); i++) {
    int t = x.at(i) * pow(3.0, (double)i);
    h += t; 
  }

  return h / ARRAY_LENGTH;
}

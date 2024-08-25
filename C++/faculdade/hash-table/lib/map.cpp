#include <cmath>
#include <iostream>
#include <ostream>
#include <strstream>
#include <string>
#define ARRAY_LENGTH 1024  

struct Pessoa {
  std::string nome = "";
  std::string genero = "";
  int idade = 0;

  bool operator==(const struct Pessoa& p) const {
    return (nome == p.nome) && (idade == p.idade) && (genero == p.genero);
  }
  
  bool operator!=(const struct Pessoa& p) const {
    return (nome != p.nome) || (idade != p.idade) || (genero != p.genero);
  }
};

std::ostream& operator<<(std::ostrstream& os, const struct Pessoa& p) {
  return os << "Nome: " << p.nome << std::endl 
            << "Gênero: " << p.genero << std::endl
            << "Idade: " << p.idade << std::endl;
}

struct Node {
  struct Pessoa data;
  struct Node * prox = nullptr;
};


std::ostream& operator<<(std::ostrstream& os, const struct Node& n) {
  return os << "data: " << &n.data << std::endl
            << "prox: " << n.prox << std:: endl;
}


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
  struct Pessoa has(const std::string x);
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

struct Pessoa map::remove(const std::string x) {
  struct Pessoa target = Pessoa();

  if (len < 1) {
    std::cout << "map::remove() > map is empty." << std::endl;
    return Pessoa();
  }

  const int h = hash(x);
  
  if (content[h].data.nome == x && content[h].prox == nullptr) {
    target = content[h].data;
    content[h].data = Pessoa();
  }

  if (content[h].data.nome != x && content[h].prox != nullptr) {
    struct Node * nav = content[h].prox;
    while (content[h].data.nome != x && content[h].prox != nullptr) {
      nav = nav->prox;
    }

    if (nav->data.nome == x && nav->prox != nullptr) {
      struct Node * prox_node = nav->prox;
      struct Pessoa target = nav->data;

      nav->prox = prox_node->prox;
      nav->data = prox_node->data;

      delete prox_node;
    }   
  }

  return target;
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

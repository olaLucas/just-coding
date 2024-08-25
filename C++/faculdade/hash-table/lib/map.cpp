#include <cmath>
#include <iostream>
#include <ostream>
#include <strstream>
#include <string>
#define ARRAY_LENGTH 1024  

struct Node {
  std::string data = std::string();
  struct Node * prox = nullptr;
};


std::ostream& operator<<(std::ostrstream& os, const struct Node& n) {
  return os << "data: " << n.data << std::endl
            << "prox: " << n.prox << std:: endl;
}

class map {
public:
  map();
 ~map();

  void insert(std::string str);
  std::string remove(const std::string x);
  unsigned int hash(const std::string x);

private:
  int len = 0;
  struct Node content[ARRAY_LENGTH];
};

map::map() {
}

map::~map() {
}

void map::insert(const std::string str) {
  if (str == "") {
    std::cout << "map::insert() > Empty str." << std::endl;
    return;
  }

  const int h = hash(str);
  if (h == -1) {
    std::cout << "map::insert() > Hash function returned -1" << std::endl;
    return;
  }

  if (content[h].data.empty()) {
    content[h].data = str;
    len++;
  } else {
    if (content[h].prox == nullptr) {
      content[h].prox = new Node {str, nullptr};
      len++;
    } else {
      struct Node * nav = content[h].prox;
      while (nav->prox != nullptr) {
        nav = nav->prox;
      }

      nav->prox = new Node {str, nullptr};
      len++;
    }
  }
}

std::string map::remove(const std::string x) {
  std::string target = std::string();

  if (len < 1) {
    std::cout << "map::remove() > map is empty." << std::endl;
    return target;
  }

  const int h = hash(x);
  
  if (content[h].data == x && content[h].prox == nullptr) {
    target = content[h].data;
    content[h].data = std::string();
    len--;
  }

  if (content[h].data != x && content[h].prox != nullptr) {
    struct Node * nav = content[h].prox;
    while (content[h].data != x && content[h].prox != nullptr) {
      nav = nav->prox;
    }

    if (nav->data == x && nav->prox != nullptr) {
      struct Node * prox_node = nav->prox;
      std::string target = nav->data;

      nav->prox = prox_node->prox;
      nav->data = prox_node->data;
      
      len--;
      delete prox_node;
    }   
  }
  
  return target;
}

unsigned int map::hash(const std::string x) {
  if (x.empty()) {
    std::cout << "map::hash() > string empty." << std::endl;
    return -1;
  }

  unsigned int h = 1;
  for (int i = 0; i < x.length(); i++) {
    unsigned int t = x.at(i) * pow(3.0, (double)i);
    h += t;  
  }

  return h % ARRAY_LENGTH;
}

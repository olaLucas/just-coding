#include <iostream>
#include <string>
#include "lib/map.cpp"

int main(void) {
  map m;

  std::cout << "hash: " << m.hash("orlando") << std::endl;
  std::cout << "hash: " << m.hash("odnalro") << std::endl;
  
  return 0;
}

#include <iostream>
#include <ostream>
#include <string>
#include "lib/map.cpp"

int main(void) {
  map m;
  
  m.insert("Lucas Santos Silva");
  std::cout << "remove: " << m.remove("Lucas Santos Silva") << std::endl;

  return 0;
}

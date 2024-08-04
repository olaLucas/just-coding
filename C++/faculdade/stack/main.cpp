#include <cstdio>
#include <iostream>
#include <ostream>
#include "lib/stack.cpp"

void print_stack(Stack * s){
  for (int i = 0; i < s->get_len(); i++) {
    std::cout << "Value: " << s->pop() << std::endl;
  }  
}

int main(void) {
  int array[] = {10, 20, 30, 40, 50};
  int arr_size = sizeof(array) / sizeof(int);
  Stack p;
  
  std::cout << "arr_size: " << arr_size << std::endl; 
  for (int i = 0; i < arr_size; i++) {
    p.insert(array[i]);
  }

  print_stack(&p);

  return 0;
} 

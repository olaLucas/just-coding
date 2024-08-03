#include <cstdio>
#include <iostream>
#include "lib/stack.cpp"

int main(void) {
  int array[] = {10, 20, 30, 40, 50};
  Stack p();
  
  printf("%d", p.get_beg()->get_data());
  p.pop(); 

  return 0;
} 

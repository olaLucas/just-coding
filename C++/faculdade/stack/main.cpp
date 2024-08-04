#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include "lib/stack.cpp"

#define ARRAY_SIZE 1024
#define RANGE 100000000

void filling_array(int array[]) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    array[i] = rand();  
  }
}

void print_arr(const int array[]) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("%d: %d\n", i, array[i]); 
  }
}

int main(void) {
  
  int array[ARRAY_SIZE];
  filling_array(array);  
  
  Stack p;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    p.insert(array[i]);
  }

  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("popping %d: %d\n", i, p.pop()); 
  }

  return 0;
} 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
  int n = 0;

  if (argc > 1) {
    n = atol(argv[1]);
  } else {

    puts("Insira o valor de N:");
    scanf("%d", &n);
  }

  int resultForm = (n * (n + 1) * (2 * n + 1)) / 6;
  int resultPuro = 0;

  for (int i = 1; i <= n; i++) {
    resultPuro += i * i;
  }

  printf("resultado formula: %d\n\n", resultForm);
  printf("resultado puro: %d\n\n", resultPuro);

  return 0;
}

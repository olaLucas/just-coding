#if !defined(INCLUDES)
  #define INCLUDES
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdbool.h>
#endif

#include "../lib/fila.h"

#define STR_SIZE 150
#define STD_SIZE_NUM 11

struct aluno {
  char * nome;
  char * numero;
	int idade;
};

bool check_numero(const char numero[]) {
  if (strlen(numero) < STD_SIZE_NUM) {
    fprintf(stderr, "strlen() < STD_SIZE_NUM\n\n");
    return false;
  }

  if (strcmp(numero, "") == 0) {
    fprintf(stderr, "check_numero: strcmp(numero, \"\") == 0\n\n");
    return false;
  }
  
  return true;
}

bool check_nome(const char nome[]) {
	  if (strlen(nome) <= 0) {
    fprintf(stderr, "strlen(nome) <= 0");
    return false;
  }

  return true;
}

struct aluno init_aluno(const char nome[], int idade, const char numero[]) 
{
  struct aluno x;
  if (idade > 0 && idade < 130) {
    x.idade = idade;
  } else { 
    printf("idade inválida: %d\n\n", idade);   
  }

  if (check_numero(numero)) {
    x.numero = (char *)calloc(strlen(numero), sizeof(char));
    strcpy(x.numero, numero);
  } else {
    printf("número inválido.\n");
  }

  if (check_nome(nome)) {
    x.nome = (char *)calloc(STR_SIZE, sizeof(char));
    strcpy(x.nome, nome);
  } else {
    printf("nome inválido.\n");
  }

  return x; 
}

void del_aluno(struct aluno * x) {
  if (x->nome) {
    free(x->nome);
  } else {
    x->nome = NULL;
  }

  if (x->numero) {
    free(x->numero);
  } else {
    x->numero = NULL;
  }
}

// adicionar argumentos de terminal. ex: --add fulano
int main(void) {
  printf("Hello, world!\n");
  return 0;
}

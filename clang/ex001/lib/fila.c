#if !defined (INCLUDES)
  #define INCLUDES
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdbool.h>
#endif


struct aluno {
  char * nome;
  char * numero;
  int idade;
};

struct node {
  struct aluno aln;
  struct node * prox;
};


bool init_node(struct node * x, const struct aluno aln) {
  x = (struct node *)calloc(1, sizeof(struct node));
	if (x == NULL) {
    fprintf(stderr, "memória insuficiente para alocar um novo nó.\n\n");
    // criar um fork (novo processo) que salva os dados da fila atual e fecha o programa
  	return false;
	} else {
    x->aln = aln;
		x->prox = NULL;
		return true;
  }
}


bool inserir_fila(struct node * inicio, const struct aluno aln) {
  if (inicio) { // fila não esta vazia
    struct node * nav = inicio;
    
    while (nav->prox != NULL) {
      nav = nav->prox;
    }

    struct node * temp = NULL; 
    if (init_node(&nav->prox, aln)) { // temp foi alocado
      printf("nó alocado com sucesso");
      return true;
    } else { // temp não foi alocado
      fprintf(stderr, "inserir_fila(): temp == NULL");
      return false;
    }
  } else { // fila está vazia
    if (init_node(&(*inicio), aln)) { // temp foi alocado
      return true;
    } else { // temp não foi alocado
      fprintf(stderr, "inserir_fila(): temp == NULL");
      return false;
    }
  }
}

struct aluno * procurar_fila(const struct node * inicio,  const char key[]) {
  if (inicio) {
    if (strlen(key) > 0) {    
      struct node * nav = inicio;
      while (nav->prox != NULL) {
        if (strcmp(nav->aln.nome, key) == 0) {
          return nav->aln;
        } else {
          nav = nav->prox;
        }
      }
    } else {
      fprintf(stderr, "procurar_fila(): strlen(key) > 0");
      return NULL;
    }
  } else {
    fprintf(stderr, "procurar_fila(): inicio == NULL\n\n");
    return NULL;
  }
}

bool excluir_fila(struct node * inicio, const char key[]) {
  if (inicio) {
    if (strlen(key) > 0) {
      if (strcmp(inicio->aln.nome, key) == 0) {
        if (inicio->prox) {
					struct node * prox = inicio->prox;
					inicio->aln = prox->aln;
					inicio->prox = prox->prox;
					free(prox);				
					return true;
				} else {
					struct node * nav = inicio;
					struct node * ant = NULL;
					while (nav->prox != NULL) {
						ant = nav;
						nav = nav->prox;
						if (strcmp(nav->aln.nome, key) == 0) {	
							if (nav->prox) {
								struct node * prox = nav->prox;
								nav->aln = prox->aln;
								nav->prox = prox->prox;
								free(prox);
								return true;
							} else { // ultimo nó
								free(nav);
								return true;
							}
						}
					}
				}
			}
  	} else { // key vazia
			fprintf(stderr,  "excluir_fila(): strlen(key) <= 0");
			return false;
  	}
	} else { // fila fazia
		fprintf(stderr, "excluir_fila(): inicio == NULL");
		return false;
	}
}

// usar ponteiro para função imprimir_aluno()
void print_fila(const struct node * inicio, void * printFunc) {
	if (inicio) {
		struct node * nav = inicio;
		while (nav->prox != NULL) {
			(*printFunc)(nav);
			nav = nav->prox;
		}		
	} else {
		fprintf(stderr, "print_fila(): inicio == NULL.\n\n");
		return;
	}
}


#include <stdio.h>
#include <stdlib.h>

#define SIZE_ARRAY 10
#define RAND_GRANDEZA 1000

typedef struct node
{
	int dado;
	struct node * esquerdo;
	struct node * direito;
} node;

typedef node * ptr_node;

typedef struct arvore
{
	int qtdNodes;
	int tamanho;
	struct node * inicio;
} arvore;


void swap();
arvore init_arv();
ptr_node init_node();
void init_array();

ptr_node inserir();
void buscar();
void exibir_emOrdem();
void exibir_node();
ptr_node excluir();


void swap(int * x, int * y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

arvore init_arv()
{
	arvore arv;
	arv.inicio = NULL;
	arv.qtdNodes = 0;
	arv.tamanho = 0;

	return arv;
}

ptr_node init_node(const int numero)
{
	ptr_node x = (ptr_node)malloc(sizeof(ptr_node));
	x->dado = numero;
	x->esquerdo = NULL;
	x->direito = NULL;

	return x;
}

void init_array(int array[])
{
	for (int i = 0; i < SIZE_ARRAY; i++)
		array[i] = (rand() % RAND_GRANDEZA);
}


ptr_node inserir(ptr_node raiz, const int numero)
{
	if (raiz == NULL)
	{	
		puts("Inserção: Elemento adicionado.");
		raiz = init_node(numero);
	}
	else
	{
		if (numero < raiz->dado)
		{
			puts("Inserção: Iterando à esquerda.");
			raiz->esquerdo = inserir(raiz->esquerdo, numero);
		}
		else if (numero > raiz->dado)
		{
			puts("Inserção: Iterando à direita.");
			raiz->direito = inserir(raiz->direito, numero);
		}
	}

	return raiz;
}

void buscar(ptr_node raiz, const int alvo)
{
	if (raiz == NULL)
	{
		puts("Busca: elemento não encontrado.");
		return;
	}
	else if (raiz->dado == alvo)
	{
		puts("Buscar: Elemento encontrado.");
		printf("Dado %d", raiz->dado);
	}
	else if (alvo < raiz->dado)
	{
		puts("Buscar: Iterando à esquerda.");
		buscar(raiz->esquerdo, alvo);
	}
	else if (alvo > raiz->dado)
	{
		puts("Buscar: Iterando à direita");
		buscar(raiz->direito, alvo);
	}
}

void exibir_emOrdem(ptr_node raiz)
{
	if (raiz == NULL)
		return;
	
	exibir_emOrdem(raiz->esquerdo);
	printf("%d ", raiz->dado);
	exibir_emOrdem(raiz->direito);
}

ptr_node excluir(ptr_node raiz, const int numero)
{
	if (raiz == NULL)
	{
		puts("Elemento não encontrado.");
		return NULL;
	}

	if (numero == raiz->dado) // elemento encontrado
	{
		if (raiz->esquerdo == NULL && raiz-> direito == NULL) // raiz sem nós adjacentes
		{
			puts("Excluindo elemento sem nós adjacentes");
			free(raiz);
			return NULL;
		}
		else if (raiz->esquerdo != NULL ^ raiz->direito != NULL) // raiz com um nó adjacente
		{
			ptr_node aux = NULL;
			if (raiz->esquerdo != NULL)
			{
				puts("Exclusão: salvando nó a esquerda excluindo raiz.");
				aux = raiz->esquerdo;
				free(raiz);
				return aux;
			}
			else if (raiz->direito != NULL)
			{
				puts("Exclusão: salvando nó a direita e excluindo raiz.");
				aux = raiz->direito;
				free(raiz);
				return aux;
			}
		}
		else if (raiz->esquerdo != NULL && raiz->direito != NULL) // raiz com dois nós adjacente
		{
			ptr_node nodeTrocar = raiz->esquerdo;
			while (nodeTrocar->direito != NULL)
				nodeTrocar = nodeTrocar->direito;
				
			swap(&raiz->dado, &nodeTrocar->dado);
			raiz->esquerdo = excluir(raiz->esquerdo, numero);

			return raiz;
		}
	}
	else
	{
		if (numero < raiz->dado) // navegando pela arvore
		{
			puts("Exclusão: Iterando à esquerda.");
			raiz->esquerdo = excluir(raiz->esquerdo, numero);
		}
		else if (numero > raiz->dado)
		{
			puts("Exclusão: Iterando à direita.");
			raiz->direito = excluir(raiz->direito, numero);
		}
	}

	return raiz;
}

int main(void)
{
	int array_rand[SIZE_ARRAY]; init_array(array_rand);
	arvore arv = init_arv();

	for (int i = 0; i < 10; i++)
		arv.inicio = inserir(arv.inicio, array_rand[i]);


	arv.inicio = excluir(arv.inicio, array_rand[rand() % SIZE_ARRAY]);

	printf("Elementos: "); exibir_emOrdem(arv.inicio); puts("\n");

	buscar(arv.inicio, array_rand[rand() % SIZE_ARRAY]);

	return 0;
}
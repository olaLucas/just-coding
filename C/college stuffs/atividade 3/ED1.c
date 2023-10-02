#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int dado; 
  struct no *proximo; 
} *ptr_node;

ptr_node inicio = NULL;
int counter = 1;

void inicializar();
void inserir(ptr_node inicio);
void excluir(ptr_node inicio);
void exibir_arvore(ptr_node inicio);
void menu();
void cleanBuffer();
void procedimento(int num);

int main(void)
{    
    //inicializar();

    menu();
    return 0;
}

void menu()
{
    int seletor = -1;
    while (seletor != 0)
    {
        system("clear");
        exibir_arvore(inicio);
        
        printf("\nSelecione uma opção: \n\n");
        printf("1. Inserir dados.\n");
        printf("2. Excluir dados.\n");
        printf("3. Exibir dados.\n");
        printf("4. Procedimento \n");
        printf("0. Sair.\n");
        
        printf("\n >>> ");
        scanf("%d", &seletor);

        switch (seletor)
        {
        case 1:
            inserir(inicio);
            break;

        case 2:
            excluir(inicio);
            break;

        case 3:
            exibir_arvore(inicio);
            break;

        case 4:
            int numero = 0;
            printf("Insira um numero: \n\n>>>");
            scanf("%d", &numero);
            procedimento(numero);
            break;
        
        default:
            printf("Opção inválida! Tente novamente. \n\n");
            cleanBuffer();
            getchar();
            break;
        }
    }
}

void inserir(ptr_node inicio)
{
    if (counter == 1)
    {
        inicializar();
    }
    else
    {
        while (inicio->proximo != NULL)
        {
            inicio = inicio->proximo;
        }

        inicio->proximo = (ptr_node)malloc(sizeof(ptr_node));
        inicio = inicio->proximo;
        inicio->dado = counter;
        counter++;
        inicio->proximo = NULL;
    }
}

void excluir(ptr_node inicio)
{
    if (counter == 1)
    {
        system("clear");
        printf("Lista vazia, não há dados para excluir. \n\n");
        cleanBuffer();
        getchar();
        return;
    }

    int num;
    ptr_node atual;
    printf("Insira o número que deseja excluir: \n\n >>> ");
    scanf("%d", &num);

    if (num == inicio->dado)
    {
        if (counter == 2)
        {
            counter--;
            free(inicio);
            inicio = NULL;
            return;
        }
        else
        {
            counter--;
            atual = inicio;
            inicio = inicio->proximo;
            atual->dado = inicio->dado;
            atual->proximo = inicio->proximo;
            free(inicio);
            return;
        }
    }
    
    while (inicio->dado != num)
    {   
        if (inicio->proximo == NULL)
        {
            printf("Número não encontrado! \n\n");
            cleanBuffer();
            getchar();
            break;
        }
        else
        {
            atual = inicio;
            inicio = inicio->proximo;
        }
    }

    if (inicio->dado == num)
    {
        atual->proximo = inicio->proximo;
        counter--;
        free(inicio);
    }
}

void exibir_arvore(ptr_node inicio)
{   
    if (counter == 1)
    {
        printf("Pilha vazia, não há dados para exibir. \n\n");
        return;
    }
    
    printf("[ ");
    while (inicio->proximo != NULL)
    {
        printf("(Dado: %d | Próximo: %p )", inicio->dado, inicio->proximo);
        inicio = inicio->proximo;
    }

    printf("(Dado: %d | Próximo: %p )", inicio->dado, inicio->proximo);
    printf("]");
}

void inicializar()
{
    inicio = (ptr_node)malloc(sizeof(ptr_node));
    inicio->dado = counter;
    inicio->proximo = NULL;
    counter++;
}

void cleanBuffer()
{
    int c;
    while ((c = getchar()) != '\n');
}

void procedimento(int num)
{
    ptr_node aux, no = NULL; 
    if(inicio != NULL) // verifica se a lista não esta vazia (se a variavel aponta para algum lugar)
    { 
        if((inicio)->dado == num) // verifica se não é o primeiro elemento da lista
        { 
            no = inicio; 
            inicio = no->proximo; 

        }
        else
        { 
            aux = inicio; 
            while(aux->proximo != NULL && aux->proximo->dado != num) // percorre a lista em busca do numero
            {
                aux = aux->proximo;
            }
            
            if(aux->proximo != NULL) // verifica se proximo nó aponta para algum lugar
            { 
                no = aux->proximo; // faz "no" apontar para o numero selecionado para exclusão
                aux->proximo = no->proximo; // faz aux apontar para o elemento após "no"
            } 
        }  
    }

    if(no != NULL)
    {
        free(no); // exclui "no"
    }
}
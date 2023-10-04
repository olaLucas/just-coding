#ifndef INCLUDES
#define INCLUDES

    #include <stdlib.h>
    #include <stdio.h>

#endif


typedef struct node
{
    int info;
    struct node * esquerdo;
    struct node * direito;

} node;

typedef node * ptr_node;

void swap(int * x, int * y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

ptr_node init_node(int info_PARAM)
{
    ptr_node elemento = (ptr_node)malloc(sizeof(ptr_node));
    elemento->info = info_PARAM;
    elemento->esquerdo = NULL;
    elemento->direito = NULL;
    
    return elemento;
}

ptr_node inserir(ptr_node inicio, int number_PARAM)
{
    if (inicio == NULL)
        inicio = init_node(number_PARAM);

    else if (number_PARAM == inicio->info)
        puts("Número já adicionado.\n");

    else if (number_PARAM < inicio->info)
        inicio->esquerdo = inserir(inicio->esquerdo, number_PARAM);

    else if (number_PARAM > inicio->info)
        inicio->direito = inserir(inicio->direito, number_PARAM);
    
    return inicio;     
}

void buscar(ptr_node inicio, int number_PARAM)
{
    if (inicio == NULL)
        puts("Arvore vazia.\n");
    
    else if (number_PARAM == inicio->info)
        printf("\nEncontrado: %d | %p\n\n", inicio->info, *inicio);

    else if (number_PARAM < inicio->info)
        buscar(inicio->esquerdo, number_PARAM);
    
    else if (number_PARAM > inicio->info)
        buscar(inicio->direito, number_PARAM);
}

void exibir_node(ptr_node node)
{
    printf("ENDEREÇO: %p \n", *node);
    printf("INFO: %d \n", node->info);
    printf("ESQUERDO: %p \n", node->esquerdo);
    printf("DIREITO: %p \n", node->direito);
}

void exibir_emOrdem(ptr_node inicio)
{
    if (inicio == NULL)
        return;

    exibir_emOrdem(inicio->esquerdo);
    printf("%d ", inicio->info);
    exibir_emOrdem(inicio->direito);
}

ptr_node excluir(ptr_node inicio, int number_PARAM)
{
    if (inicio == NULL) 
    {
        printf("Arvore vazia ou elemento não encontrado.");
        return NULL;
    }
    
    if (number_PARAM != inicio->info)
    {
        if (number_PARAM < inicio->info)
        {
            inicio->esquerdo = excluir(inicio->esquerdo, number_PARAM);
        }
        else if (number_PARAM > inicio->info)
        {
            inicio->direito = excluir(inicio->direito, number_PARAM);
        }
    }
    else if (number_PARAM == inicio->info)
    {
        if (inicio->esquerdo == NULL && inicio->direito == NULL)
        {
            free(inicio);
            inicio = NULL;
        }
        else if (inicio->esquerdo == NULL ^ inicio->direito == NULL)
        {
            ptr_node prox = NULL;
            if (inicio->esquerdo != NULL)
            {
                prox = inicio->esquerdo;
                free(inicio);

                return prox;
            }
            else if (inicio->direito != NULL)
            {
                prox = inicio->direito;
                free(inicio);

                return prox;
            }
        }
        else if (inicio->esquerdo != NULL && inicio->direito != NULL)
        {
            ptr_node trocar = NULL;
            ptr_node anterior = NULL;

            trocar = inicio->esquerdo;
            while (trocar->direito != NULL)
            {
                anterior = trocar;
                trocar = trocar->direito;
            }
            
            swap(&inicio->info, &trocar->info);
            inicio->esquerdo = excluir(inicio->esquerdo, number_PARAM);
            
            return inicio;
        }
    }   

    return inicio;
}
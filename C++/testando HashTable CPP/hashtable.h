#if !defined(HASH_INCLUDES)
#define HASH_INCLUDES

#include <iostream>
#include <string>
#include <array>

#define ARRAY_TAM 20

using std::string;
using std::array;
using std::cout;
using std::cin;
using std::endl;

typedef struct node
{
    int info = -1;
    struct node * prox = NULL; 

} node;

typedef node * ptr_node;

#endif // HASH_INCLUDES


class hashtable
{
private:
    
    array<node, ARRAY_TAM> arrayHash;

public:
    hashtable();
    /* ~hashtable(); */

    ptr_node init_ptr_node(ptr_node elemento);
    node initNode(int info = -1, ptr_node prox = NULL);

    unsigned int defineIndex(unsigned int n);
    void inserir_dados(unsigned int n);
    void excluir_dados(unsigned int n);

    int getInfo(unsigned int x);
    ptr_node getProx(unsigned int x);
    
    void display_array();
    void display_node(node paramNode, int i = -1);
};

hashtable::hashtable()
{
}

ptr_node hashtable::init_ptr_node(ptr_node elemento)
{
    elemento = new node;
    return elemento;
}

node hashtable::initNode(int info, ptr_node prox)
{
    node temp;
    temp.info = info;
    temp.prox = prox;

    return temp;
}

unsigned int hashtable::defineIndex(unsigned int n)
{
    return n % ARRAY_TAM;
}

void hashtable::inserir_dados(unsigned int n)
{
    unsigned int key = defineIndex(n);
    if (arrayHash[key].info == -1)
    {
        arrayHash.at(key) = initNode(n);
    }
    else
    {
        ptr_node navegador = arrayHash[key].prox;
        if (navegador->prox == NULL)
        {
            navegador->prox = init_ptr_node(navegador->prox);
            *navegador->prox = initNode(n);
        }
        else
        {
            while (navegador->prox != NULL)
            {
                navegador = navegador->prox;
            }

            navegador->prox = init_ptr_node(navegador->prox);
            *navegador->prox = initNode(n);
        }
    }
}

void hashtable::excluir_dados(unsigned int n)
{
    unsigned int key = defineIndex(n);

    if (arrayHash[key].info == n) // caso seja o no principal
    {
        if (arrayHash[key].prox == NULL) // caso não tenha nós adjacentes
        {
            arrayHash.at(key) = initNode();
        }
        else if (arrayHash[key].prox->prox == NULL) // caso tenha somente 1
        {
            arrayHash[key].info = arrayHash[key].prox->info;
            delete arrayHash[key].prox;
            arrayHash[key].prox = NULL; 
        }
        else // caso tenha mais de um
        {
            arrayHash[key].info = arrayHash[key].prox->info;
            ptr_node temp = arrayHash[key].prox->prox;
            delete arrayHash[key].prox;
            arrayHash[key].prox = temp; 
        }
    }
    else if (arrayHash[key].prox->info == n) // caso seja o primeiro nó adjacente 
    {
        ptr_node navegador = arrayHash[key].prox;
        navegador->info = navegador->prox->info;
        navegador->prox = navegador->prox->prox;
    }
    else // procurando nos demais nós adjacentes
    {
        ptr_node atual;
        ptr_node navegador = arrayHash[key].prox;

        while (navegador->prox != NULL)
        {
            if (navegador->info == n)
            {
                atual->prox = navegador->prox;
                delete navegador;                
            }
            else
            {
                atual = navegador;
                navegador = navegador->prox;
            }
        }
    }
}

int hashtable::getInfo(unsigned int x)
{  
    return arrayHash.at(defineIndex(x)).info;   
}

ptr_node hashtable::getProx(unsigned int x)
{
    return arrayHash.at(defineIndex(x)).prox;   
}

void hashtable::display_array()
{
    for (int i = 0; i != arrayHash.size(); i++)
    {
        if (arrayHash[i].info != -1)
        {
            display_node(arrayHash.at(i), i);
            if (arrayHash[i].prox != NULL)
            {
                ptr_node navegador = arrayHash[i].prox; 
                while (navegador->prox != NULL)
                {
                    display_node(*navegador, i);
                    navegador = navegador->prox;
                }
            }   
        }
    }
}

void hashtable::display_node(node paramNode, int i)
{
    if (i == -1)
        cout << "\tNode adjacente: " << i << endl;
    else
        cout << "Node: " << i << endl;
    
    cout << "\tInfo: " << paramNode.info << endl;
    cout << "\tProx: " << paramNode.prox << endl;
}
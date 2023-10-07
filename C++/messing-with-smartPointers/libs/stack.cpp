#if !defined(INCLUDES)
#define INCLUDES

    #include <iostream>
    #include <memory>

#endif // INCLUDES

namespace node
{
    typedef struct node_struct
    {
        int info = -1;
        std::shared_ptr<node_struct> prox = nullptr;

    } node_struct;

} // namespace node

namespace pilha
{
    typedef struct pilha_struct
    {
        unsigned int tamanho;
        std::shared_ptr <node::node_struct> inicio = nullptr;
        std::shared_ptr <node::node_struct> fim = nullptr;

        pilha_struct() : tamanho(0), inicio(nullptr), fim(nullptr) {};
        pilha_struct(pilha_struct &p) : tamanho(p.tamanho), inicio(p.inicio), fim(p.inicio) {};

        pilha_struct operator = (pilha_struct p)
        {
            pilha_struct temp;
            temp.tamanho = p.tamanho;
            temp.inicio = p.inicio;
            temp.fim = p.fim;

            return p;
        }

    } pilha_struct;

    pilha::pilha_struct inserir(pilha_struct p, const int numero);
    void exibir_node(std::shared_ptr <node::node_struct> p);
    void exibir(pilha_struct p);
    void buscar(pilha_struct p, const int numero);
    void excluir(pilha_struct p);

} // namespace pilha


pilha::pilha_struct pilha::inserir(pilha::pilha_struct p, const int numero)
{
    if (p.inicio == nullptr)
    {
        p.tamanho++;
        p.inicio = std::shared_ptr<node::node_struct> (new node::node_struct {numero, nullptr});
        p.fim = p.inicio;
        std::cout << "INSERIR: pilha inicializada: " << p.inicio->info << std::endl;
    }
    else
    {
        std::shared_ptr <node::node_struct> navegador = p.inicio;
        while (navegador->prox != nullptr)
            navegador = navegador->prox;

        navegador->prox = std::shared_ptr <node::node_struct> (new node::node_struct {numero, nullptr});
        p.fim = navegador->prox;
        std::cout << "INSERIR: elemento adicionado: " << navegador->prox->info << std::endl;
    }

    return p;
}

void pilha::exibir_node(std::shared_ptr <node::node_struct> p)
{
    std::cout << p->info << " ";
}

void pilha::exibir(pilha::pilha_struct p)
{
    if (p.inicio == nullptr)
    {
        std::cout << "Pilha vazia." << std::endl;
        return;
    }

    std::shared_ptr <node::node_struct> navegador = p.inicio;
    while (navegador->prox != nullptr)
    {
        exibir_node(navegador);
        navegador = navegador->prox;
    }

    exibir_node(navegador);
}

void pilha::buscar(pilha::pilha_struct p, const int numero)
{
    std::shared_ptr <node::node_struct> navegador = p.inicio;
    while (navegador->info != numero || navegador->prox == nullptr)
    {
        navegador = navegador->prox;
    }
    
    if (navegador->info == numero)
        exibir_node(std::move(navegador));
    else
        std::cout << "Elemento não encontrado. " << std::endl;        
}

void pilha::excluir(pilha::pilha_struct p)
{
    if (p.inicio == nullptr)
    {
        std::cout << "Pilha vazia, nenhum elemento para retirar." << std::endl;
        return;
    }
    else if (p.inicio->prox == nullptr)
    {
        std::cout << "EXCLUIR: Removendo " << p.inicio->info << " da pilha." << std::endl;
        p.inicio.reset();
        return;
    }
    else
    {
        std::shared_ptr <node::node_struct> navegador = p.inicio;
        while (navegador->prox->prox != nullptr)
        {
            navegador = navegador->prox;
        }
        
        std::cout << std::endl << "EXCLUIR: Removendo " << navegador->prox->info << " da pilha." << std::endl;
        p.fim = navegador;
        navegador->prox.reset();
    }
}
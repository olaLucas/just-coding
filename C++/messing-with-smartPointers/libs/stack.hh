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
        std::shared_ptr<node::node_struct> inicio;
        std::shared_ptr<node::node_struct> fim;

        pilha_struct() : tamanho(0), inicio(nullptr), fim(nullptr) {};
        pilha_struct(pilha_struct &p) : tamanho(p.tamanho), inicio(p.inicio), fim(p.fim) {};

        pilha_struct & operator = (pilha_struct p)
        {
            tamanho = p.tamanho;
            inicio = p.inicio;
            fim = p.fim;
            return *this;
        }

    } pilha_struct;

    pilha_struct inserir(pilha_struct p, const int numero);
    void exibir(pilha_struct p);
    void buscar(pilha_struct p, const int numero);
    void excluir(pilha_struct p);

} // namespace pilha
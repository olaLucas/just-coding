typedef struct node node;

typedef node * ptr_node;

ptr_node init_node(int info_PARAM);
ptr_node inserir(ptr_node inicio, int number_PARAM);
void buscar(ptr_node inicio, int number_PARAM);
void exibir_node(ptr_node node);
void exibir_emOrdem(ptr_node inicio);
ptr_node excluir(ptr_node inicio, int number_PARAM);
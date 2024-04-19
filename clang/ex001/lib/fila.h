struct node;

extern bool init_node(struct aluno aln);

extern bool inserir_fila(struct node * inicio, struct aluno aln);

extern struct aluno * procurar_fila(const struct node * inicio, const char key[]);

extern bool excluir_fila(const struct node * inicio, const char key[]);

extern void print_fila(const struct node * inicio, void * printFunc);

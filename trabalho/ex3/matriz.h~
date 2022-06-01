#include <stdlib.h>
#include <stdio.h>

struct lista
{
	int coluna;
	int linha;
	int info;
	struct lista* prox;
};


struct identidade
{
	int ordem;
	struct lista* prim;
};

typedef struct lista Lista;
typedef struct identidade Identidade;

Lista* cria_lista(void);
Lista* insere_lista(Lista *l, int info,int col, int lin);
void inicializa_matriz(Identidade *id, Lista *l);
void imprime_matriz(Identidade *id);
void mostra_elementos(Identidade *id);


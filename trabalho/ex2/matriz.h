#include <stdio.h>
#include <stdlib.h>

struct lista
{
	int linha;
	int coluna;
	int info;
	struct lista* prox;
};

struct esparca
{
	int linhas;
	int colunas;
	struct lista *prim;
};

typedef struct lista Lista;
typedef struct esparca Esparca;

Lista *cria_lista(void);
Lista *inicializa_matriz(Lista *l,Esparca *e);
void imprime_matriz(Esparca *e);
Lista *insere_lista(Lista *l,int info,int col,int lin);
void consulta_matriz( Esparca *e);
void somatorio_linha(Esparca *e);
void percentual(Esparca *e);

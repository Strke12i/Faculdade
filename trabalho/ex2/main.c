#include "matriz.h"

int main()
{
	Esparca e;
	Lista *l;

	fprintf(stdout,"Digite o tamanho da matriz(coluna X linhas):");
	scanf("%d %d",&e.colunas,&e.linhas);
	l = cria_lista();
	l = inicializa_matriz(l,&e);
	e.prim = l;
	imprime_matriz(&e);
	consulta_matriz(&e);
    somatorio_linha(&e);
	percentual(&e);

	return 0;
}

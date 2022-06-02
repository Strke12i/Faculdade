#include "matriz.h"

int main()
{
	Esparca e;
	Lista *l;

	l = cria_lista();
	inicializa_matriz(l,&e);
	imprime_matriz(&e);
	consulta_matriz(&e);
    somatorio_linha(&e);
	percentual(&e);
	deleta(&e);

	return 0;
}

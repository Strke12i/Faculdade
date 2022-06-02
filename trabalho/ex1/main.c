#include "matriz.h"

int main()
{
	Diagonal d;
	cria_matriz(&d);
	inicializa_matriz(&d);
	imprime_matriz(&d);
	consulta_matriz(&d);
	deleta(&d);

	return 0;

}

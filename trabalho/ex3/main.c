#include "matriz.h"

int main()
{
	Identidade id;
	Lista *l;
	l = cria_lista();
	inicializa_matriz(&id,l);
	imprime_matriz(&id);
	mostra_elementos(&id);
}

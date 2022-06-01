#include "matriz.h"

int main()
{
	Identidade id;
	Lista *l;
	
	fprintf(stdout,"Defina a ordem da matriz:");
	scanf("%d",&id.ordem);

	l = cria_lista();
	inicializa_matriz(&id,l);
	imprime_matriz(&id);
	mostra_elementos(&id);
}

#include "matriz.h"

int main()
{
	Diagonal d;
	int i,j;
	fprintf(stdout,"Informe a ordem de sua matriz:");
	scanf("%d",&d.ordem);

	cria_matriz(&d);
	inicializa_matriz(&d);
	imprime_matriz(&d);
	fprintf(stdout,"Informe a posição[x,y] para encontrar o elemento na matriz:");
	scanf("%d %d",&i,&j);
	consulta_matriz(&d,i,j);

	return 0;

}

#include <stdio.h>
#include <stdlib.h>

struct diagonal{
	int ordem;
	int *v;
};

typedef struct diagonal Diagonal;

void cria_matriz(Diagonal *d);
void inicializa_matriz(Diagonal *d);
void imprime_matriz(Diagonal *d);
void consulta_matriz(Diagonal *d,int linha,int col);


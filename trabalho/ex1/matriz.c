#include "matriz.h"

void cria_matriz(Diagonal *d)
{
	fprintf(stdout,"Informe a ordem de sua matriz:");
	scanf("%d",&d->ordem);
	if(d->ordem > 0)
	{
		d->v = malloc(sizeof(int)*d->ordem);
		return;
	}
	fprintf(stdout,"Numero invalido para ordem!");
	exit(1);
}

void inicializa_matriz(Diagonal *d)
{
	fprintf(stdout,"Digite os numeros da diagonal da matriz:\n");
	for(int i =0; i < d->ordem ; i++)
		scanf("%d",&d->v[i]);
}

void imprime_matriz(Diagonal *d)
{
	for(int i = 0; i < d->ordem; i++)
	{
		for(int j = 0; j < d->ordem; j++)
		{
			if( i == j)	
				fprintf(stdout,"%d ",d->v[i]);
			else
				fprintf(stdout,"0 ");
		}
		fprintf(stdout,"\n");
	}
}

void consulta_matriz(Diagonal *d)
{
	int linha,col;
	fprintf(stdout,"Informe a posição(l c) para encontrar o elemento na matriz(elementos começam no [0,0]):");
	scanf("%d %d",&linha,&col);
	if(linha >= d->ordem || col >= d->ordem)
	{
		fprintf(stdout,"Coordenadas inválidas");
		return;
	}

	if(linha != col )
	{
		fprintf(stdout,"Elemento na posição[%d,%d]: 0",linha,col);
		return;
	}

	fprintf(stdout,"Elemento na posição[%d,%d]: %d",linha,col,d->v[linha]);
}

void deleta(Diagonal *d)
{
	free(d->v);
}

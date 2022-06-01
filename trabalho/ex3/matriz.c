#include "matriz.h"

Lista *cria_lista()
{
	return NULL;
}

Lista *insere_lista(Lista *l,int info, int col,int lin)
{
	Lista* nl = (Lista*)malloc(sizeof(Lista));
	nl->info = info;
	nl->coluna = col;
	nl->linha = lin;
	nl->prox = l;
	return nl;
}

	void inicializa_matriz(Identidade *id, Lista *l)
{
	int n;
	fprintf(stdout,"Digite os valores em ordem da matriz:\n");
	for(int i = 0; i < id->ordem; i++)
	{
		for(int j = 0; j < id->ordem; j++)
		{
			scanf("%d",&n);
			if(n!=0) 
				l = insere_lista(l,n,j,i);
		}
	}
	id->prim = l;
}

int coordenadas_existem(Lista *l,int i,int j)
{
	for(Lista *p=l;p!=NULL;p=p->prox)
	{
		if(p->linha==i && p->coluna==j)
			return p->info;
	}
	return 0;
}

void imprime_matriz(Identidade *id)
{
	for(int i = 0; i < id->ordem; i++)
	{
		for(int j = 0; j < id->ordem; j++)
		{
			fprintf(stdout,"%d ",coordenadas_existem(id->prim,i,j));
		}
		fprintf(stdout,"\n");
	}
}

void mostra_elementos(Identidade *id)
{
	for(Lista *p = id->prim; p!=NULL; p = p->prox)
	{
		if(p->linha != p->coluna)
			fprintf(stdout,"Elemento %d[%d,%d] fora da posição de diagonal\n",p->info,p->linha,p->coluna);
		
		else if(p->info != 1)
			fprintf(stdout,"Elemento %d[%d,%d] não bate com com o valor 1\n",p->info,p->linha,p->coluna);

	}
}

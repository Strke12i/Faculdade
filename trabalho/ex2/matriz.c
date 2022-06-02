#include "matriz.h"
   
Lista *cria_lista(void)
{
	return NULL;
}

Lista *insere_lista(Lista *l, int info, int col,int lin)
{
	Lista *nl = (Lista*)malloc(sizeof(Lista));
	nl->info = info;
	nl->linha = lin;
	nl->coluna = col;
	nl->prox = l;

	return nl;
}


void *inicializa_matriz(Lista *l,Esparca *e)
{
	int n;
	fprintf(stdout,"Digite o tamanho da matriz(linhas colunas):");
	scanf("%d %d",&e->linhas,&e->colunas);
	if(e->linhas <= 0 || e->colunas <= 0)
	{
		fprintf(stdout,"Tamanho inválido para a matriz");
		exit(1);
	}

	fprintf(stdout,"Digite em ordem os valores de sua matriz:\n");
	
	for(int i = 0; i < e->linhas; i++)
	{
		for(int j = 0; j < e-> colunas;j++)
		{
			scanf("%d",&n);
			if(n!=0)
				l = insere_lista(l,n,j,i);
		}
	}
	e->prim = l;
}

int coordenadas_existem(Lista *l,int i,int j)
{
	for(Lista *p=l;p!=NULL;p=p->prox)
	{
		if(i==p->linha && j == p->coluna)
		{
			return p->info;
		}
	}
	return 0;
}

void imprime_matriz(Esparca *e)
{
	for(int i = 0; i < e->linhas; i++)
	{
		for(int j = 0; j < e->colunas; j++)
		{
			fprintf(stdout,"%d ",coordenadas_existem(e->prim,i,j));	
		}
		fprintf(stdout,"\n");
	}
}

void consulta_matriz(Esparca *e)
{
	int col,lin;
	fprintf(stdout,"Digite a linha e coluna do matriz que deseja consultar:\n");
	scanf("%d %d",&col,&lin);
	if(!(col < e->colunas && lin < e->linhas))
	{
		fprintf(stdout,"Posição inválida na matriz\n");
		exit(1);
	}
	fprintf(stdout,"O elemento na posição[%d,%d] é :%d\n",col,lin,coordenadas_existem(e->prim,col,lin));	
}

void somatorio_linha(Esparca *e)
{
	int soma = 0,linha;
	fprintf(stdout,"Digite a linha que deseja fazer o somatório:");
	scanf("%d",&linha);
	if(linha>= e->linhas)
	{
		fprintf(stdout,"Linha inválida na matriz");
		exit(1);
	}
	for(Lista *p=e->prim;p!=NULL;p=p->prox)
	{
		if(p->linha == linha)
			soma += p->info;
	}
	fprintf(stdout,"O somatório da linha %d é igual á %d\n",linha,soma);
}

void percentual(Esparca *e)
{
	int c = 0;
	for(Lista *p=e->prim;p!=NULL;p=p->prox)
		c++;
	int total_matriz = e->linhas * e-> colunas;
	float p = ((float)c/total_matriz) * 100;
	fprintf(stdout,"O percentual de não-nulos é %.2f\n",p);
}

void deleta(Esparca *e)
{
	Lista *p = e->prim;
	while(p!=NULL)
	{
		Lista *aux = p->prox;
		free(p);
		p = aux;
	}	
}

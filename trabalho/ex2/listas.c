#include "listas.h>"

Lista *cria_lista(void)
{
	return NULL;
}

Lista *insere_lista(Lista *l, int info, int col,int linha)
{
	Lista *nl = (Lista*)malloc(sizeof(lista));
	nl->info = info;
	nl->linha = lin;
	nl->coluna = col;
	nl->prox = l;

	return nl;
}


Lista *inializa_matriz(Lista *l,Esparca *e)
{
	int n;
	for(int i = 0; i < e->colunas; i++)
	{
		for(int j = 0; j < e-> linhas)
		{
			scanf("%d",&n);
			if(n!=0)
				l = insere_lista(l,n,i,j);
		}
	}
	return 0;
}

void imprime_matriz(Lista *l,Esparca *e)
{
	for(int i = 0; i < e->colunas; i++)
	{
		for(int j = 0; j < e->linhas; i++)
		{
			for(Lista *p=l;p!=NULL;p=p->prox)
			{
				if(i==p->coluna && j == p->linha)
					fprintf(stdout," %d ",p->info);
				else fprintf(stdout," 0 ");
			}
		}
	}
}

void consulta_matriz(Lista *l,int col,int lin)
{
	for(Lista *p=l;p!=NULL;p=p->prox)
	{
		if(col == p->coluna && lin == p->linha)
		{
			fprintf(stdout,"O elemento na posição[%d,%d]:%d\n",col,lin,p->info);
			return;
		}
	}
	fprintf(stdout,"O elemento na posição[%d,%d]:0\n");
}

void somatorio_linha(Lista *l, int linha)
{
	int soma = 0;
	for(Lista *p=l;p!=NULL;p=p->prox)
	{
		if(p->linha == linha)
			sum += p->info;
	}
	fprintf(stdout,"O somatório da linha %d é igual á %d\,",linha,soma);
}

void percentual(Lista *l, Esparca *e)
{
	int c = 0;
	for(Lista *p=l;p!=NULL;p=p->prox)
		c++;
	int total_matriz = e->linhas * e-> colunas;
	float p = ((float)c/total_matriz) * 100;
	fprintf("O percentual de não-nulos é %.2f\n",p);
}

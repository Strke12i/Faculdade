#include "heap.h"

Heap* cria_heap(int tamanho)
{
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->tamanho = tamanho;
	h->fila=(int*)malloc(sizeof(int)*tamanho);
	h->pos = 0;
	return h;
}

int pos_pai(int posicao)
{
	return ((posicao - 1) / 2);
}
int pos_filho_esq(int posicao)
{
	return ((posicao * 2) + 1);
}
int pos_filho_dir(int posicao)
{
	return ((posicao * 2) + 2);
}

void insere_heap(Heap* h, int n)
{
	if(h == NULL)
	{
		fprintf(stdout,"Fila não foi inicializada\n");
		return;
	}
	if(h->pos == h->tamanho) 
	{
		fprintf(stdout,"Heap chegou ao seu limite de %d elementos\n",h->tamanho);
		return;
	}

	// inserir na primeira posição vaga do Array
	h->fila[h->pos] = n;
	h->pos++;

	// Levar o elemento inserido na sua respectiva posição de acordo com a prioridade

	balanceia_insercao_heap(h);
}

void balanceia_insercao_heap(Heap* h)
{
	//Pega o valor ultima posição a ser inserida no array
	int i = h->pos - 1;
	
	// Vai comparar o valor de i com o valor de seu pai, caso tenha pai
	while( i != 0 && (h->fila[pos_pai(i)] < h->fila[i]))
	{
		// Faz a troca dos valores
		int tmp = h->fila[pos_pai(i)];
		h->fila[pos_pai(i)] = h->fila[i];
		h->fila[i] = tmp;

		i = pos_pai(i);
	}
}


void imprime_heap(Heap* h)
{	
	if( h == NULL || h->pos == 0)
	{
		fprintf(stdout,"Não pode imprimir heap vazio\n");
		return;
	}
	
	int i = 0;
	// Enquanto i for diferente do valor do ultimo inserido
	while(1)
	{
		if( i != h->pos)
		{
			// Printa o valor i na fila
			fprintf(stdout,"Pai %d ..",h->fila[i]);
			// Vai verificar se o valor de i possui filhos
			if(pos_filho_esq(i) < h->pos)
				fprintf(stdout,"Esq %d ..",h->fila[pos_filho_esq(i)]);	
			if(pos_filho_dir(i) < h->pos)
				fprintf(stdout,"Dir %d ..",h->fila[pos_filho_dir(i)]);
				
			fprintf(stdout,"\n");
			i++;
		}else break;
	}
	
	//Printa a fila em ordem
	fprintf(stdout,"Fila em ordem de prioridade:");
	for(i = 0; i < h->pos; i++)
		fprintf(stdout,"%d ",h->fila[i]);
	fprintf(stdout,"\n");
}

void remove_heap(Heap* h,int *valor)
{
	if( h == NULL || h->pos == 0)
	{
		fprintf(stdout,"Não pode remover de fila sem nenhum elemento\n");
		return;
	}
	
	// Vai passar para o pointer o valor da posição max
	*valor = h->fila[0];
	h->pos--;

	if( h->pos == 0) return;

	// Faz a troca do primeiro pelo ultimo elemento
	h->fila[0] = h->fila[h->pos];
	
	balanceia_remocao_heap(h, 0);
	
}

void balanceia_remocao_heap(Heap* h, int pos)
{
	// Recebe a posição de recursão
	int i = pos;
	
	// Compara se a posição do filho existe e se o valor do filho é maior que a do pai
	if((h->pos > pos_filho_esq(pos)) && (h->fila[pos_filho_esq(pos)] > h->fila[pos]))
		i = pos_filho_esq(pos);
	if((h->pos > pos_filho_dir(pos)) && (h->fila[pos_filho_dir(pos)] > h->fila[i]))
		i = pos_filho_dir(pos);
	
	//Faz a troca dos valores
	if(i != pos)
	{
		int tmp = h->fila[i];
		h->fila[i] = h->fila[pos];
		h->fila[pos] = tmp;
		balanceia_remocao_heap(h,i);
	}
}


int consulta_heap(Heap* h,int n,int* pos)
{
	if(h == NULL || h->pos == 0)
	{
		fprintf(stdout,"Não é possivel procurar elemento em heap vazio\n");
		return 0;
	}

	for(int i = 0; i < h->pos; i++)
	{
		if(n == h->fila[i])
		{
			*pos = i;
			return 1;
		}
	}
	
	return 0;

}

void libera_heap(Heap* h)
{
	free(h->fila);
	free(h);
}
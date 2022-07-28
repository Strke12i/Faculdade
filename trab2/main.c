#include "heap.h"


int acao()
{
	int tmp;
	while(1)
	{
		fprintf(stdout,"Digite 1 para inserir, 2 para imprimir, 3 para consultar, 4 para remover elemento da fila e 5 para sair\n");
		scanf("%d",&tmp);
		if(tmp > 0 && tmp <= 5)
			break;
		fprintf(stdout,"Numero inválido digite novamente!\n");
	}
	return tmp;
}

void inserir(Heap* h)
{
	int tmp;
	fprintf(stdout,"Insira os valores da fila:\n");
	for(int i = 0; i < h->tamanho; i++)
	{
		if(scanf("%d",&tmp) == EOF)
			break;
		insere_heap(h, tmp);
	}	
}

void consultar(Heap* h)
{
	int tmp, pos;
	fprintf(stdout,"Qual o numero você deseja procurar na fila:");
	scanf("%d",&tmp);

	if(consulta_heap(h,tmp,&pos))
		fprintf(stdout,"O Numero %d esta na posicao %d da Fila\n",tmp,pos);
	else
		fprintf(stdout,"O Número %d nao esta na fila\n",tmp);
}

void remover(Heap* h)
{
	int tmp,pos;
	fprintf(stdout,"Digite o numero que deseja remover:");
	scanf("%d",&tmp);

	if(consulta_heap(h,tmp,&pos))
	{
		fprintf(stdout,"Elemento não está na fila..\n");
		return;
	}

	remove_heap(h,&tmp);
	fprintf(stdout,"Elemento %d removido da posicao %d da fila\n",tmp,pos);
	imprime_heap(h);
}

void cria_nova_fila(Heap* h)
{
	int tmp;
	fprintf(stdout,"Digite o tamanho da fila que deseja criar:");
	scanf("%d",&tmp);
	h = cria_heap(tmp);
}

int main()
{
	int tmp;
	fprintf(stdout,"Digite o tamanho da fila que deseja criar:");
	scanf("%d",&tmp);
	Heap* h = cria_heap(tmp);

	while(1)
	{
		tmp = acao();
		if(tmp == 1)
			inserir(h);
		if(tmp == 2)
			imprime_heap(h);
		if(tmp == 3)
			consultar(h);
		if(tmp == 4)
			remover(h);
		if(tmp == 5)
			break;
	}

	return 0;
}
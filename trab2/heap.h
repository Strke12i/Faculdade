#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_HEAP 20

struct heap
{
	int tamanho;
	int pos;
	int* fila;
};

typedef struct heap Heap;

Heap* cria_heap(int tamanho);
int pos_pai(int posicao);
int pos_filho_esq(int posicao);
int pos_filha_dir(int posicao);

void insere_heap(Heap* h, int n);
void balanceia_insercao_heap(Heap* h);
void balanceia_remocao_heap(Heap* h,int pos);
void imprime_heap(Heap* h);
void remove_heap(Heap* h,int *valor);
int consulta_heap(Heap* h,int n,int *pos);
void libera_heap(Heap* h);

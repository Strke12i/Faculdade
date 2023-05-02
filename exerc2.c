#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
	char nome[81];
	char matricula[8];
	float p1;
	float p2;
	float p3;
	struct lista* prox;
};

typedef struct lista Lista;

float calcula_media(Lista* l){
    return( (l->p1 + l->p2 + l->p3 )/ 3);
}

Lista* insere_ord(Lista* l,char* nome, char* matricula, float p1, float p2, float p3){
    
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    strcpy(novo->nome, nome);
    strcpy(novo->matricula, matricula);
    novo->p1 = p1;
    novo->p2 = p2;
    novo->p3 = p3;
    
    if(l == NULL){
        l = novo;
        return l;
    }

    if(calcula_media(novo) <= calcula_media(l)){
        novo->prox = l;
        l = novo;
        return l;
    }

    Lista* anterior = l;
    Lista* atual = l->prox;

    while(atual != NULL && calcula_media(novo) > calcula_media(atual)){
        anterior = atual;
        atual = atual->prox;
    }

    novo->prox = atual;
    anterior->prox = novo;

    return l;

}

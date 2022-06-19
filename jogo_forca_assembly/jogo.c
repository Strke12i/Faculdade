#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Pegar uma lista de palavras.
// Sortear palavra
// Informar o campo para o usuário
// Verificar se o usuario quer tentar acertar a palavra ->
	// se sim abrir campo para string
	// não -> continua normalmente o jogo
// Caso a letra não esteja na palavra perde pontos

FILE *abrir_arquivo_palavras()
{
	FILE *arq = fopen("wordlist.txt","r");
	if(arq==NULL)
	{
		fprintf(stdout,"Erro ao abrir o arquivo");
		exit(1);
	}
	return arq;
}

int quantidade_palavras()
{
	FILE *arq=abrir_arquivo_palavras();
	int contador_palavras = 0;
	while(1)
	{
		char str[100];
		fscanf(arq,"%s",str);	
		if(feof(arq))
			break;
		contador_palavras++;
	}
	fclose(arq);
	return contador_palavras;
}

void retorna_palavra(char *str)
{
	FILE *arq = abrir_arquivo_palavras();
	int sorteador, contador = 0;
	srand(time(NULL));
	sorteador = rand() % quantidade_palavras();

	while(1)
	{
		fscanf(arq,"%s",str);
		if(contador == sorteador)
			break;
		contador++;
		if(feof(arq))
		{
			fprintf(stdout,"Errorr");
			break;
		}
	}
	fclose(arq);
}

int main()
{
	char str[100];
	retorna_palavra(str);
	fprintf(stdout,"Palavra %s",str);
}


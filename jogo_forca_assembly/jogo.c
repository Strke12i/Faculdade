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

typedef struct{
	char palavra[100];
	char letras_acertadas[100];
}Palavra;

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

void retorna_palavra(Palavra *p)
{
	int quant = quantidade_palavras();
	FILE *arq = abrir_arquivo_palavras();
	int sorteador, contador = 0;
	srand(time(NULL));
	sorteador = rand() % quant;
	char str[100];
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
	strcpy(p->palavra,str);
	fclose(arq);
}

void display_forca(int vida)
{
	/*		()
		   /||\
		    /\
	*/
	fprintf(stdout,"-------\n");
	fprintf(stdout,"|   |\n");
	if(vida >= 1) fprintf(stdout,"|  ()\n");
	if(vida >= 2)
	{	
		if(vida == 2) fprintf(stdout,"|  ||	\n");
		if(vida == 3) fprintf(stdout,"| /||	\n");
		if(vida >= 4) fprintf(stdout,"| /||\\ \n");
	}
	if(vida >=5)
	{
		if(vida == 5) fprintf(stdout,"|  /	\n");
		if(vida == 6) fprintf(stdout,"|  /\\ \n");
	}
	fprintf(stdout,"|\n|\n|\n");
}

void preenche_palavra(Palavra *p)
{
	int i = 0;
	while(p->palavra[i]!='\0')
	{
		p->letras_acertadas[i] = '-';
		i++;
	}
	p->letras_acertadas[i] = '\0';

}


void acerta_letra(Palavra *p, char letra)
{
	int i = 0;
	while(p->palavra[i]!='\0')
	{
		if(letra == p->palavra[i])
			p->letras_acertadas[i] = letra;
		i++;
	}
}

void display_palavra(Palavra *p)
{
	for(int i = 0; i < strlen(p->letras_acertadas);i++)
	{
		if(p->letras_acertadas[i] == '-')
			fprintf(stdout," _ ");
		else
			fprintf(stdout," %c ",p->letras_acertadas[i]);
	}
	fprintf(stdout,"\n");
}

int verifica_resposta(Palavra *p)
{
	char str[100];
	fprintf(stdout,"Digite a resposta:");
	scanf("%s",str);
	if(!strcmp(str,p->palavra))
	{
		fprintf(stdout,"Você ganhou");
		return 1;
	}

	fprintf(stdout,"Você Errou! Perde uma vida\n");
	return 0;
}

int verifica_letra(Palavra *p, char letra, char *alfabeto)
{
	int i = 0;
	while(i < 26)
	{
		if(letra == alfabeto[i])
			return 0;
		i++;
	}
	i = 0;
	
	while(p->palavra[i]!='\0')
	{
		if(letra == p->palavra[i])
		{
			acerta_letra(p,letra);
			return 1;
		}
		i++;
	}
	return 0;
}

int maximo_jogadas(Palavra *p)
{
	int i = 0,cont =0;
	while(p->letras_acertadas[i]!='\0')
	{
		if(p->letras_acertadas[i] == '-')
			cont++;
		i++;
	}
	if(cont <= 3)
		return 1;
	return 0;
}

void jogo()
{
	Palavra p;
	int vida = 0;
	retorna_palavra(&p);
	printf("%s\n",p.palavra);
	preenche_palavra(&p);
	char letras[26];
	while(1)
	{
		display_forca(vida);
		display_palavra(&p);
		if(vida >= 6)
		{
			fprintf(stdout,"Fim de jogo\n");
			break;
		} 
		if(maximo_jogadas(&p))
		{
			if(!verifica_resposta(&p)) vida++;
			else break;
		}
		else
		{
			fprintf(stdout,"\nL:");
			char letra;
			scanf(" %c",&letra);

			if(!(verifica_letra(&p,letra,letras)))
			{
				vida++;
			}
		}
	}
}


int main()
{
	jogo();
	return 0;
}


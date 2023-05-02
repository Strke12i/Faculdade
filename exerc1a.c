#include <stdio.h>
#include <stdlib.h>

int** aloca(int m, int n){
    int **matriz = (int**)malloc(m * sizeof(int*));
    for (size_t i = 0; i < m; i++)
    {
        matriz[i] = (int*)malloc(n * sizeof(int));
    }

    if(matriz == NULL){
        printf("Erro na alocação");
    }

    return matriz;
}

void diagonal(int** mat, int m, int n){
    int soma = 0;
    for (size_t i = 0; i < m; i++)
    {
        soma += mat[i][i];
    }

    printf("Soma %d",soma);
    
}

int main(){
    return 0;
}
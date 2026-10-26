#include <stdio.h>
#include <stdlib.h>

//comparador para os pares
int comparaCresc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

//comparador para os impares
int comparaDesc(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int main() {
 
    int N;
    int x;

    if(scanf("%d", &N) != 1) return 0;
    
    int *pares = (int*) malloc(N * sizeof(int));
    int *impares = (int*) malloc(N * sizeof(int));
    int qtdPares = 0, qtdImpares = 0;
    
    //separando os pares e impaes no input
    for(int i=0; i < N; i++){
        scanf("%d", &x);
        if(x % 2 == 0)
            pares[qtdPares++] = x;
        else
            impares[qtdImpares++] = x;
    }
    
    //ordena os pares de forma crescente
    qsort(pares, qtdPares, sizeof(int), comparaCresc);
    
    //ordena os impares de forma decrescente
    qsort(impares, qtdImpares, sizeof(int), comparaDesc);
    
    //imprime pares
    for(int i = 0; i < qtdPares; i++)
        printf("%d\n", pares[i]);
    
    //mostra impares
    for(int i = 0; i < qtdImpares; i++)
        printf("%d\n", impares[i]);
    
    free(pares);
    free(impares);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//comparador pra ordenar strings
int compara(const void *a, const void *b){
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    int N, K;
    if(scanf("%d %d", &N, &K) != 2) return 0;
    
    char nomes[100][21];
    for(int i = 0; i < N; i++)
        scanf("%s", nomes[i]);
    
    //ordena os nomes ne
    qsort(nomes, N, sizeof(nomes[0]), compara);
    
    //o k nesimo aluno é a resposta
    printf("%s\n", nomes[K-1]);
    return 0;
}
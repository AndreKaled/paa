// problem: https://judge.beecrowd.com/pt/problems/view/1548
#include <stdio.h>

void troca(int *vetor, int i, int j) {
    int tmp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = tmp;
}

int particiona(int *vetor, int inicio, int fim) {
    int pivo = vetor[fim];
    int indice_pivo = inicio;
    for (int i = inicio; i < fim; i++) {
        if (vetor[i] >= pivo) {
            troca(vetor, indice_pivo, i);
            indice_pivo++;
        }
    }
    troca(vetor, indice_pivo, fim);
    return indice_pivo;
}

void quick(int *vetor, int inicio, int fim){
    if (inicio >= fim) {
        return;
    }
    int meio = particiona(vetor, inicio, fim);
    quick(vetor, inicio, meio - 1);
    quick(vetor, meio + 1, fim);
}

int main(){
    int N;
    scanf("%d", &N);
    while(N){
        N--;
        int M;
        scanf("%d", &M);
        int P[M];
        int copia[M];
        int nota;
        for(int i = 0; i < M; i++) {
            scanf("%d", &nota);
            P[i] = nota;
            copia[i] = nota;
        }
        quick(P, 0, M - 1);
        int resultado = 0;
        for (int i = 0; i < M; i++) {
            if (P[i] == copia[i]) {
                resultado++;
            }
        }
        printf("%d\n", resultado);
    }
    return 0;
}
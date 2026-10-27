#include <stdio.h>
#include <stdlib.h>

int buscaBinaria(int *v, int n, int chave){
    int esq = 0, dir = n -1;
    while(esq <= dir){
        int meio = esq + (dir - esq) /2;
        if(v[meio] == chave) return meio;
        else if(v[meio] < chave) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}
int main() {
    int N, M;
    if(scanf("%d %d", &N, &M) != 2) return 0;
    
    int casas[N];
    
    for(int i = 0; i < N; i++)
        scanf("%d", &casas[i]);
    
    int pos_atual = 0;
    long long tempo_total = 0;
    for(int i = 0; i < M; i++){
        int dest;
        scanf("%d", &dest);
        
        int novo_idx = buscaBinaria(casas, N, dest);
        tempo_total += abs(novo_idx - pos_atual);
        pos_atual = novo_idx;
    }
    
    printf("%lld\n", tempo_total);
 
    return 0;
}
#include <stdio.h>
#include <stdbool.h>

bool vet[100001];
int main() {
 
    int V, M;
    if(scanf("%d %d", &V, &M) != 2) return 0;
    
    int moedas[M];
    for(int i=0; i < M; i++)
        scanf("%d", &moedas[i]);
        
    vet[0] = true;
        
    for(int i = 0; i < M; i++){
        int m = moedas[i];
        for(int j = V; j >= m; j--){
            if(vet[j-m])
                vet[j] = true;
        }
    }
    
    if(vet[V])
        printf("S\n");
    else
        printf("N\n");
 
    return 0;
}
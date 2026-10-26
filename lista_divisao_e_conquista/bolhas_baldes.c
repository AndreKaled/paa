#include <stdio.h>
 
int main() {
    int N;
    while(scanf("%d", &N) ==1 && N!=0){
        int permutacoes[N+1];
        for(int i = 1; i <= N; i++)
            scanf("%d", &permutacoes[i]);
            
        long long trocas =0;
        //troca cara item na posicao certa
        for(int i=1; i <= N; i++){
            while(permutacoes[i] != i){
                int tmp = permutacoes[i];
                permutacoes[i] = permutacoes[tmp];
                permutacoes[tmp] = tmp;
                trocas++;
            }
        }
        
        if(trocas % 2 != 0)
            printf("Marcelo\n");
        else
            printf("Carlos\n");
    }
   
    return 0;
}
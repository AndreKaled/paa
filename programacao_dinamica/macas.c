#include <stdio.h>
#include <stdlib.h>
 
int main() {
 
    int N, M, K;
    while((scanf("%d %d %d", &N, &M, &K) == 3) && (N || M || K)){
        //vetores pra guardar posicao e tempo
        //de cada maca
        //indice 0 eh a posicao inicial do rafa
        int x[1001], y[1001], t[1001];
        
        // le as macas
        for(int i = 1; i <= K; i++)
            scanf("%d %d %d", &x[i], &y[i], &t[i]);
        
        //le posicao de rafa
        scanf("%d %d", &x[0], &y[0]);
        t[0] = 0; 
            
        //dp[i] = maximo de macas que podem ser pegas terminando
        //na maca i
        int dp[1001] = {0}, ans = 0;
        for(int i = 1; i <= K; i++){
            for(int j = 0; j < i; j++){
                //rafael anda em 8 direcoes
                //ent o tempo minimo pra ir eh
                //max(|dx|, |dy|)
                int dx = abs(x[i] - x[j]);
                int dy = abs(y[i] - y[j]);
                int d = dx > dy ? dx : dy;
                //so pega a maca se der tempo pra percorrer d
                if((j == 0 || dp[j] > 0) && t[i] - t[j] >= d){
                    int cand = dp[j] + 1;
                    //atualiza se esse caminho for melhor
                    if(cand > dp[i]) dp[i] = cand;
                }
            }
            //resposta global do melhor caminho que termina em i
            if(dp[i] > ans)
                ans = dp[i];
        }
        printf("%d\n", ans);
    }
 
    return 0;
}
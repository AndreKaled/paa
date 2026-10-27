#include <stdio.h>
#include <string.h>

int N,M,K;
char tabuleiro[105][105];
int dist[105][105]; // distancia do BFS a partir de uma origem
int qx[10005], qy[10005]; //fila do BFD (x e y separados)
int px[16], py[16]; //posicioes: indice 0 = cavalo, 1..k = peoes
int D[16][16]; //distancia entre cada par de pontos importantes
int dp[1 << 15][15]; // dp[mask][i] = menor custo visitando mask e terminando

//BFS padrao que preenche a matriz dist
void bfs(int si, int sj){
    int dx[] = {2,2,-2,-2,1,1,-1,-1};
    int dy[] = {1,-1,1,-1,2,-2,2,-2};
    int h = 0, t = 0; //cabeca e cauda da fila
    
    //comeco tudo com -1 de nao visitado
    memset(dist, -1, sizeof(dist));
    dist[si][sj] = 0;
    qx[t] = si; qy[t++] = sj;
    
    while(h < t){
        int x = qx[h], y = qy[h++];
        
        //os 8 saltos possiveis do cavalo
        for(int i = 0; i < 8; i++){
            int a = x + dx[i], b = y + dy[i];
            
            //fora do tabuleiro? pula
            if(a < 0 || a >= N || b < 0 || b >= M) 
                continue;
            //posicao invalida ou ja visitada
            if(tabuleiro[a][b] == '#' || dist[a][b] != -1)
                continue;
                
            dist[a][b] = dist[x][y] + 1;
            qx[t] = a;
            qy[t++] = b;
        }
    }
}

int main() {
 
    while(scanf("%d %d %d", &N, &M, &K) == 3 && (N || M || K)){
        int n = 1; //conta quantos pontos tenho
        //comeca com 1 por causa do cavalo, e conta os peoes
        
        for(int i = 0; i < N; i++){
            scanf("%s", tabuleiro[i]);
            for(int j = 0; j < M; j++){
                //cavalo vai no indice 0
                if(tabuleiro[i][j] == 'C'){
                    px[0] = i;
                    py[0] = j;
                }
                //peoes vao de 1 ate k
                else if(tabuleiro[i][j] == 'P'){
                    px[n] = i;
                    py[n] = j;
                    n++;
                }
            }
        }
            
        //pra cada ponto importante, rodo um BFS e guardo
        //as distancias em D
        for(int j = 0; j <= K; j++){
            bfs(px[j], py[j]);
            for(int t=0; t <= K; t++)
                D[j][t] = dist[px[t]][py[t]];
        }
            
        memset(dp, 0x3f, sizeof dp);
        
        //caso base: comecei do cavalo e fui direto pro peao i
        for(int i = 0; i < K; i++)
            dp[1 << i][i] = D[0][i + 1];
        int full = (1 << K) -1; //mascara com todos os peoes capturados
        
        
        //pra cada mascara e ultimo peao i, tento
        //ir pro peao j que ainda nao peguei
        for(int m = 0; m <= full; m++)
            for(int i = 0; i < K; i++) if ((m >> i) & 1)// i ja foi visitado?
                //j ainda nao foi visitado
                for(int j=0; j < K; j++) if(!((m >> j) & 1)){
                    int nm = m | (1 << j); // nova mascara com j marcado
                    int v = dp[m][i] + D[i + 1][j + 1]; // custo: atual + salto de 1 pra j
                    if(v < dp[nm][j])
                        dp[nm][j] = v; // relaxa
                }
                
        //resposta: melhor custo terminando em algum peao + volta pra origem
        int resp = 1 << 30;
        for(int i = 0; i < K; i++){
            int v = dp[full][i] + D[i + 1][0];
            if(v < resp)
                resp = v;
        }
        
        printf("%d\n", resp);
    }
 
    return 0;
}
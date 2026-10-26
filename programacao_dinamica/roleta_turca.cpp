#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int S, B;
    //le enquanto a leitura der certo
    while((scanf("%d %d", &S, &B) == 2) && (S || B)){
        //x = numero das S espacos da roleta
        //y = numero das B bolas na ordem q foram jogadas
        vector<int> X(S), Y(B);
        
        //le os S espacos da roleta
        for(int i = 0; i < S; i++)
            scanf("%d", &X[i]);
        //le as B bolas
        for(int i = 0; i < B; i++)
            scanf("%d", &Y[i]);
            
        //testa as S rotacoes possíiveis da roleta
        //i eh offset da posicao onde a primeira bola comecar
        long long melhor = LLONG_MIN;
        const long long NEG = LLONG_MIN / 4;
        for(int i = 0; i < S; i++){
            // dp[j][k]: j bolas colocadas, usando os k primeiros espacos
            //a partir de i
            vector<vector<long long>> dp(B+1, vector<long long>(S+1,NEG));
            for (int j = 0; j <= S; j++)
                dp[0][j] = 0;
            for(int j = 1; j <= B; j++){
                for(int k = 2; k <= S; k++){
                    dp[j][k] = dp[j][k-1];
                    if(dp[j-1][k-2] > NEG){
                        int a = X[(i+k-2) % S];
                        int b = X[(i+k-1) % S];
                        long long v = dp[j-1][k-2] - (long long)Y[j-1] * (a+b);
                        dp[j][k] = max(dp[j][k], v);
                    }
                }
            }
            //retorna o maior entre o melhor e o lucro
            melhor = max(melhor, dp[B][S]);
        }
        printf("%lld\n", melhor);
    }
 
    return 0;
}
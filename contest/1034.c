// problem: https://judge.beecrowd.com/pt/problems/view/1034
#include <stdio.h>

#define INF 1000000000 // valor grande para representar "infinito"

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M);
        int blocos[25];
        for (int i = 0; i < N; i++) {
            scanf("%d", &blocos[i]);
        }

        // dp[i] = mínimo de blocos para atingir comprimento i
        int dp[M + 1];
        dp[0] = 0;
        for (int i = 1; i <= M; i++) {
            dp[i] = INF;
        }

        for (int i = 1; i <= M; i++) {
            for (int j = 0; j < N; j++) {
                int b = blocos[j];
                if (b <= i && dp[i - b] + 1 < dp[i]) {
                    dp[i] = dp[i - b] + 1;
                }
            }
        }

        printf("%d\n", dp[M]);
    }
    return 0;
}
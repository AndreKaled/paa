#include <stdio.h>
#include <bits/stdc++.h>
#include <string.h>
using namespace std;

using ull = unsigned long long;
 
int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    getchar(); // consome o \n depois de M e N
    string formula;
    char linha[10000];
    
    //le a formula inteira
    while(fgets(linha, sizeof(linha), stdin) != NULL)
        formula += linha;
        
    int K = (N + 1 + 63)/64;
    
    //cada linha eh uma clausula e cada bit uma variavel
    //o bit N representa o resultado da formula
    vector<vector<ull>> a(M, vector<ull>(K, 0));
    
    //inverte o valor de um bit
    auto altera = [&](vector<ull>& col, int bit) {
        col[bit / 64] ^= (1ULL << (bit % 64));
    };
    
    int pos = 0;
    
    //tranforma cada clausula em xor
    for(int i = 0; i < M; i++){
        int inicio = formula.find('(', pos);
        int fim = formula.find(')', inicio);
        
        string clausula = formula.substr(inicio + 1, fim - inicio - 1);
        pos = fim + 1;
        
        //quantidade literais verdadeiros precisa ser impar
        altera(a[i], N);
        
        stringstream ss(clausula);
        string token;
        bool neg = false;
        
        while(ss >> token){
            if(token == "not"){
                neg = true;
            }else if(token[0] == 'x'){
                int v = stoi(token.substr(1)) -1;
                
                //add a variavel na equacao
                altera(a[i], v);
                
                //variavel negada altera o lado direito da equacao
                if(neg)
                    altera(a[i], N);
                neg = false;
            }
        }
    }
    
    vector<int> pivo(N, -1);
    int rank = 0;
    
    //eliminacao de gauss
    for(int col = N -1; col >= 0; col--){
        int r = rank;
        
        //procura uma linha q tenha 1 nessa coluna
        while(r < M && !(a[r][col/64] & (1ULL << (col % 64))))
            r++;
            
        if(r == M)
            continue; //variavel sem pivo
            
        swap(a[rank], a[r]);
        pivo[col] = rank;
        
        //zera essa variavel nas linhas abaixo com xor
        for(int j = rank +1; j < M; j++){
            if(a[j][col/64] & (1ULL <<(col % 64))){
                for(int k = 0; k < K; k++)
                    a[j][k] ^= a[rank][k];
            }
        }
        rank++;
    }
    
    //se 0 = 1 o sistema nao tem solucao
    for(int i = rank; i < M; i++){
        bool zero = true;
        for(int j = 0; j < N; j++){
            if(a[i][j / 64] & (1ULL << (j % 64))){
                zero = false;
                break;
            }
        }
        
        if(zero && (a[i][N/64] & (1ULL << (N % 64)))){
            printf("impossible\n");
            return 0;
        }
    }
    //comeca colocando T nas variaveis livres
    vector<int> x(N, 1);

    //calcula as variaveis com pivo usando as que ja foram calculadas
    for (int col = 0; col < N; col++) {
        if (pivo[col] == -1)
            continue;

        int r = pivo[col];
        int val = (a[r][N / 64] >> (N % 64)) & 1ULL;

        for (int j = 0; j < col; j++) {
            if (a[r][j / 64] & (1ULL << (j % 64)))
                val ^= x[j];
        }

        x[col] = val;
    }

    //imprime a atribuicao encontrada
    for (int i = 0; i < N; i++)
        printf("%c", x[i] ? 'T' : 'F');

    printf("\n");

    return 0;
}
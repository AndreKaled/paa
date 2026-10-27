#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int P, W;
vector<int> enfeites, peso;

int backtracking(int i, int pesoAtual){
    //caso base
    if(i == P)
        return 0;
        
    //opcao 1 eh nao pegar o pacote atual
    int melhor = backtracking(i + 1, pesoAtual);
    
    //opcao 2 eh pegar o pacote se der
    if(pesoAtual + peso[i] <= W){
        melhor = max(melhor, enfeites[i] + backtracking(i+1, pesoAtual + peso[i]));
    }
    return melhor;
}

int main() {
    int G;
    scanf("%d", &G);
    
    for(int g = 1; g <= G; g++){
        scanf("%d %d", &P, &W);
        enfeites.resize(P);
        peso.resize(P);
        
        for(int i = 0; i < P; i++)
            scanf("%d %d", &enfeites[i], &peso[i]);
        
        printf("Galho %d:\n", g);
        printf("Numero total de enfeites: %d\n\n", backtracking(0,0));
    
        //if(g < G)
        //   printf("\n");
    }
 
    return 0;
}
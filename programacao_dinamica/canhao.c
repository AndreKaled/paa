#include <stdio.h>
#include <string.h>

int max(int a, int b){
    return (a > b) ? a : b;
}

void loop(){
    int N;
    if(scanf("%d", &N) != 1) return;
    
    int poder[55], peso[55];
    for(int i = 0; i < N; i++)
        scanf("%d %d", &poder[i], &peso[i]);
        
    int k, r;
    //capacidade de carga
    scanf("%d", &k);
    // resistencia do castelo
    scanf("%d", &r);
    
    int dano[105];
    memset(dano, 0, sizeof(dano));
    
    for(int i = 0; i < N; i++){
        //percorre ate peso[i] de tras pra frente
        //pra nao resusar o mesmo projetil
        for(int p = k; p >= peso[i]; p--)
            dano[p] = max(dano[p], dano[p - peso[i]] + poder[i]);
    }
            
    int dano_max = dano[k];
    
    //verifica se o dano eh suficeinte
    if(dano_max >= r)
        printf("Missao completada com sucesso\n");
    else
        printf("Falha na missao\n");    
}

int main() {
 
    int casos;
    if(scanf("%d", &casos) == 1){
        while(casos--){
            loop();
        }
    }
 
    return 0;
}
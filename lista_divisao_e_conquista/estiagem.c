#include <stdio.h>
#include <math.h>
#define MAX_CONSUMO 201 

int main() {
 
    int N, caso = 1;
    while(scanf("%d", &N) == 1 && N != 0){
        int pessoas_consumo[MAX_CONSUMO] = {0};
        long long total_pessoas = 0;
        long long total_consumo = 0;
        
        for(int i = 0; i < N; i++){
            int x, y;
            scanf("%d %d", &x, &y);
            int consumo_pessoa = y/x; //arredonda pra baixo
            pessoas_consumo[consumo_pessoa] += x;
            total_pessoas += x;
            total_consumo += y;
        }
        
        //linha em brabco pra separar os casos de teste
        if(caso > 1)
            printf("\n");
            
        printf("Cidade# %d:\n", caso++);
        
        //imprime os grupos de consumo em ordem
        //crscente
        int primeiro =1;
        for(int i = 0; i < MAX_CONSUMO; i++){
            if(pessoas_consumo[i] > 0){
                if(!primeiro)
                    printf(" ");
                printf("%d-%d", pessoas_consumo[i], i);
                primeiro = 0;
            }
        }
        printf("\n");
        
        //consumo medio
        double medio = (double)total_consumo / total_pessoas;
        double medio_truncado = floor(medio * 100.0) / 100.0;
        printf("Consumo medio: %.2f m3.\n", medio_truncado);
    }
 
    return 0;
}
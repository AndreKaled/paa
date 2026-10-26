#include <stdio.h>
 
int main() {
 
    double valor;
    if(scanf("%lf", &valor) != 1) return 0;
    
    //converte pra centavos inteiros pra
    //evitar erro de arredondamento
    int centavos = (int)(valor * 100 + 0.5);
    
    //vetor com as notas e moedas
    int notas[] = {10000, 5000, 2000, 1000, 500, 200};
    int moedas[] = {100, 50, 25, 10, 5, 1};
    
    printf("NOTAS:\n");
    for(int i = 0; i < 6; i++){
        int qtd = centavos / notas[i];
        printf("%d nota(s) de R$ %.2f\n", qtd, notas[i] / 100.0);
        centavos %= notas[i];//resto da proximoa nota
    }
    
    printf("MOEDAS:\n");
    for(int i = 0; i < 6; i++){
        int qtd = centavos / moedas[i];
        printf("%d moeda(s) de R$ %.2f\n", qtd, moedas[i] / 100.0);
        centavos %= moedas[i];//resto da proximoa moeda
    }
    
 
    return 0;
}
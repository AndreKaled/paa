#include <stdio.h>
//funcao pra intercalar os vetores e contar
// as trocas ao mesmo tempo
int merge(int* v, int esq, int meio, int dir){
    int i = esq, j = meio+1, k = 0;
    int tmp[dir-esq+1]; // vetor auxiliar
    int trocas = 0;
    
    while(i <= meio && j <= dir){
        if(v[i] <= v[j]){
            tmp[k++] = v[i++];
        }else{
            tmp[k++] = v[j++];
            /*todos os itens restantes na metade da esquerda
            sao maiores de v[j], tendo entao inversões*/
            trocas += (meio-i+1);
        }
    }
    
    //cpia o resto da esquerda
    while(i <= meio)
        tmp[k++] = v[i++];
    
    //copia o resto da direita
    while(j <=dir)
        tmp[k++] = v[j++];
        
    //cpiando de volta pro original
    for(int i=esq, k=0;i <= dir; i++, k++)
        v[i] = tmp[k];
        
    return trocas;
}

int mergeSort(int *v, int esq, int dir){
    int trocas = 0;
    if(esq < dir){
        int meio = esq + (dir-esq)/2;
        
        //soma as trocas da metade esq +
        //metade dir + intercalacao
        trocas += mergeSort(v, esq, meio);
        trocas += mergeSort(v, meio+1, dir);
        trocas += merge(v, esq, meio, dir);
    }
    return trocas;
}

int main() {
    //num de casos de teste
    int N;
    if(scanf("%d", &N) != 1) return 0;
    
    while(N--){
        int L;
        scanf("%d", &L);
        
        int vagoes[L];
        for(int i = 0; i < L; i++) 
            scanf("%d", &vagoes[i]);
        
        // joga pro merge que vai contar as trocas
        int totalTrocas = mergeSort(vagoes, 0, L-1);
        printf("Optimal train swapping takes %d swaps.\n", totalTrocas);
    }
 
    return 0;
}
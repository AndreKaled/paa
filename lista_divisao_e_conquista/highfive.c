#include <stdio.h>

// funcao que combina duas metades ordenadas e conta os highfives
long long merge(int *v, int esq, int meio, int dir){
    int i = esq, j = meio+1, k = 0;
    int tmp[dir - esq + 1];
    long long highFive = 0;
    
    while(i <= meio && j <= dir){
        if(v[i] <= v[j]){
            highFive += (dir -j +1);
            tmp[k++] = v[i++];
        }else{
            tmp[k++] = v[j++];
        }
    }
    
    while(i <= meio) tmp[k++] = v[i++];
    while(j <= dir) tmp[k++] = v[j++];
    
    for(int pos = esq, idx = 0; pos <= dir; pos++, idx++)
        v[pos] = tmp[idx];
        
    return highFive;
}
 
 
long long mergeSort(int *v, int esq, int dir){
    long long highFive = 0;
    if(esq < dir){
        int meio = esq + (dir - esq)/2;
        highFive+= mergeSort(v, esq, meio);
        highFive+= mergeSort(v, meio + 1, dir);
        highFive+= merge(v, esq, meio, dir);
    }
    return highFive;
}
 
int main() {
 
    int N;
    while(scanf("%d", &N) != EOF){
        int fila[N];
        //input
        for(int i=0; i < N; i++)
            scanf("%d", &fila[i]);
        
        long long highFive = mergeSort(fila, 0, N - 1);
        printf("%lld\n", highFive);
    }   
 
    return 0;
}
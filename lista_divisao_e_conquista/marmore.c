#include <stdio.h>

void quickSort(int* v, int esq, int dir){
    if(esq < dir){
        int pivo = v[(esq + dir)/2];
        int i = esq, j = dir;
        
        while(i <= j){
            while(v[i] < pivo) i++;
            while(v[j] > pivo) j--;
            if(i<=j){
                int tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
                i++; j--;
            }
        }
        quickSort(v, esq, j);
        quickSort(v, i, dir);
    }
}

int buscaBinaria(int *v, int n, int x){
    int inicio = 0, fim = n-1, pos = -1;
    
    while(inicio <= fim){
        int meio = inicio + (fim - inicio)/2;
        if(v[meio] == x){
            pos = meio;
            //vai buscando pra esquerda
            //pra achar a primeira ocorrencia
            fim = meio - 1;
        }
        else if(v[meio] < x)
            inicio = meio+1;
        else
            fim = meio-1;
    }
    return pos;
}

int main() {
 
    int N = 0, Q = 0, caso = 1;
    
    while(scanf("%d %d", &N, &Q) == 2 && (N != 0 && Q != 0)){
        int marmores[N];
        for(int i=0; i < N; i++)
            scanf("%d", &marmores[i]);
            
        quickSort(marmores, 0, N-1);
            
        printf("CASE# %d:\n", caso++);
        for(int i=0; i < Q; i++){
            int consulta;
            scanf("%d", &consulta);
            int pos = buscaBinaria(marmores, N, consulta);
            if(pos != -1)
                printf("%d found at %d\n", consulta, pos+1);
            else
                printf("%d not found\n", consulta);
        }
                
    }
    return 0;
}
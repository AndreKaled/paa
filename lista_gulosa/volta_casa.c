#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double v, p, razao;
} Queijo;

//comparador pra ordenar do maior custo beneficio para o menor
int comp(const void *a, const void *b){
    double diff = ((Queijo*)b)->razao - ((Queijo*)a)->razao;
    return (diff > 0) - (diff < 0);
}

int main() {
    int N;
    double B;
    if(scanf("%d %lf", &N, &B) != 2) return 0;
    
    Queijo q[N];
    for(int i=0; i < N; i++) 
        scanf("%lf", &q[i].v);
        
    for(int i=0; i < N; i++){ 
        scanf("%lf", &q[i].p);
        q[i].razao = (q[i].p == 0) ? 1e18 : (q[i].v / q[i].p);
        
        
    }
    
    qsort(q, N, sizeof(Queijo), comp);
    
    double vol = 0;
    for(int i = 0; i < N && B > 0; i++){
        if(q[i].p == 0)
            vol += q[i].v; //pega tudo se for gratis
        else if(B >= q[i].p){
            //compra a peça inteira
            vol += q[i].v;
            B -= q[i].p;
        }else{
            //compra so a fracao q der do orcamento
            vol += q[i].v * (B / q[i].p);
            B = 0;
        }
        
    }
    
    long long K = (sqrt(1+8*vol)-1)/2;
    
    printf("%lld\n", K);
    return 0;
}
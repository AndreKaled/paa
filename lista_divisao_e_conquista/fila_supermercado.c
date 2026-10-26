#include <stdio.h>
#include <stdlib.h>

typedef struct {
    //tempo que o caixa vai ta livre
    long long tempo_livre;
    //numero do funcionario
    int id;
    //tempo q o funcionario leva por item
    int v;
} Caixa;

//troca dois caixas de posicao na arvore
void troca(Caixa *a, Caixa *b){
    Caixa tmp = *a;
    *a = *b;
    *b = tmp;
}

//quem fica livre mais cedo sai primeiro da arvore
//em caso de empate o caixa com menor id tem prioridade
int compara(Caixa a, Caixa b){
    if(a.tempo_livre != b.tempo_livre) 
        return a.tempo_livre < b.tempo_livre;
    return a.id < b.id;
}

//ajusta a arvore de cima pra baixo dps de atualizar a raiz
void heap_down(Caixa heap[], int n, int i){
    int menor = i;
    int esq = 2*i+1;
    int dir = 2*i+2;
    if(esq < n && compara(heap[esq], heap[menor])) menor = esq;
    if(dir < n && compara(heap[dir], heap[menor])) menor = dir;
    if(menor != i){
        troca(&heap[i], &heap[menor]);
        heap_down(heap, n, menor);
    }
}

//ajusta a arvore de baixo pra cime ao inserir novo caixa
void heap_up(Caixa heap[], int i){
    while(i > 0){
        int pai = (i-1)/2;
        if(compara(heap[i], heap[pai])){
            troca(&heap[i], &heap[pai]);
            i = pai;
        }else{
            break;
        }
    }
}

int main() {
    int N, M;
    if(scanf("%d %d", &N, &M) != 2) return 0;
    
    int v[N+1];
    for(int i=1; i <= N; i++)
        scanf("%d", &v[i]);
        
    int c[M];
    for(int i=0; i < M; i++)
        scanf("%d", &c[i]);
    
    Caixa heap[N];
    int size = 0;
    
    //todos os caixas começam livres
    for(int i = 1; i <= N; i++){
        heap[size].tempo_livre = 0;
        heap[size].id = i;
        heap[size].v = v[i];
        size++;
        heap_up(heap, size-1);
    }
    
    //o proximo cliente da fila vai sempre para o caixa
    //que liberar primeiro
    for(int cliente = 0; cliente < M; cliente++){
        Caixa caixa_livre = heap[0];
        //o novo atendimento acumula no tempo q o caixa ja tava ocupado
        caixa_livre.tempo_livre += (long long)caixa_livre.v * c[cliente];
        //coloca o caixa atualizado de volta ao topo
        //e reordena a arvore
        heap[0] = caixa_livre;
        heap_down(heap, size, 0);
    }
    //tempo total ate atender toos os clientes
    //e o maior tempo livre entre todos os caixas
    long long tempo_total = 0;
    for(int i=0; i < size; i++)
        if(heap[i].tempo_livre > tempo_total)
            tempo_total = heap[i].tempo_livre;
            
    printf("%lld\n", tempo_total);
    return 0;
}
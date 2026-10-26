#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int v; //lucro
    int t; //prazo da tarefa
} Tarefa;

//ordena do maior para menor lucro (maior pra menor)
int compara(const void *a, const void *b){
    Tarefa *t1 = (Tarefa *)a;
    Tarefa *t2 = (Tarefa *)b;
    return t2->v - t1->v;
}

int main() {
    int N, M;
    
    while(scanf("%d %d", &N, &M) != EOF){
        Tarefa tarefas[N];
        int soma_total = 0;
        
        for(int i=0; i < N; i++){
            scanf("%d %d", &tarefas[i].v, &tarefas[i].t);
            // soma o lucro de todas as tarefas
            soma_total += tarefas[i].v;
        }
        
        //ordena pra priorizar as mais valiosas
        qsort(tarefas, N, sizeof(Tarefa), compara);
        
        //vet pra marcar quais horarios ja estao ocupados
        int alocado[M+1];
        memset(alocado, 0, sizeof(alocado));
        int lucro_obtido = 0;
        
        //processa cada tarefa de valor decrescente
        for(int i = 0; i < N; i++){
            for(int hora = tarefas[i].t; hora >= 1; hora--)
                if(!alocado[hora]){
                    alocado[hora] = 1; // ocupa horario
                    lucro_obtido += tarefas[i].v;
                    break;
                }
        }
        
        int dinheiro_perdido = soma_total - lucro_obtido;
        printf("%d\n", dinheiro_perdido);
    }
 
    return 0;
}
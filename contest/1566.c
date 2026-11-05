//problem: https://judge.beecrowd.com/pt/problems/view/1566
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar para o qsort ordenar em ordem crescente
int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    // Lê o número de casos de teste
    if (scanf("%d", &N) != 1) return 0;

    // Aloca uma matriz dinâmica para guardar os resultados de cada caso
    // matriz[i] guardará a lista de alturas do caso i
    int **resultados = malloc(N * sizeof(int *));
    int *tamanhos = malloc(N * sizeof(int)); // Guarda a quantidade de pessoas de cada caso

    for (int i = 0; i < N; i++) {
        int pessoas;
        if (scanf("%d", &pessoas) != 1) return 0;
        tamanhos[i] = pessoas;

        // Aloca espaço para as alturas desse caso específico
        resultados[i] = malloc(pessoas * sizeof(int));

        // Lê as alturas uma por uma (equivalente ao split + map do Python)
        for (int j = 0; j < pessoas; j++) {
            if (scanf("%d", &resultados[i][j]) != 1) return 0;
        }

        // Ordena o vetor atual (equivalente ao alturas.sort())
        qsort(resultados[i], pessoas, sizeof(int), comparar);
    }

    // Exibe os resultados formatados com espaço entre eles
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < tamanhos[i]; j++) {
            printf("%d", resultados[i][j]);
            if (j < tamanhos[i] - 1) {
                printf(" "); // Imprime espaço apenas ENTRE os números
            }
        }
        printf("\n"); // Quebra de linha ao fim de cada caso de teste

        // Libera a memória alocada para este caso
        free(resultados[i]);
    }

    // Libera as estruturas principais
    free(resultados);
    free(tamanhos);

    return 0;
}

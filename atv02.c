#include <stdio.h>
#include <stdlib.h>

//pode ta desordenado mesmo q vai funcionar
int sequencial(int* v, int n, int val){
    for(int i = 0; i < n; i++)
        if(v[i] == val)
            return i;
    return -1;
}

//exige-se estar com o vetor ordenado pq se nao n funciona
int binaria(int* v, int n, int val){
    int inicio = 0, fim = n-1;
    while(inicio <= fim){
        int meio = inicio + (fim - inicio)/2;
        if(v[meio] < val)
            inicio = meio+1;
        else if(v[meio] > val)
            fim = meio-1;
        else
            return meio;
    }
    return -1;
}


/**int main() {
    int v[] = {3, 25, 42, 18, 7, 31, 10};
    int n = 7;

    int valor = 42;

    int resultado = binaria(v, n, valor);

    if (resultado != -1)
        printf("Valor %d encontrado na posicao %d.\n", valor, resultado);
    else
        printf("Valor %d nao encontrado.\n", valor);

    return 0;
}*/


void merge(int* v, int inicio, int meio, int fim, int* aux){
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while(i <= meio && j <= fim){
        if(v[i] <= v[j]){
            aux[k] = v[i];
            i+=1;
        }else{
            aux[k] = v[j];
            j+=1;
        }
        k+=1;
    }
    while(i <= meio){
        aux[k] = v[i];
        i++;
        k++;
    }
    while(j <= fim){
        aux[k] = v[j];
        j++;
        k++;
    }
    // copia o trecho ordenado de volta para o vetor original
    for(int i = inicio; i <= fim; i++)
        v[i] = aux[i];

}

void mergeSort(int* v, int inicio, int fim, int* aux){
    if(inicio < fim){
        int meio = inicio + (fim - inicio)/2;
        mergeSort(v, inicio, meio, aux);
        mergeSort(v, meio+1, fim, aux);
        merge(v, inicio, meio, fim, aux);
    }
}

void aplicaMergeSort(int* v, int n){
    int vaux[n];
    mergeSort(v, 0, n-1, vaux);
}

void heapify(int* v, int n, int i){
    //inicia o maior como raiz da arvore
    int maior = i;
    int esq = 2*i +1;
    int dir = 2*i +2;

    if(esq < n && v[esq] > v[maior])
        maior = esq;
    if(dir < n && v[dir] > v[maior])
        maior = dir;
    if(maior != i){
        int tmp = v[i];
        v[i] = v[maior];
        v[maior] = tmp;
        heapify(v, n, maior);
    }
}

void heapSort(int* v, int n){
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for(int i = n -1; i > 0; i--){
        int tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;

        heapify(v, i, 0);
    }
}

/**int main() {
    int v[] = {3, 25, 42, 18, 7, 31, 10};
    int n = 7;

    printf("Vetor antes da ordenacao:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");

    heapSort(v, n);

    printf("Vetor depois da ordenacao:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");

    return 0;
}*/

void countSort(int* v, int n){
    int max = v[0];
    //pega o maximo
    for(int i = 0; i < n; i++)
        if(v[i] > max)
            max = v[i];

    // cria novo vetor aux 
    int* cntV = (int*)calloc(max + 1, sizeof(int));

    // conta quantas vezes cada numero aparece em V
    for(int i = 0; i < n; i++)
        cntV[v[i]]++;

    // confesso que nao entendi exatamente oq isso deveria fazer, mas funciona
    for(int i = 1; i <= max; i++)
        cntV[i] += cntV[i-1];

    // criando vetor de saída
    int* aux = (int*)malloc(n * sizeof(int));
    for(int i = n - 1; i >= 0; i--){
        aux[cntV[v[i]] - 1] = v[i];
        cntV[v[i]]--;
    }

    //copiando vetor
    for(int i = 0; i < n; i++)
        v[i] = aux[i];

    free(cntV);
    free(aux);
}

int main() {
    int v[] = {3, 25, 42, 18, 7, 31, 10};
    int n = 7;

    printf("Vetor antes da ordenacao:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");

    countSort(v, n);

    printf("Vetor depois da ordenacao:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");

    return 0;
}
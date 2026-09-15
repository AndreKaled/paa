# Parte 1 - Escrevendo algoritmos e determinando suas complexidades
## 1. Especifique cada problema e calcule o M.C. (melhor caso), P.C. (pior caso), C.M. (caso médio) e a ordem de complexidade para algoritmos (incluindo o de melhor desempenho teórico possível) para os seguintes problemas. Procure ainda, pelos L.I. (limite inferior) de tais problemas. Apresente um quadro comparativo para os algoritmos de cada problema (versões iterativa vs recursiva, MC/CM/PC e LI):

### a) Busca sequencial e binária
```c
int buscaSequencialIterativo(int* A, int n, int x){
    for(int i = 0; i < n; i++){
        if(A[i] == x)
            return i;
    }
    return -1;
}

int buscaSequencialRecursivo(int* A, int i, int n, int x){
    if(i >= n)
        return -1;
    if(A[i] == x)
        return i;
    return buscaSequencialRecursivo(A, i+1, n, x);
}

int buscaBinariaIterativa(int* A, int n, int x){
    int esq = 0;
    int dir = n;
    while(esq <= dir){
        int meio = (esq+dir)/2;
        if(A[meio] == x)
            return meio;
        else if(A[meio] < x)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    return -1;
}

int buscaBinariaRecursiva(int* A, int esq, int dir, int x){
    if(esq > dir)
        return -1;
    int meio = (esq + dir)/2;
    if(A[meio] == x)
        return meio;
    else if(A[meio] < x)
        return buscaBinariaRecursiva(A, meio+1, dir, x);
    else
        return BuscaBinariaRecursiva(A, esq, meio-1, x);
}
```

Cálculo da ordem de complexidade:
![Busca Sequencial Iterativa Notations](/imgs/busca_sequencial_iterativo.png)

![Busca Sequencial Recursiva Notations](/imgs/busca_sequencial_recursivo.png)

![Busca Binária Iterativa Notations](/imgs/busca_binaria_iterativa.png)

![Busca Binária Recursiva Notations](/imgs/busca_binaria_recursiva.png)

| Algoritmo                  | M.C.      | C.M.      | P.C.      | Ordem      | L.I.       | Ótimo?                        |
|----------------------------|-----------|-----------|-----------|------------|------------|-------------------------------|
| Busca Sequencial Iterativa | O(1)      | O(n)      | O(n)      | O(n)       | Ω(log n)   | Não (vetor ordenado)          |
| Busca Sequencial Recursiva | O(1)      | O(n)      | O(n)      | O(n)       | Ω(log n)   | Não (vetor ordenado)          |
| Busca Binária Iterativa    | O(1)      | O(log n)  | O(log n)  | O(log n)   | Ω(log n)   | Sim                           |
| Busca Binária Recursiva    | O(1)      | O(log n)  | O(log n)  | O(log n)   | Ω(log n)   | Sim                           |
### b) Fatorial de um número
```c
int* fatorial_iterativo(int* fat, int N){
    fat[0] = 1;
    for(int j = 1; i < N; j++)
        fat[j] = j * fat[j-1];
    return fat[];
}

int fatorial_recursivo(int N){
    if (N == 0)
        return 1;
    else
        return N * fatorial_recursivo(N-1); 
}
```

Calculo de ordem de complexidade:
![Fatorial iterativo notations](/imgs/fatorial_iterativo.png)

![Fatorial recursivo notations](/imgs/fatorial_recursivo.png)

| Versão    | M.C.  | C.M.  | P.C.  | Ordem  | L.I.   | Ótimo? |
|-----------|-------|-------|-------|--------|--------|--------|
| Iterativa | O(1)  | O(n)  | O(n)  | O(n)   | Ω(n)   | Sim    |
| Recursiva | O(1)  | O(n)  | O(n)  | O(n)   | Ω(n)   | Sim    |

### c) Ordenação

### d) Máximo e Mínimo de uma lista
```py
def max_min_iterativo(lista):
    if not lista:
        return None, None
    maximo = lista[0]
    minimo = lista[0]

    for numero in lista[1:]:
        if numero > maximo:
            maximo = numero
        if numero < minimo:
            minimo = numero

    return maximo, minimo

def max_min_recursivo(lista):
    if not lista:
        return None, None
    if len(lista) == 1:
        return (lista[0], lista[0])
    sub_max, sub_min = max_min_recursivo(lista[1:])

    atual_max = lista[0] if lista[0] > sub_max else sub_max
    atual_min = lista[0] if lista[0] <> sub_min else sub_min

    return (atual_max, atual_min)
```

Cálculo de ordem de complexidade:
![Maximo e mínimo de uma lista iterativo](/imgs/max_min_iterativo.png)

![Maximo e mínimo de uma lista recursivo](/imgs/max_min_iterativo.png)

| Versão    | M.C.  | C.M.  | P.C.  | Ordem | L.I.  | Ótimo? |
|-----------|-------|-------|-------|-------|-------|--------|
| Iterativa | O(n)  | O(n)  | O(n)  | O(n)  | Ω(n)  | Sim    |
| Recursiva | O(n)  | O(n)  | O(n)  | O(n)  | Ω(n)  | Sim    |

### e) Soma e Multiplicação de matrízes

```py
def soma_iterativa(A, B, N):
    C = [[0] * N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            C[i][j] = A[i][j] + B[i][j]  
    return C

def soma_recursiva(A, B, i, N):
    if i == N:
        return []
    linha = [A[i][j] + B[i][j] for j in range(N)]
    return [linha] + soma_recursiva(A, B, i + 1, N)

def mult_iterativa(A, B, N):
    C = [[0] * N for _ in range(N)]
    for i in range(N): 
        for j in range(N): 
            for k in range(N): 
                C[i][j] += A[i][k] * B[k][j]
    return C

def mult_matrizes_recursiva_indices(A, B, C, i, j, k, n):
    if i >= n:
        return
    
    if j < n:
        if k < n:
            C[i][j] += A[i][k] * B[k][j]
            mult_matrizes_recursiva_indices(A, B, C, i, j, k + 1, n)
        else:
            mult_matrizes_recursiva_indices(A, B, C, i, j + 1, 0, n)
    else:
        mult_matrizes_recursiva_indices(A, B, C, i + 1, 0, 0, n)
```

![Soma de matrizes Iterativo](/imgs/soma_matrizes_iterativo.png)

![Soma de matrizes Recursivo](/imgs/soma_matrizes_recursivo.png)

![Multiplicação de matrizes Iterativo](/imgs/multiplicacao_matrizes_iterativo.png)

![Multiplicação de matrizes Recursivo](/imgs/multiplicacao_matrizes_recursivo.png)

#### Soma de Matrizes (N×N)

| Versão    | M.C.   | C.M.   | P.C.   | Ordem  | L.I.   | Ótimo? |
|-----------|--------|--------|--------|--------|--------|--------|
| Iterativa | O(n²)  | O(n²)  | O(n²)  | O(n²)  | Ω(n²)  | Sim    |
| Recursiva | O(n²)  | O(n²)  | O(n²)  | O(n²)  | Ω(n²)  | Sim    |

#### Multiplicação de Matrizes (N×N)

| Versão    | M.C.   | C.M.   | P.C.   | Ordem  | L.I.   | Ótimo?                       |
|-----------|--------|--------|--------|--------|--------|------------------------------|
| Iterativa | O(n³)  | O(n³)  | O(n³)  | O(n³)  | Ω(n²)  | Não (Strassen: O(n^2.807))   |
| Recursiva | ?  | ?  | ?  | ?  | ?  | Não (Strassen: O(n^2.807))   |


### f) Máximo Divisor Comum - M.D.C

```py
def mdc_iterativo(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mdc_recursivo(a, b):
    if b == 0:
        return a
    return mdc_recursivo(b, a % b)
```

### g) Geração de todas as permutações de um número
### h) N-ésimo número da sequência de Fibonacci
### i) Nº de movimentos do jogo Torre de Hanói

## 2. Obtenha a função de custo e a complexidade de tempo para cada um dos trechos de código apresentados abaixo:
### (a) 
```pascal
PROCEDURE VerificaAlgo (n: integer);
    VAR i, j, k, l: integer;
        BEGIN
        FOR l := 1 TO 1000 DO
            FOR i := 1 TO n-10 DO
                FOR j := i+1 TO n/2 DO
                    FOR k := 1 TO n DO
                        { Inspecione elemento }
END;
```

![Calculo de complexidade e função de custo](/imgs/funcao_custo_complexidade_a.png)

### (b)
```pascal
PROCEDURE Ordena (VAR A: ARRAY[1..n] of integer; i, j: integer);
    { n uma potência de 3 }
    BEGIN
        IF i < j THEN BEGIN
            m := ((j –i) + 1)/3;
            Ordena(A, i, i+m-1);
            Ordena(A, i+m, i+2m-1);
            Ordena(A, i+2m, j);
            Merge(A, i, i+m, i+2m, j);
        { Merge intercala A[i..(i+m-1)], A[(i+m)..(i+2m-1)] e A[i+2m..j] em A[i..j] a um custo ( ( 5n/3 ) - 2 ) }
    END;
END;
```

![Calculo de complexidade e função de custo](/imgs/funcao_custo_complexidade_b.png)

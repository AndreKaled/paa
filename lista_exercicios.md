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

## 3. Considere a equação abaixo, que define uma função f(n) para números inteiros não negativos. Escreva algoritmos recursivos e iterativos (não-recursivos) que representem a relação de recorrência abaixo:
$$f(n) = \begin{cases} n, & \text{para } n \le 1 \\ f(n/2), & \text{para } n > 1 \end{cases}$$

Algoritmo recursivo:
```c
int f(int n) {
    if (n <= 1) {
        return n;
    }
    return f(n / 2);
}
```

Algoritmo iterativo:
```c
int f(int n) {
    while (n > 1) {
        n = n / 2;
    }
    return n;
}
```

# Parte 2 - Entendendo o comportamento assintótico de funções
## 4 Escrever em notação O, o, Ω, ω, Θ:
### (a) $n^3 –1$
$\theta(n^3)$; $O(n^3)$; $o(n^4)$; $\Omega(n^3)$; $\omega(n^2)$

### (b) $n^2 + 2 \log n$
$\theta(n^2)$; $O(n^2)$; $o(n^3)$; $\Omega(n^2)$; $\omega(n)$

### (c) $29n + n \log n$
$\theta(n \log n)$; $O(n^2)$; $o(n^2)$; $\Omega(n \log n)$; $\omega(n)$

### (d) $3n^n + 5(2^n)$
$\theta(n^n)$; $O(n^n)$; $o(n^{n+1})$; $\Omega(n^n)$; $\omega(2^n)$

### (e) $(n-1)^n + n^{n-1})$
$\theta(n^n)$; $O(n^n)$; $o(n^{n+1})$; $\Omega(n^n)$; $\omega(n^{n-1})$

### (f) $302$
$\theta(1)$; $O(1)$; $o(\log n)$; $\Omega(1)$; $\omega(1/n)$

## 5. Demonstre se é certo ou errado:
### (a) Se $f,g$ são funções tais que $f = O(g)$ e $g = \Omega(g)$, então $f = \theta(g)$.
Note que $g = \Omega(g)$ é uma tautologia, portanto a hipótese se reduz a apenas $f = O(g)$

Suponha por absurdo que a afirmação é verdadeira, ou seja, que $f = O(g)$ implica $f = \Theta(g)$.
 
Por definição, $f = \Theta(g)$ exige duas condições simultâneas:
$$\exists\, c_1, c_2 > 0,\ n_0 \in \mathbb{N} \text{ tais que } c_1\,g(n) \le f(n) \le c_2\,g(n), \quad \forall\, n \ge n_0$$
 
Seria necessário que $f = \Omega(g)$, ou seja, que $f$ cresce pelo menos tão rápido quanto $g$.
 
Tome o contraexemplo: $f(n) = 1$ e $g(n) = n$.
 
- $f = O(g)$? Sim: $1 \le 1 \cdot n$ para todo $n \ge 1$. ✓
- Pela afirmação, deveríamos ter $f = \Theta(g)$, logo em particular $f = \Omega(g)$.
- $f = \Omega(g)$ exigiria $\exists\, c > 0$ tal que $1 \ge c \cdot n$ para todo $n$ suficientemente grande.
- Mas $c \cdot n \to +\infty$, então não existe tal $c$. Contradição, Errado.
Logo a afirmação é falsa.

### (b) Se a complexidade do M.C. de um algoritmo for $f$, então o número de passos que o algoritmo efetua, para qualquer entrada, é $\Omega(f)$.

### (c) Se a complexidade de P.C. de um algoritmo for $f$, então o número de passos que o algoritmo efetua, para qualquer entrada, é $\theta(f)$.
P.C = $f(n)$ significa que toda entrada custa $O(f(n))$ Não garante que toda entrada custe $\Omega(f(n))$. SUponha por absurdo que toda entrada tem custo $\theta(f(n))$. Tomando Insertion Sort, seu pior caso é $f(n) = \theta(n^2)$. Pela afirmação toda entrada deveria ter custo $\theta(n^2)$. Mas a entrada já ordenada o custo é $\theta(n)$, e $\theta(n) \neq \theta(n^2)$. Contradição. Errado.

### (d) A complexidade de M.C. de um algoritmo para um certo problema é necessariamente maior do que qualquer limite inferior para o problema.
Suponha por absurdo que a M.C. do algoritmo >= qualquer limite inferior do problema. Tomando Insertion Sort no problema de ordenação por comparações:
* O limite inferior do problema é $\Omega(n \log n)$
* O M.C. do Insertion Sort é $\theta(n)$ (entrada já ordenada)

Pela afirmação, deveríamos ter $\theta(n) >= \theta(n \log n)$, mas $n = o(n \log n)$, logo n cresce mais devagar que $n \log n$. Contradição. Errado.

### (e) $o(g(n)) \cap \omega(g(n))$ é o conjunto vazio.
Suponha por absurdo que existe $f$ tal que $f \in o(g)$ e $f \in \omega(g)$ simultaneamente.
Tomando $f = o(g)$ significa que $\lim_{n \to \infin} {f(n)}/{g(n)} = 0$, 
e que $f = \omega(g)$ significa que $\lim_{n \to \infin} {f(n)}/{g(n)} = +\infin$
Isso é uma contradição, pois temos que o limite $\lim_{n \to \infin} {f(n)}/{g(n)} satisfaz simultaneamente $L = 0$ e $L = +\infin$. e um limite é único, não se pode assumir dois valores simultaneos

## 6. Suponha dois algoritmos A e B, com funções de complexidade de tempo $a(n) = n^2 - n + 549$ e $b(n) = 49n + 49$, respectivamente. Determine quais valores de n pertencentes ao conjunto dos números naturais, para os quais A leva menos tempo para executar do que B.
$a(n) < b(n)$
$n^2 - n + 549 < 49n + 49$
$n^2 - n - 49n + 549 - 49 < 0$
$n^2 - 50n + 500 < 0$
$\triangle = b^2 -4ac = (-50)^2 - 4(1)(500) = 2500 - 2000 = 500$
$n = {-(-50) \pm \sqrt{500}/2(1)} = {50 \pm 10\sqrt{5}}/2 = {25 \pm 5\sqrt(5)}$

Aproximando a raiz, temos:
$13,82 < n < 36,18$

Portanto para os numeros naturais:
$n \in {14, 15, 16, ..., 35, 36}$

## 7. Verifique:
### (a) $2n^2 +1$ é $O(2^n)$
$\lim_{n \to \infin} {2n^2+1}/{2^n} = 0$
Verdade
### (b) $2n^2 +1$ é $O(n^2)$
$\lim_{n \to \infin} {2n^2+1}/{n^2} = \lim_{n \to \infin} 2 + {1}/{n^2} = 2+0 = 2$
Verdade
### (c) $n^r$ é $O(n^s)$
$\lim_{n \to \infin} {n^r}/{n^s} = \lim_{n \to \infin} n^{r-s}$
Se $r <= s$, então o limite é 1 (para $r = s$) ou 0 (para $r < s$).
Se $r > s$, então o limite tende a $\infin$.
É verdade se $r <= s$, e falso se $r > s$.
### (d) $n^{k+1}$ é $O(n^k)$
$\lim_{n \to \infin} {n^{k+1}}/{n^k} = \lim_{n \to \infin} n^{k+1-k} = \lim_{n \to \infin} n^{1} = \infin$
Como o limite tende a $\infin$, é falso.
### (e) $2^{2n}$ é $O(2^n)$
$\lim_{n \to \infin} {2^{2n}}/{2^n} = \lim_{n \to \infin} {(2^n)^2}/{2^n} = \lim_{n \to \infin} 2^n = \infin$
Como o limite tende a $\infin$, é falso.
### (f) $n \log n$ é $O(n^2)$
### (g) $403$ é $O(1)$
$\lim_{n \to \infin} {403}/{1} = 403$
Como o limite dá uma constante, é verdade.
### (h) $n \log n$ é $O(n^{1+e})$
### (h) $n^k$ é $O(2^n)$

## 8. Prove ou disprove quem é \theta de quem (faça comparações entre as 3 funções):
### (a) $f(n) = n^2-1$
### (b) $g(n) = n^2$
### (c) $h(n) = n^3$

$$\lim_{n \to \infin} {f(n)}/{g(n)} = \lim_{n \to \infin} {n^2-1}/{n^2} = \lim_{n \to \infin} {1 - 1/{n^2}} = 1 - 0 = 1$$
Como o limite é constante 1 (e maior que 0), fica provado que $f(n) = \theta(g(n))$, e por simetria $g(n) = \theta(f(n))$.

$$\lim_{x \to \infin} {g(n)}/{h(n)} = \lim_{x \to \infin} {n^2}/{n^3} = \lim_{x \to \infin} 1/n = 0$$
Como o limite é 0, g(n) cresce mais devagar que h(n), portanto a relação correta é $g(n) = o(h(n))$

$$\lim_{x \to \infin} {f(n)}/{h(n)} = \lim_{x \to \infin} {n^2-1}/{n^3} = \lim_{x \to \infin} {n^2}/{n^3} - {1}{n^3} = \lim_{x \to \infin} {1}/{n} - {1}{n^3} = 0 - 0 = 0$$
Novamente o limite é 0, portanto f(n) cresce mais devagar que h(n).

Somente $f(n) = \theta(g(n))$
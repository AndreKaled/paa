# Algoritmos de Busca e Ordenação
---

## Algoritmos de Busca

### Busca Sequencial

**Descrição:** percorre o vetor posição por posição, do início ao fim, comparando cada elemento com o valor procurado. O método funciona em vetores ordenados ou não.

**Especificação do problema**

- **Entrada:** um vetor `V` com `n` elementos inteiros (não necessariamente precisa estar ordenado); o tamanho `n` do vetor; um valor a ser localizado (`valor`).
- **Saída:** a posição (índice) de `valor` dentro de `V`, caso exista; ou `-1`, caso `valor` não pertença a `V`.
- **Restrições:** `n ≥ 0`; os índices do vetor variam de `0` a `n-1`; o vetor pode conter elementos em qualquer ordem e, neste algoritmo, elementos repetidos não alteram o resultado (é retornada a primeira ocorrência).
- **Objetivo:** determinar se `valor` está presente em `V` e devolver sua posição.

#### Como funciona na prática?
- Começa a busca no índice 0
- Pergunta "É você?" para cada elemento
- Se achar, devolve a posição
- Se não achar até o fim, devolve -1

**Pseudocódigo**

```pascal
FUNÇÃO BuscaSequencial(V, n, valor): Inteiro

    // V     -> vetor de entrada onde a busca será realizada
    // n     -> quantidade de elementos válidos em V
    // valor -> elemento que se deseja localizar em V

    PARA i DE 0 ATÉ n-1 FAÇA // vai andando do inicio ao fim
        SE V[i] = valor ENTÃO
            RETORNE i        // valor encontrado na posição i, encerra a busca
        FIM SE
    FIM PARA

    RETORNE -1               // percorreu todo o vetor e não achou o valor

FIM FUNÇÃO
```

**Complexidade:** no pior caso (valor ausente ou na última posição) são feitas `n` comparações O(n). No melhor caso (valor na primeira posição), é O(1).

---

### Busca Binária

**Descrição:** aproveita um vetor previamente ordenado para descartar, a cada passo, metade dos elementos restantes. Compara o valor procurado com o elemento do meio do intervalo de busca e decide se continua procurando na metade da esquerda ou da direita, até encontrar o valor ou o intervalo ficar vazio.

**Especificação do problema**

- **Entrada:** um vetor `V` com `n` elementos inteiros, **ORDENADO** de forma crescente; o tamanho `n` do vetor; um valor a ser localizado (`valor`).
- **Saída:** a posição (índice) de `valor` dentro de `V`, caso exista; ou `-1`, caso `valor` não pertença a `V`.
- **Restrições:** `V` deve estar ordenado (condição obrigatória para o algoritmo funcionar corretamente); `n ≥ 0`; os índices variam de `0` a `n-1`.
- **Objetivo:** localizar `valor` em tempo logarítmico, explorando a ordenação do vetor para eliminar metade das possibilidades a cada comparação.


#### Como funciona na prática?
- Define o `inicio = 0` e o `fim = n-1`
- Enquanto o `inicio` não ultrapassar o `fim`
  - Calcula o índice do meio `meio`
  - Se o valor do meio for o que quero, achamos
  - Se o meio for menor do que o procurado, joga a metade da esquerda fora (`inicio = meio + 1`)
  - Se for maior do que o procurado, joga a metade da direita fora (`fim = meio -1`)
- Se sair do loop, é pq não tinha o valor


**Pseudocódigo**

```pascal
FUNÇÃO BuscaBinaria(V, n, valor): Inteiro

    // V      -> vetor de entrada, já ORDENADO de forma crescente
    // n      -> quantidade de elementos válidos em V
    // valor  -> elemento que se deseja localizar em V
    // inicio -> limite inferior do intervalo de busca atual
    // fim    -> limite superior do intervalo de busca atual
    // meio   -> índice do elemento central do intervalo [inicio, fim]

    inicio <- 0
    fim <- n - 1

    ENQUANTO inicio ≤ fim FAÇA
        meio <- inicio + (fim - inicio) / 2   // pega o indice do meio, evitando estourar limites em vetores grandes

        SE V[meio] = valor ENTÃO
            RETORNE meio          // encontrou o valor exatamente no meio
        SENÃO SE V[meio] < valor ENTÃO
            inicio <- meio + 1     // valor está na metade direita, descarta a esquerda
        SENÃO
            fim <- meio - 1        // valor está na metade esquerda, descarta a direita
        FIM SE
    FIM ENQUANTO

    RETORNE -1                    // intervalo esvaziou: valor não está no vetor

FIM FUNÇÃO
```

**Complexidade:** a cada iteração o intervalo de busca é reduzido à metade, resultando em O(log n) no pior caso, bem mais eficiente que a busca sequencial, desde que o vetor já esteja ordenado.

---

## Algoritmos de Ordenação por Comparação

### Merge Sort

**Descrição:** algoritmo de "dividir para conquistar". Divide recursivamente o vetor ao meio até restarem sublistas de um único elemento (que já estão, por definição, ordenadas) e depois vai intercalando (*merge*) essas sublistas duas a duas, sempre produzindo uma sublista maior e ordenada, até reconstruir o vetor inteiro.

**Especificação do problema**

- **Entrada:** um vetor `V` com `n` elementos inteiros, em qualquer ordem; os índices `inicio` e `fim` que delimitam o trecho do vetor a ser ordenado; um vetor auxiliar `aux`, do mesmo tamanho de `V`, usado como área de trabalho temporária.
- **Saída:** o próprio vetor `V`, com os elementos entre as posições `inicio` e `fim` reorganizados em ordem crescente.
- **Restrições:** é necessário um vetor auxiliar (`aux`) de apoio, com o mesmo tamanho de `V`, para realizar a intercalação sem perder elementos; funciona para qualquer conjunto de valores comparáveis (não exige domínio limitado).
- **Objetivo:** ordenar o vetor de forma eficiente e estável (preserva a ordem relativa de elementos iguais), com garantia de desempenho O(n log n) mesmo no pior caso.


#### Como funciona na prática?
- A função principal divide o vetor recursivamente até sobrar 1 elemento.
- A função auxiliar (Merge) pega duas metades que já estão ordenadas e as intercala (mistura) numa nova lista temporária, do menor para o maior.
- No final, copia essa lista temporária de volta para o vetor original.


**Pseudocódigo**

```pascal
PROCEDIMENTO MergeSort(V, inicio, fim, aux)

    // V      -> vetor a ser ordenado
    // inicio -> índice inicial do trecho de V a ordenar nesta chamada
    // fim    -> índice final do trecho de V a ordenar nesta chamada
    // aux    -> vetor auxiliar (mesmo tamanho de V), usado para montar
    //           o trecho intercalado antes de copiá-lo de volta a V
    // meio   -> índice que divide [inicio, fim] em duas metades

    SE inicio < fim ENTÃO         // só há o que fazer se o trecho tem mais de 1 elemento

        meio <- inicio + (fim - inicio) / 2

        MergeSort(V, inicio, meio, aux)      // ordena recursivamente a metade esquerda
        MergeSort(V, meio + 1, fim, aux)     // ordena recursivamente a metade direita
        Merge(V, inicio, meio, fim, aux)     // intercala as duas metades já ordenadas

    FIM SE

FIM PROCEDIMENTO


PROCEDIMENTO Merge(V, inicio, meio, fim, aux)

    // i -> percorre a metade esquerda  [inicio .. meio]
    // j -> percorre a metade direita   [meio+1 .. fim]
    // k -> posição onde o próximo menor elemento é escrito em aux

    i <- inicio
    j <- meio + 1
    k <- inicio

    ENQUANTO i ≤ meio E j ≤ fim FAÇA
        SE V[i] ≤ V[j] ENTÃO
            aux[k] <- V[i]; i <- i + 1     // o menor da vez está na metade esquerda
        SENÃO
            aux[k] <- V[j]; j <- j + 1     // o menor da vez está na metade direita
        FIM SE
        k <- k + 1
    FIM ENQUANTO

    ENQUANTO i ≤ meio FAÇA          // copia o que sobrou da metade esquerda, se houver
        aux[k] <- V[i]; i <- i + 1; k <- k + 1
    FIM ENQUANTO

    ENQUANTO j ≤ fim FAÇA           // copia o que sobrou da metade direita, se houver
        aux[k] <- V[j]; j <- j + 1; k <- k + 1
    FIM ENQUANTO

    PARA k DE inicio ATÉ fim FAÇA   // devolve o trecho já intercalado para o vetor original
        V[k] <- aux[k]
    FIM PARA

FIM PROCEDIMENTO
```

**Complexidade:** O(n log n) em todos os casos (melhor, médio e pior), com custo adicional de O(n) de memória para o vetor auxiliar.

---

### Heap Sort 

**Descrição:** organiza o vetor como um heap de máximo (uma árvore binária, representada dentro do próprio vetor, em que cada nó é maior ou igual a seus filhos). Constrói esse heap e, repetidamente, retira o maior elemento (a raiz) trocando-o com o último elemento do trecho ainda não ordenado, reduzindo o heap e restaurando sua propriedade a cada remoção.

**Especificação do problema**

- **Entrada:** um vetor `V` com `n` elementos inteiros, em qualquer ordem.
- **Saída:** o próprio vetor `V`, com todos os `n` elementos reorganizados em ordem crescente.
- **Restrições:** a ordenação é feita no próprio vetor (*in-place*), sem necessidade de vetor auxiliar; não é estável (elementos iguais podem trocar de ordem relativa).
- **Objetivo:** ordenar o vetor com garantia de desempenho O(n log n) no pior caso, usando apenas espaço extra constante (O(1)), ao contrário do Merge Sort.

#### Como funciona na prática?

- Fase 1: Constrói o Heap. Percorre o vetor de trás pra frente ajustando os "pais" para serem maiores que os "filhos" (função Heapify).

- Fase 2: Ordenar de fato. Troca a raiz (maior) com o último elemento. Diminui o tamanho do heap. Rodo o Heapify na nova raiz para restaurar a regra do pai maior que os filhos. Repito.



**Pseudocódigo**

```pascal
PROCEDIMENTO HeapSort(V, n)

    // V -> vetor a ser ordenado
    // n -> quantidade de elementos em V
    // i -> variável de controle usada nos dois laços abaixo

    // 1ª fase: constrói o heap de máximo a partir do vetor desordenado.
    // Começa no último nó que tem filhos (índice n/2 - 1) e volta até a raiz.
    PARA i DE (n/2 - 1) ATÉ 0 (decrescente) FAÇA
        Heapify(V, n, i)
    FIM PARA

    // 2ª fase: repetidamente move a raiz (maior elemento) para o final
    // do trecho ainda não ordenado e refaz o heap com o restante.
    PARA i DE (n-1) ATÉ 1 (decrescente) FAÇA
        TROCA(V[0], V[i])          // maior elemento vai para sua posição final
        Heapify(V, i, 0)           // restaura o heap apenas no trecho [0, i-1]
    FIM PARA

FIM PROCEDIMENTO


PROCEDIMENTO Heapify(V, n, i)

    // Garante a propriedade de heap de máximo na subárvore com raiz em i,
    // assumindo que as subárvores dos filhos de i já são heaps válidos.
    // n     -> tamanho do heap considerado (pode ser menor que o vetor todo)
    // i     -> índice do nó raiz da subárvore a ajustar
    // maior -> índice do maior valor entre o nó i e seus filhos
    // esq   -> índice do filho esquerdo de i, na representação em vetor (2i + 1)
    // dir   -> índice do filho direito de i, na representação em vetor (2i + 2)

    maior <- i
    esq <- 2*i + 1
    dir <- 2*i + 2

    SE esq < n E V[esq] > V[maior] ENTÃO
        maior <- esq
    FIM SE

    SE dir < n E V[dir] > V[maior] ENTÃO
        maior <- dir
    FIM SE

    SE maior ≠ i ENTÃO
        TROCA(V[i], V[maior])     // desce o valor menor, sobe o filho maior
        Heapify(V, n, maior)      // repete o ajuste na subárvore afetada
    FIM SE

FIM PROCEDIMENTO
```

**Complexidade:** construir o heap custa O(n); cada uma das `n` remoções custa O(log n) para restaurar o heap — total O(n log n) no pior, médio e melhor caso, com espaço extra O(1).

---

## Ordenação Linear sem Comparação Direta

### Counting Sort

**Descrição:** em vez de comparar elementos entre si, conta quantas vezes cada valor aparece no vetor (assumindo que os valores são inteiros dentro de uma faixa limitada e conhecida, de `0` a `max`). A partir dessa contagem, calcula diretamente a posição final de cada elemento no vetor ordenado, sem nenhuma comparação entre pares de elementos.

**Especificação do problema**

- **Entrada:** um vetor `V` com `n` elementos inteiros **NÃO NEGATIVOS**, cujo valor máximo é `max`.
- **Saída:** o vetor `V` com os elementos reorganizados em ordem crescente.
- **Restrições:** os elementos devem ser inteiros não negativos, dentro de um domínio limitado e conhecido `[0, max]`; quanto maior for `max` em relação a `n`, mais memória extra o algoritmo consome (é ineficiente para domínios muito grandes ou esparsos); não faz nenhuma comparação direta entre elementos de `V`.
- **Objetivo:** ordenar o vetor em tempo linear O(n + max), explorando o domínio limitado dos valores em vez de compará-los par a par.


#### Como funciona na prática?
- Descubro qual é o maior número (max).
- Crio um vetor de contagem (cntV) do tamanho max+1, todo zerado.
- Passo pelo vetor original e conto: cntV[numero]++.
- Transformo essa contagem em contagem acumulada: agora cntV[x] diz quantos números são menores ou iguais a x.
- Percorro o vetor original de trás pra frente (pra garantir estabilidade), e coloco cada número na posição certa no vetor auxiliar, usando a contagem acumulada.
- Copio o auxiliar de volta pro original.

**Pseudocódigo**

```pascal
PROCEDIMENTO CountingSort(V, n)

    // V    -> vetor de entrada e de saída (inteiros não negativos)
    // n    -> quantidade de elementos em V
    // max  -> maior valor presente em V; define o tamanho do vetor de contagem
    // cntV -> vetor de contagem, de tamanho (max + 1); cntV[x] guarda quantos
    //         elementos de V são iguais a x e, depois, quantos são ≤ x
    // aux  -> vetor auxiliar de saída, de tamanho n, onde o resultado ordenado
    //         é montado antes de ser copiado de volta para V
    // i    -> variável de controle usada nos laços

    // descobre o maior valor do vetor
    max <- V[0]
    PARA i DE 1 ATÉ n-1 FAÇA
        SE V[i] > max ENTÃO
            max <- V[i]
        FIM SE
    FIM PARA

    // cria o vetor de contagem, do tamanho (max+1), todo zerado
    cntV <- NOVO VETOR[0..max], inicializado com 0

    // conta quantas vezes cada numero aparece em V
    PARA i DE 0 ATÉ n-1 FAÇA
        cntV[V[i]] <- cntV[V[i]] + 1
    FIM PARA

    // transforma a contagem simples em contagem acumulada:
    //    cntV[x] passa a indicar quantos elementos de V são ≤ x,
    //    ou seja, a posição final (1-based) do último elemento igual a x
    PARA i DE 1 ATÉ max FAÇA
        cntV[i] <- cntV[i] + cntV[i-1]
    FIM PARA

    // monta o vetor de saída, percorrendo V de trás para frente
    //    (garante que o algoritmo seja estável)
    aux <- NOVO VETOR[0..n-1]
    PARA i DE (n-1) ATÉ 0 (decrescente) FAÇA
        aux[ cntV[V[i]] - 1 ] <- V[i]   // posição final do elemento V[i]
        cntV[V[i]] <- cntV[V[i]] - 1    // próxima ocorrência de V[i] vai para a posição anterior
    FIM PARA

    // 6) copia o resultado ordenado de volta para o vetor original
    PARA i DE 0 ATÉ n-1 FAÇA
        V[i] <- aux[i]
    FIM PARA

FIM PROCEDIMENTO
```

**Complexidade:** O(n + max) de tempo e O(n + max) de espaço extra. É linear no tamanho da entrada apenas quando `max` não é muito maior que `n`; por isso é indicado para domínios limitados (ex.: notas de 0 a 10, idades, códigos de faixa pequena), e não para valores genéricos e muito dispersos.


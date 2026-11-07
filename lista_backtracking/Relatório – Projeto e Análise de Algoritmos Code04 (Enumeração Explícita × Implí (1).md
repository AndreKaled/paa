# Relatório – Projeto e Análise de Algoritmos: Code04 (Enumeração Explícita × Implícita)

**Nome:** André Kaled Duarte Coutinho Andrade  **Data:** 07/11/2026

---

## 1. Introdução

Esta atividade teve como objetivo praticar o projeto de algoritmos para problemas de otimização combinatória, comparando duas formas de percorrer o espaço de soluções. Na **enumeração explícita**, geramos e testamos todos os candidatos (todos os subconjuntos, todas as ordens de visita, todas as atribuições). Na **enumeração implícita**, o espaço é percorrido de forma estruturada e ramos inteiros são descartados sem serem visitados: *backtracking com poda*, *programação dinâmica sobre subconjuntos* ou uma *reformulação* do problema em uma estrutura que se resolve em tempo polinomial. 

| Questão | Técnica | Espaço explícito | Como foi evitado |
| --- | --- | --- | --- |
| Árvore de Natal (2026) | Backtracking puro (mochila 0/1) com poda por capacidade | 2^P subconjuntos de pacotes | ramos que estouram a capacidade W são cortados (sem memoização) |
| Cavalo (1513) | BFS + PD sobre subconjuntos (Held-Karp) | K! ordens de captura | O(2^K · K²) transições |
| Modificando SAT (2888) | Eliminação de Gauss em GF(2) | 2^N atribuições | O(M · N · N/64) |
| Coloração de Imagem (1907) | DFS iterativa (componentes conexos) | sequências de cliques | O(N · M), cada pixel visitado uma vez |
| Carteiro (2448) | Busca binária | varredura linear a cada entrega | O(M log N) |

**Uso de IA nesta atividade:** usei o DeepSeek em duas questões: Árvore de Natal (um Presentation Error) e Modificando SAT (um Wrong Answer 40%). Cavalo, Coloração de Imagem e Carteiro resolvi sozinho, sem IA e sem código pronto. O registro da conversa está no arquivo `AndreKaled-Code04-IAGen`. 

---

## 2 e 3. Explicação dos Problemas e dos Algoritmos de Solução

---

### Questão 1 – Árvore de Natal (2026)

#### 2.1 Enunciado (síntese)

São dados G galhos de uma árvore de Natal. Para cada galho há P pacotes de enfeites, cada um com uma quantidade de enfeites e um peso, e o galho suporta no máximo peso W. Cada pacote é levado inteiro ou não é levado. O objetivo é imprimir, para cada galho, o **número máximo de enfeites** que cabem sem passar de W (P < 100 e W < 1000). 

#### 2.2 Instância de entrada e sua solução (toy)

Instância toy minha (não é a do enunciado, cujas saídas de exemplo são 40, 37 e 52):

```
Entrada        Interpretação
1              G=1 galho
3 5            P=3 pacotes, W=5
10 4           pacote A: 10 enfeites, peso 4
7 3            pacote B:  7 enfeites, peso 3
6 2            pacote C:  6 enfeites, peso 2
```

Árvore de decisão (levar / não levar cada pacote), com as 8 folhas:

| Pacotes levados | Peso | Enfeites | Situação |
| --- | --- | --- | --- |
| nenhum | 0 | 0 | válido |
| A | 4 | 10 | válido |
| B | 3 | 7 | válido |
| C | 2 | 6 | válido |
| A, B | 7 | — | cortado (7 > 5) |
| A, C | 6 | — | cortado (6 > 5) |
| B, C | 5 | **13** | válido, **ótimo** |
| A, B, C | 9 | — | cortado |

```
Saída:
Galho 1:
Numero total de enfeites: 13
<linha em branco>
```

#### 3.1 Modelagem e pseudo-código comentado

Cada pacote gera uma decisão binária, então o espaço é uma árvore de profundidade P. A função recebe o índice `i` do pacote em análise e o peso já acumulado.

```
ARVORE(P, W, enfeites[0..P-1], peso[0..P-1]):
    função BT(i, pesoAtual):
        se i = P: devolve 0                    # CASO-BASE: todos os pacotes decididos
        melhor ← BT(i+1, pesoAtual)            # ramo 1: NÃO levar o pacote i
        se pesoAtual + peso[i] ≤ W:            # PODA: só entra no ramo 2 se cabe
            melhor ← max(melhor, enfeites[i] + BT(i+1, pesoAtual + peso[i]))
        devolve melhor
    devolve BT(0, 0)

saída, para cada galho g:
    imprime Galho g:
    imprime Numero total de enfeites: <resultado>
    imprime uma linha em branco             # sempre, inclusive após o último galho
```

#### 3.2 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** backtracking puro, isto é, enumeração implícita de uma árvore de decisão binária, com poda por viabilidade.
- **Onde:** a chamada `BT(i+1, ...)` do ramo 1 sempre ocorre; a do ramo 2 só ocorre se `pesoAtual + peso[i] ≤ W`. Essa condição é a poda: nenhuma folha com excesso de peso é explorada, e a subárvore inteira abaixo do corte é descartada.
- **Limite da técnica:** a poda é só de viabilidade. Não há poda por otimalidade (um limite superior que descarte ramos que não podem superar o melhor já achado) e não há memoização, então o mesmo estado `(i, pesoAtual)` pode ser recalculado muitas vezes. O pior caso continua O(2^P).
- **Benefício:** código curto e direto, que mapeia a decisão levar/não levar. Passou nos testes do juiz, mas o argumento da IA de que não havia risco de tempo porque P < 100 e W < 1000 **não vale** para backtracking sem memoização (isso só valeria com tabela, em O(P · W)). Fico dependendo de testes pequenos.

---

### Questão 2 – Cavalo (1513)

#### 2.3 Enunciado (síntese)

Um tabuleiro N × M tem casas bloqueadas (`#`), um cavalo (`C`) e K peões (`P`). O cavalo deve capturar **todos os peões**, em qualquer ordem, e **voltar à casa inicial**, usando o menor número de saltos em L. Há vários casos de teste, terminados por `0 0 0`. Saída: o número mínimo de saltos.

#### 2.4 Instância de entrada e sua solução (toy)

```
Entrada        Interpretação
4 4 2          tabuleiro 4x4, K=2 peões
C...           cavalo em (0,0)
..P.           peão 1 em (1,2)
.P..           peão 2 em (2,1)
....
0 0 0          fim da entrada
```

Distâncias em saltos entre os pontos importantes (0 = cavalo):

| De \\ Para | cavalo | peão 1 | peão 2 |
| --- | --- | --- | --- |
| cavalo | 0 | 1 | 1 |
| peão 1 | 1 | 0 | 2 |
| peão 2 | 1 | 2 | 0 |

Roteiros possíveis: cavalo → peão 1 → peão 2 → cavalo = 1 + 2 + 1 = 4; cavalo → peão 2 → peão 1 → cavalo = 1 + 2 + 1 = 4.

```
Saída: 4
```

#### 3.3 Modelagem e pseudo-código comentado

Os K + 1 pontos importantes formam um grafo completo cujos pesos são as distâncias do cavalo (calculadas por BFS). O problema vira um **caixeiro viajante** sobre esses pontos. `dp[mask][i]` = menor custo partindo do cavalo, capturando exatamente os peões de `mask` e terminando no peão `i`.

```
CAVALO(tab, N, M, K):
    pontos[0] ← posição do cavalo; pontos[1..K] ← posições dos peões
    para s de 0 até K:                         # uma BFS por ponto importante
        dist ← BFS_CAVALO(pontos[s])           # 8 saltos, ignora '#', -1 = não visitado
        D[s][t] ← dist[pontos[t]] para todo t
    dp[*][*] ← ∞
    para i de 0 até K-1:
        dp[{i}][i] ← D[0][i+1]                 # CASO-BASE: cavalo → peão i
    para mask de 0 até 2^K - 1:                # em ordem crescente
        para i em mask:                        # último peão capturado
            para j fora de mask:               # próximo peão
                dp[mask ∪ {j}][j] ← min(dp[mask ∪ {j}][j], dp[mask][i] + D[i+1][j+1])
    devolve min sobre i de ( dp[todos][i] + D[i+1][0] )   # fecha o ciclo voltando ao cavalo
```

#### 3.4 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** duas técnicas combinadas. (1) **BFS** em um grafo implícito (casas são vértices e saltos permitidos são arestas) para obter distâncias mínimas. (2) **PD sobre subconjuntos (bitmask)**, o algoritmo de Held-Karp para o caixeiro viajante.
- **Onde:** as BFS preenchem a matriz `D`; os três laços aninhados sobre `mask`, `i` e `j` preenchem `dp`. O estado `(mask, i)` resume tudo o que importa do passado: quais peões já foram capturados e onde o cavalo está.
- **Enumeração explícita × implícita:** testar todas as ordens de captura custa K! (15! ≈ 1,3 × 10¹²). Com a PD há 2^K · K estados e K transições por estado, ou seja, 2^15 · 15 · 15 ≈ 7,4 milhões de operações por caso.
- **Benefício:** a BFS reaproveita a estrutura do tabuleiro (bloqueios incluídos) e a PD reaproveita os prefixos de roteiros que terminam no mesmo peão com o mesmo conjunto capturado.

---

### Questão 3 – Modificando SAT (2888)

#### 2.5 Enunciado (síntese)

Dada uma fórmula booleana em forma normal conjuntiva com M cláusulas e N variáveis (M, N ≤ 2000), cada cláusula com no máximo 3 literais, decidir se existe uma atribuição em que **cada cláusula tenha exatamente 1 ou exatamente 3 literais verdadeiros**. Se existir, imprimir a **lexicograficamente máxima** (a variável de menor índice que difere deve ser `T` na maior), como uma string de N caracteres `T`/`F`; senão, imprimir `impossible`.

#### 2.6 Instância de entrada e sua solução (toy)

Segundo exemplo do enunciado:

```
Entrada                                  Interpretação
5 6                                      M=5 cláusulas, N=6 variáveis
(not x1) and                             C1
(x1 or x2 or x4) and                     C2
(x1 or x3 or x5) and                     C3
(not x2 or x3 or x5) and                 C4
(x2 or x3 or not x4)                     C5
```

Cada cláusula vira uma equação em GF(2) (soma = XOR):

| Cláusula | Equação |
| --- | --- |
| (not x1) | x1 = 0 |
| (x1 or x2 or x4) | x1 + x2 + x4 = 1 |
| (x1 or x3 or x5) | x1 + x3 + x5 = 1 |
| (not x2 or x3 or x5) | x2 + x3 + x5 = 0 |
| (x2 or x3 or not x4) | x2 + x3 + x4 = 0 |

Resolvendo: x1 = 0; de C2 e C3, x2 + x4 = 1 e x3 + x5 = 1; em C4, x2 + 1 = 0, logo x2 = 1 e x4 = 0; em C5, 1 + x3 + 0 = 0, logo x3 = 1 e x5 = 0. A variável x6 não aparece em nenhuma equação, então é **livre** e recebe `T` (o maior valor).

```
Saída: FTTFFT
```

No terceiro exemplo, `(x1 or x1 or not x1)` vira x1 + x1 + x1 = 1 + 1 = 0, ou seja, as duas ocorrências de x1 se cancelam e sobra x1 = 0. A saída é `F`.

#### 3.5 Modelagem e pseudo-código comentado

**Observação-chave:** com no máximo 3 literais, os números de literais verdadeiros permitidos (1 ou 3) são exatamente os valores **ímpares** possíveis. Logo a condição de cada cláusula é: XOR dos valores dos literais = 1. Como ¬x = x ⊕ 1, cada negação inverte o lado direito, e variáveis repetidas se cancelam. A matriz aumentada \[A | b\] é guardada em bits (64 variáveis por palavra), com b na coluna N.

```
SAT_XOR(M, N, clausulas):
    para cada cláusula i:                       # monta a linha [A | b]
        b[i] ← 1
        para cada literal (x_v, negado):
            A[i][v] ← A[i][v] XOR 1             # repetida se cancela
            se negado: b[i] ← b[i] XOR 1
    rank ← 0
    para col de N-1 até 0, DECRESCENTE:         # pivôs nos maiores índices
        procura linha r ≥ rank com A[r][col] = 1
        se não existe: col é variável LIVRE; continua
        troca linhas r e rank; pivo[col] ← rank
        para toda linha j > rank com A[j][col] = 1:
            linha j ← linha j XOR linha rank    # zera col abaixo do pivô
        rank ← rank + 1
    se existe linha i ≥ rank com A[i] = 0 e b[i] = 1:
        devolve impossible                      # equação 0 = 1
    x[v] ← 1 para toda variável livre           # T é o maior valor
    para col de 0 até N-1, CRESCENTE:
        se col é pivô (linha r):
            x[col] ← b[r] XOR (soma de A[r][j] · x[j] para j < col)
    devolve x como string de T/F
```

#### 3.6 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** **redução a um sistema linear sobre GF(2)** resolvido por eliminação de Gauss. Não é backtracking: o problema geral de SAT é NP-difícil, mas a restrição de paridade (1 ou 3 literais verdadeiros) o transforma em XOR-SAT, que é polinomial.
- **Onde:** a modelagem acontece ao ler cada cláusula; a eliminação percorre as colunas de N-1 a 0, e a substituição final percorre de 0 a N-1.
- **Por que o resultado é o lexicograficamente máximo:** como os pivôs são escolhidos nas colunas de maior índice, a linha de cada pivô tem zeros nas colunas à sua direita, então `x[col]` depende só de variáveis de índice menor. Percorrendo de 0 a N-1, cada variável livre pode valer `T` sem afetar as anteriores, e cada variável pivô fica determinada pelas anteriores. Isso é uma escolha gulosa por índice, sem precisar tentar e voltar atrás.
- **Enumeração explícita × implícita:** testar todas as atribuições custa 2^N (até 2^2000). A eliminação custa O(M · N · ⌈N/64⌉), no máximo 2000 · 2000 · 32 ≈ 1,3 × 10⁸ XORs de palavras de 64 bits.

---

### Questão 4 – Coloração de Imagem (1907)

#### 2.7 Enunciado (síntese)

Uma imagem N × M (até 1024 × 1024) tem pixels brancos (`.`) e pretos (`o`). A ferramenta “balde de tinta”, ao clicar em um pixel branco, pinta de preto toda a região de pixels brancos ligada a ele pelos **4 vizinhos** (cima, baixo, esquerda, direita). O objetivo é imprimir o **número mínimo de cliques** para pintar a imagem inteira.

#### 2.8 Instância de entrada e sua solução (toy)

```
Entrada        Interpretação
4 5            imagem 4x5
..o..
.oo..
o..oo
oo.o.
```

| Região | Pixels (linha, coluna) |
| --- | --- |
| A | (0,0), (0,1), (1,0) |
| B | (0,3), (0,4), (1,3), (1,4) |
| C | (2,1), (2,2), (3,2) |
| D | (3,4) |

O pixel (1,0) e o (2,1) só se tocam na diagonal, então não estão na mesma região. Pintar uma região não altera as outras, e um clique só alcança uma região, então são necessários 4 cliques.

```
Saída: 4
```

#### 3.7 Modelagem e pseudo-código comentado

A imagem é um grafo implícito: pixels brancos são vértices e vizinhança de 4 direções são arestas. A resposta é o número de componentes conexos.

```
COLORACAO(img, N, M):
    cliques ← 0
    para cada pixel (i, j):
        se img[i][j] = '.':
            cliques ← cliques + 1          # um clique pinta a região inteira
            DFS(i, j)                      # pinta a região para não contá-la de novo
    devolve cliques

DFS(i, j):                                  # versão iterativa, com pilha explícita
    pilha ← [(i, j)]; pinta (i, j)
    enquanto pilha não vazia:
        (x, y) ← desempilha
        para cada vizinho (nx, ny) de (x, y) dentro da imagem com img = '.':
            pinta (nx, ny)                 # marca ao empilhar: nunca entra duas vezes
            empilha (nx, ny)
```

#### 3.8 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** busca em profundidade (DFS) em grafo implícito, ou *flood fill*, para contar componentes conexos.
- **Onde:** o laço duplo sobre os pixels inicia uma DFS a cada pixel branco ainda não pintado; cada DFS consome uma região inteira.
- **Enumeração explícita × implícita:** testar sequências de cliques explode combinatoriamente. Como regiões diferentes são independentes, o mínimo é exatamente o número de componentes, e cada pixel é visitado uma vez: O(N · M), cerca de 10⁶ operações no pior caso.
- **Por que iterativa:** uma região pode ter até \~10⁶ pixels, e uma recursão dessa profundidade estouraria a pilha de chamadas; a pilha explícita fica no heap.

---

### Questão 5 – Carteiro (2448)

#### 2.9 Enunciado (síntese)

Uma rua tem N casas, cujos números aparecem em ordem crescente da primeira à última (o código usa busca binária). O carteiro começa na primeira casa e recebe M cartas, entregues na ordem dada. Ir de uma casa à vizinha leva 1 unidade de tempo. O objetivo é imprimir o tempo total de deslocamento.

#### 2.10 Instância de entrada e sua solução (toy)

```
Entrada          Interpretação
5 3              N=5 casas, M=3 cartas
10 20 30 40 50   números das casas (posições 0..4)
30 10 50         destinos das cartas, em ordem
```

| Entrega | Destino | Posição | Anterior | Tempo |
| --- | --- | --- | --- | --- |
| 1 | casa 30 | 2 | 0 (início) | 2 |
| 2 | casa 10 | 0 | 2 | 2 |
| 3 | casa 50 | 4 | 0 | 4 |

```
Saída: 8
```

#### 3.9 Modelagem e pseudo-código comentado

A ordem das entregas é fixa, então não há escolha a otimizar. O trabalho é converter cada número de casa em sua posição na rua e somar as distâncias entre posições consecutivas.

```
CARTEIRO(N, M, casas[0..N-1], destinos[1..M]):
    pos ← 0; total ← 0                        # começa na primeira casa
    para cada destino d:
        idx ← BUSCA_BINARIA(casas, N, d)      # O(log N)
        total ← total + |idx − pos|
        pos ← idx
    devolve total                             # long long: a soma pode passar de 2³¹

BUSCA_BINARIA(v, n, chave):
    esq ← 0; dir ← n − 1
    enquanto esq ≤ dir:
        meio ← esq + (dir − esq) / 2          # evita estouro de esq + dir
        se v[meio] = chave: devolve meio
        senão se v[meio] < chave: esq ← meio + 1   # descarta a metade esquerda
        senão: dir ← meio − 1                      # descarta a metade direita
    devolve −1                                # não encontrado
```

#### 3.10 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** busca binária, uma instância de divisão e conquista em que cada comparação descarta metade do espaço de busca.
- **Onde:** na função `BUSCA_BINARIA`, chamada uma vez por carta.
- **Enumeração explícita × implícita:** varrer a lista inteira a cada entrega seria O(N · M); a busca binária faz O(log N) por entrega, total O(N + M log N) contando a leitura. Aqui a “enumeração implícita” é só a eliminação de metade das posições a cada passo; não há otimização combinatória.


---

## 4. Processo de Resolução

### 4.1 Etapas realizadas

Escrevi as cinco soluções por conta própria, sem código pronto. Só em duas (Árvore de Natal e SAT) recorri à IA, e nas duas foi para entender o veredito do juiz, não para gerar a solução: a única linha de código que veio da IA foi a correção da função `altera` em SAT. Os números de versão abaixo correspondem aos arquivos que guardei.

**Árvore de Natal.** A lógica (decidir levar ou não cada pacote, com corte pela capacidade) está no meu código. A primeira submissão deu **Presentation Error (100%)**: as respostas estavam certas e só o formato diferia. Realmente não percebi o erro e levei o veredito ao DeepSeek para ele verificar.

| Versão | Saída por galho |
| --- | --- |
| v1 | `...%d\n` e, se g < G, mais `\n\n` | Presentation error (100%) |
| v2 (sugestão do DeepSeek) | `...%d\n` e, se g < G, mais `\n` |
| final | `...%d\n\n` sempre |

Contando os bytes: na v1, `40\n` seguido de `\n\n` deixa duas linhas em branco entre galhos e nenhuma depois do último. Na versão final, `40\n\n` deixa uma linha em branco depois de cada galho, inclusive o último. O juiz aparentemente esperava a linha em branco final, e a sugestão da IA (reduzir para uma linha entre galhos) corrigia só metade do problema. A correção que funcionou foi a que testei por conta própria. Depois, a explicação da IA sobre por que ela funcionou contava as linhas em branco de forma inconsistente: dizia que o formato esperado tinha duas linhas em branco entre os casos, mas a saída aceita tem uma. A IA também não conseguiu abrir o enunciado em português (as leituras falharam) e por isso deduziu o formato a partir do exemplo que colei.

**Cavalo.** Foi a questão em que mais demorei, mas o tempo foi gasto na ideia: passei dias pensando em como atacar o problema, e só depois de chegar em BFS entre os pontos importantes + PD sobre subconjuntos é que escrevi o código. Com a ideia pronta, as três versões diferem só em erros de implementação, não de lógica:

| Versão | O que estava errado / mudou | Resultado |
| --- | --- | --- |
| v1 | A matriz era declarada como `tabuleiro`, mas usada como `g` na leitura e na `bfs`; faltava `;` depois de `int full = (1 << K) -1`; a condição `!(m >> j) & 1` estava mal parentesada | erro de compilação |
| v2 | Leitura passou a usar `tabuleiro`; `;` adicionado; condição corrigida para `!((m >> j) & 1)`; sobrou um `g[a][b]` dentro da `bfs` | erro de compilação |
| v3 | Último `g` trocado por `tabuleiro` | passou |

A condição da v1 é um erro de lógica, não só de digitação: `!` tem precedência maior que `&`, então `!(m >> j) & 1` vira `(!(m >> j)) & 1`, que só é verdadeiro quando `m >> j` é 0, e não quando o peão j ainda não foi capturado. Ela não chegou a ser exercitada porque o código ainda não compilava; corrigi na v2.

**Modificando SAT.** Modelei sozinho a restrição como sistema XOR resolvido por eliminação de Gauss com bitsets. A primeira submissão deu **Wrong answer 40%**. Enviei ao DeepSeek, em um único prompt, o enunciado e o código, pedindo para identificar o erro e como corrigir.

| Versão | Mudança |
| --- | --- |
| v1 | `altera` com `1ULL << (bit & 64)` |
| final | `1ULL << (bit % 64)` |

A IA apontou exatamente essa linha. Para `bit` de 0 a 63, `bit & 64` vale sempre 0, então toda chamada alternava o bit 0 da palavra em vez do bit certo; para `bit` ≥ 64, o deslocamento podia ser 64, que é comportamento indefinido. Com isso as equações (inclusive o lado direito, guardado na coluna N) ficavam erradas, e a eliminação resolvia um sistema que não era o da fórmula. O resto do algoritmo (paridade, Gauss do maior para o menor índice, variáveis livres em `T`) a IA analisou à mão com exemplos pequenos e considerou correto; ela não executou o código. O arquivo `sat.cpp` entregue já tem a correção.

**Coloração de Imagem.** Comecei direto com a DFS recursiva, que é a forma mais natural de contar regiões, e acabei em uma versão iterativa. O que mudou entre as versões:

| Versão | O que mudou | Resultado |
| --- | --- | --- |
| v1 | DFS recursiva; matriz `img[1024][1024]` | Runtime Error |
| v2 | Mesma DFS recursiva; matriz aumentada para `img[1025][1025]` | Runtime Error |
| v3 | DFS iterativa, com pilha explícita em `vector`; matriz `img[1024][1025]` | passou |

Pelo código, minha leitura do que aconteceu é a seguinte: o `scanf(%s)` grava o caractere terminador, então cada linha precisa de M + 1 colunas; com M = 1024 a v1 não tinha espaço, e a v2 tentou resolver isso aumentando a matriz. Como a v2 já comportava as linhas e mesmo assim não passou, o problema restante era a recursão: uma região pode ter cerca de 10⁶ pixels, e uma recursão dessa profundidade estoura a pilha de chamadas. A v3 trocou a recursão por uma pilha explícita e passou.

**Carteiro.** A ideia (converter o número da casa em posição por busca binária e somar as distâncias) estava certa desde a primeira versão: a função `buscaBinaria` é idêntica nas três. O que mudou foram só erros de digitação nos nomes da variável de posição:

| Versão | O que estava errado | Resultado |
| --- | --- | --- |
| v1 | Declarei `post_atual` mas usei `pos_atual` e `pos_total` | erro de compilação |
| v2 | Declaração corrigida para `pos_atual`, mas sobrou `pos_total = novo_idx;` | erro de compilação |
| v3 | `pos_total` trocado por `pos_atual` | passou |

**Desenho Continuo.** Não tentei. esqueci do prazo de entrega e também não notei que não havia feito, mas também li a questão e fiquei sem ideia do que fazer.

### 4.2 Suporte / desenvolvimento acelerado por IA

| Questão | Ferramenta (modelo/versão) | Nº de prompts | Para que usei | O que a IA resolveu de fato |
| --- | --- | --- | --- | --- |
| Árvore de Natal | DeepSeek V4.1-Flash, com raciocínio e busca na web | 2 | Entender um Presentation Error | Apontou o formato (linhas em branco) como causa, mas sugeriu a correção errada; a correção certa foi minha. Também afirmou que não havia risco de tempo com P < 100 e W < 1000, argumento que não vale para backtracking sem memoização |
| Modificando SAT | DeepSeek V4.1-Flash, com raciocínio e busca na web| 1 | Achar o motivo do Wrong answer 40% | Achou o `bit & 64` no lugar de `bit % 64`; verificou o restante da lógica à mão |
| Cavalo | Não usei IA | — | — | — |
| Coloração de Imagem | Não usei IA | — | — | — |
| Carteiro | Não usei IA | — | — | — |

O registro completo da conversa (32 páginas) está em `AndreKaled-Code04-IAGen`.

---

## 5. Principais dificuldades e sugestões

1. **Presentation Error é invisível.** Duas linhas em branco entre os galhos e nenhuma no fim, ou uma linha em branco depois de cada galho, parecem iguais ao olho. O que resolveu foi contar os `\n` da saída. Sugestão: comparar a saída com o exemplo usando `diff` ou `cat -A` localmente, e lembrar que o juiz pode exigir quebra de linha (ou linha em branco) depois do último caso.
2. **Um operador errado derrubou um algoritmo correto.** Em SAT, trocar `%` por `&` em uma única linha de manipulação de bits deixou a matriz inteira errada, e o veredito “Wrong answer 40%” não ajuda a localizar isso. Sugestão: testar a função auxiliar isoladamente (conferir que `altera(v, bit)` liga exatamente aquele bit) e comparar com uma força bruta para N pequeno (2^N com N ≤ 10).
3. **Uso crítico da IA.** Em SAT, um prompt bastou. Em Árvore de Natal, a IA errou o diagnóstico do formato, descreveu mal os bytes na explicação final e usou um argumento inválido sobre complexidade. Sugestão para a atividade: pedir à IA hipóteses *e* um teste mínimo que as confirme, e verificar o resultado antes de aceitar.
4. **Backtracking puro depende de testes fracos.** O meu passou, mas é O(2^P) no pior caso. Aprendizado: estimar 2^P antes de escolher a técnica e saber que o mesmo problema tem solução O(P · W) por PD.
5. **Ver o tamanho do espaço antes de escolher a técnica.** K! (15!) levou ao bitmask, 2^N (até 2^2000) levou à reformulação em XOR, e as regiões independentes de Coloração levaram à contagem de componentes. Em cada caso a modelagem foi o que tornou a enumeração implícita possível.
6. **Casos limite não tratados.** Em Cavalo (peão inalcançável, K = 0) e em Carteiro (destino inexistente) o código depende de garantias do enunciado.

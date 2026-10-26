# Relatório – Projeto e Análise de Algoritmos: Code03 (Programação Dinâmica)

**Nome:** André Kaled Duarte Coutinho Andrade 
**Data:** 26/10/2026

---

## 1. Introdução

Esta atividade teve como objetivo praticar o projeto de algoritmos por programação dinâmica (PD). A PD resolve problemas que têm subestrutura ótima (a solução ótima é composta por soluções ótimas de subproblemas) e subproblemas sobrepostos (os mesmos subproblemas aparecem várias vezes). Em vez de recalcular, guardamos o resultado de cada subproblema em uma tabela e o reaproveitamos. Na prática, a maior parte dos meus erros esteve justamente na definições de casos-base e nas condições de "estado inválido", não na ideia geral.

Foram resolvidas quatro questões do Beecrowd:

| Questão | Tipo de PD | Estado |
| --- | --- | --- |
| Maçãs (1517) | Maior caminho em sequência (parecido com LIS) | `dp[i]` |
| Roleta Turca (1485) | Seleção de pares não sobrepostos em vetor circular | `dp[j][k]` |
| Troco | Soma de subconjuntos (mochila 0/1 booleana) | `vet[v]` |
| Canhão de Destruição | Mochila 0/1 | `dano[p]` |

**Uso de IA nesta atividade:** usei IA principalmente para depurar Maçãs (Kimi) e Roleta Turca (Claude). Em ambos os casos, parte do código já era meu antes de pedir ajuda. O registro dos prompts e das respostas está no arquivo `AndreKaled-Code03-IAGen`.

---

## 2 e 3. Explicação dos Problemas e dos Algoritmos de Solução

---

### Questão 1 – Maçãs (1517)

#### 2.1 Enunciado (síntese)

Rafael está em uma grade N×M e anda 1 casa por segundo em qualquer das 8 direções. Caem K maçãs; a maçã i cai na posição (xᵢ, yᵢ) e só é apanhada se Rafael estiver lá exatamente no instante tᵢ. Os tempos vêm em ordem não-decrescente. Dada a posição inicial de Rafael (no tempo 0), o objetivo é imprimir o **número máximo de maçãs** que ele consegue apanhar. A posição inicial é lida **depois** das K maçãs.

#### 2.2 Instância de entrada e sua solução (toy)

```
Entrada          Interpretação
5 5 3            grade 5x5, K=3 maçãs
2 2 2            maçã 1: (2,2) no tempo 2
5 5 3            maçã 2: (5,5) no tempo 3
3 3 4            maçã 3: (3,3) no tempo 4
1 1              Rafael começa em (1,1) no tempo 0
0 0 0            fim da entrada
```

A distância entre dois pontos com movimento em 8 direções é `max(|dx|, |dy|)` (distância de Chebyshev). Como Rafael pode esperar parado, basta `tⱼ - tᵢ ≥ distância`.

```
Linha 1 .  .  .  .  .       (R = início, 1/2/3 = maçãs)
Linha 2 .  1  .  .  .
Linha 3 .  .  3  .  .
Linha 4 .  .  .  .  .
Linha 5 .  .  .  .  2
        c1 c2 c3 c4 c5      R em (1,1)
```

| i | Vem de | Distância | Tempo disponível | Alcançável? | dp\[i\] |
| --- | --- | --- | --- | --- | --- |
| 1 | início | 1 | 2 | sim | 1 |
| 2 | início | 4 | 3 | não | 0 (inalcançável) |
| 2 | maçã 1 | 3 | 1 | não | 0 |
| 3 | início | 2 | 4 | sim | 1 |
| 3 | maçã 1 | 1 | 2 | sim | **2** |

```
Saída: 2
```

A maçã 2 é importante nesta instância: ela é inalcançável e o algoritmo não pode usá-la como ponto de partida para a maçã 3.

#### 3.1 Modelagem e pseudo-código comentado

`dp[i]` = maior número de maçãs apanhadas por um percurso que **termina** na maçã i (0 = inalcançável). O índice 0 representa a posição inicial de Rafael, com t = 0.

```
MAÇÃS(K, x[0..K], y[0..K], t[0..K]):      # índice 0 = posição inicial
    dp[1..K] ← 0                           # 0 = ainda inalcançável
    resposta ← 0
    para i de 1 até K:
        para j de 0 até i-1:               # candidatos a "maçã anterior"
            d ← max(|x[i]-x[j]|, |y[i]-y[j]|)   # 8 direções
            # só parte de j se j for o início OU uma maçã já alcançável
            se (j = 0 ou dp[j] > 0) e t[i]-t[j] ≥ d:
                dp[i] ← max(dp[i], dp[j] + 1)   # apanha a maçã i
        resposta ← max(resposta, dp[i])
    devolve resposta
```

#### 3.2 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** programação dinâmica, com tabela unidimensional (o problema se parece com a subsequência crescente mais longa, em que "crescente" vira "alcançável a tempo").
- **Onde:** no laço duplo, que preenche `dp[i]` a partir de todos os `dp[j]` com j < i. Os tempos já estão ordenados, então os candidatos a anterior são só os índices menores.
- **Por que PD:** o melhor percurso que termina em i contém, como prefixo, o melhor percurso que termina em algum j anterior (subestrutura ótima). Sem a tabela seria preciso testar todos os subconjuntos das K maçãs, ou seja, O(2^K).
- **Benefício:** O(K²) tempo e O(K) memória; com K ≤ 1000 são cerca de 500 mil comparações por caso.

---

### Questão 2 – Roleta Turca (1485)

#### 2.3 Enunciado (síntese)

Uma roleta circular tem S espaços numerados (−64 a 64). São jogadas B bolas numeradas (−64 a 64). Cada bola ocupa **dois espaços adjacentes**, e as bolas não se sobrepõem. As bolas ficam na mesma **ordem cíclica** em que foram jogadas, mas pode haver espaços vazios entre elas. O valor de uma bola é `Y × (soma dos dois espaços)`; esse valor é o que a banca **paga** (se for negativo, a banca recebe). A arrecadação da banca é a soma dos `−Y × (a+b)` das bolas. O objetivo é imprimir a **arrecadação máxima** possível entre todas as posições válidas.

#### 2.4 Instância de entrada e sua solução (toy)

```
Entrada               Interpretação
6 2                   S=6 espaços, B=2 bolas
3 -2 4 1 -5 2         espaços X0..X5 (sentido horário)
2 -3                  bolas Y1=2, Y2=-3
0 0                   fim da entrada
```

Pares adjacentes (k, k+1) e suas somas, de forma circular:

```
  pares:   p0=(0,1)  p1=(1,2)  p2=(2,3)  p3=(3,4)  p4=(4,5)  p5=(5,0)
  somas:      1         2         5        -4        -3         5
```

Ganho da banca com a bola 1 (Y=2) em um par de soma s: **−2·s**. Com a bola 2 (Y=−3): **+3·s**. Dois pares se sobrepõem se compartilham um espaço (ex.: p2 e p3 compartilham o espaço 3).

| Bola 1 em | Bola 2 em | Ganho bola 1 | Ganho bola 2 | Total |
| --- | --- | --- | --- | --- |
| p3 (−4) | p5 (5) | +8 | +15 | **23** |
| p4 (−3) | p2 (5) | +6 | +15 | 21 |
| p3 (−4) | p2 (5) | sobrepõe | — | inválido |

```
Saída: 23
```

#### 3.3 Modelagem e pseudo-código comentado

Fixo uma **rotação** i (onde o "corte" do círculo acontece) e trato os espaços como um vetor linear de S posições a partir de i. Para cada rotação:

`dp[j][k]` = maior arrecadação ao colocar as **j primeiras bolas** usando apenas os **k primeiros espaços** da rotação.

```
ROLETA(S, B, X[0..S-1], Y[0..B-1]):
    melhor ← -∞
    para i de 0 até S-1:                    # testa cada rotação (corte do círculo)
        dp[0..B][0..S] ← -∞                 # -∞ = configuração impossível
        dp[0][k] ← 0 para todo k            # CASO-BASE: 0 bolas = ganho 0
        para j de 1 até B:                  # j <= B (inclusive!)
            para k de 2 até S:
                # opção 1: nenhuma bola termina no espaço k-1
                dp[j][k] ← dp[j][k-1]
                # opção 2: a bola j ocupa os espaços k-2 e k-1
                se dp[j-1][k-2] ≠ -∞:
                    a ← X[(i+k-2) mod S]; b ← X[(i+k-1) mod S]
                    dp[j][k] ← max(dp[j][k], dp[j-1][k-2] - Y[j-1]*(a+b))
        melhor ← max(melhor, dp[B][S])
    devolve melhor
```

#### 3.4 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** programação dinâmica com tabela bidimensional (bolas × espaços), uma instância do padrão "escolher itens em ordem, sem sobreposição".
- **Onde:** a escolha em `dp[j][k]` é binária: o espaço k−1 fica livre, ou ele é o fim do par da bola j. A recorrência combina as duas opções com `max`.
- **Tratamento do círculo:** o círculo é quebrado em S vetores lineares (um por rotação). Algum corte fica logo antes do par da primeira bola, então todos os arranjos circulares são cobertos, inclusive aqueles em que uma bola atravessa a fronteira original do vetor (por isso o `mod S`).
- **Por que PD (e não força bruta):** o número de formas de posicionar as bolas cresce combinatoriamente; a tabela evita reavaliar as mesmas combinações.
- **Benefício:** O(S · S · B) por caso, no pior caso 250·250·125 ≈ 7,8 milhões de operações, bem abaixo do limite de 3 s.
- **Detalhe técnico:** o valor fica em `long long` e o "impossível" é um sentinela `LLONG_MIN/4` (dividir por 4 evita estouro ao subtrair valores).

---

### Questão 3 – Troco

#### 2.5 Enunciado (síntese)

Dado um valor V (≤ 10⁵) e M moedas (M ≤ 10³, cada uma com valor ≤ 10⁵), decidir se existe um **subconjunto** das moedas cuja soma seja exatamente V. Cada moeda só pode ser usada uma vez. Imprimir `S` se for possível e `N` caso contrário.

#### 2.6 Instância de entrada e sua solução (toy)

```
Entrada        Interpretação
10 4           V=10, M=4 moedas
6 5 3 2        valores das moedas
```

Soma alcançável após considerar cada moeda (só somas ≤ 10):

| Após a moeda | Somas alcançáveis |
| --- | --- |
| (nenhuma) | {0} |
| 6 | {0, 6} |
| 5 | {0, 5, 6} |
| 3 | {0, 3, 5, 6, 8, 9} |
| 2 | {0, 2, 3, 5, 6, 7, 8, 9, **10**} |

```
Saída: S      (5 + 3 + 2 = 10)
```

Nesta instância, o guloso que subtrai a moeda enquanto "cabe" (6, depois 3) termina com resto 1 e erra; é por isso que o problema precisa de PD.

#### 3.5 Modelagem e pseudo-código comentado

`vet[v]` = verdadeiro se existe um subconjunto das moedas já processadas que soma exatamente v.

```
TROCO(V, M, moedas[0..M-1]):
    vet[0..V] ← falso
    vet[0] ← verdadeiro                      # CASO-BASE: soma 0 sempre possível
    para cada moeda m:
        para v de V até m, DECRESCENTE:      # decrescente = cada moeda usada 1 vez
            se vet[v - m]: vet[v] ← verdadeiro
    devolve (vet[V] ? 'S' : 'N')
```

#### 3.6 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** PD de **soma de subconjuntos** (mochila 0/1 na versão booleana), com otimização de espaço para 1 dimensão.
- **Onde:** a transição `vet[v] ← vet[v] ou vet[v-m]` reaproveita as somas já construídas com as moedas anteriores.
- **Ponto central:** o laço de `v` vai de trás para frente. Se fosse para a frente, `vet[v-m]` poderia já ter sido atualizada na mesma moeda e ela seria contada várias vezes (isso resolveria o problema com moedas ilimitadas).
- **Benefício:** O(V·M) ≈ 10⁸ operações simples no pior caso e O(V) de memória; um guloso é O(M), mas incorreto.

---

### Questão 4 – Canhão de Destruição

#### 2.7 Enunciado (síntese)

Há N projéteis, cada um com um poder de destruição e um peso. O canhão carrega projéteis até a capacidade K (soma dos pesos ≤ K) e é carregado uma única vez. Se o **dano total máximo** for ≥ R (resistência do castelo), imprime-se `Missao completada com sucesso`; senão, `Falha na missao`. Há vários casos de teste.

#### 2.8 Instância de entrada e sua solução (toy)

```
Entrada        Interpretação
1              1 caso de teste
3              N=3 projéteis
10 4           projétil A: poder 10, peso 4
7 3            projétil B: poder 7,  peso 3
6 2            projétil C: poder 6,  peso 2
5              K=5 (capacidade)
13             R=13 (resistência)
```

Evolução do vetor `dano[0..5]` (dano máximo com capacidade p):

| Após o projétil | dano\[0\] | dano\[1\] | dano\[2\] | dano\[3\] | dano\[4\] | dano\[5\] |
| --- | --- | --- | --- | --- | --- | --- |
| (início) | 0 | 0 | 0 | 0 | 0 | 0 |
| A (10, 4) | 0 | 0 | 0 | 0 | 10 | 10 |
| B (7, 3) | 0 | 0 | 0 | 7 | 10 | 10 |
| C (6, 2) | 0 | 0 | 6 | 7 | 10 | **13** |

Melhor carga: B + C (peso 3+2 = 5, dano 13). Como 13 ≥ 13:

```
Saída: Missao completada com sucesso
```

#### 3.7 Modelagem e pseudo-código comentado

`dano[p]` = maior dano obtenível com carga de peso **no máximo** p.

```
CANHÃO(N, poder[], peso[], K, R):
    dano[0..K] ← 0                           # CASO-BASE: sem carga, sem dano
    para cada projétil i:
        para p de K até peso[i], DECRESCENTE: # decrescente: usa o projétil 1 vez
            dano[p] ← max(dano[p], dano[p - peso[i]] + poder[i])
    se dano[K] ≥ R: imprime "Missao completada com sucesso"
    senão:           imprime "Falha na missao"
```

#### 3.8 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** PD da **mochila 0/1**, com vetor unidimensional.
- **Onde:** `max(dano[p], dano[p-peso]+poder)` compara "não levar o projétil" com "levar o projétil". Como o vetor foi inicializado com 0, `dano[p]` já é o melhor para peso **até** p, então `dano[K]` é a resposta.
- **Subestrutura ótima:** o melhor dano com capacidade p usando os i primeiros projéteis é o melhor entre excluir ou incluir o i-ésimo, em cima do melhor dano com a capacidade restante.
- **Benefício:** O(N·K), no máximo 50·100 = 5000 operações por caso, contra O(2^N) da força bruta.

---

## 4. Processo de Resolução

### 4.1 Etapas realizadas

Em todas as questões, comecei escrevendo uma tentativa própria (nenhuma foi obtida pronta). Os números de versão abaixo correspondem aos arquivos que guardei.

**Maçãs.** Modelei o problema como `dp[i]` terminando na maçã i, com distância `max(|dx|,|dy|)`. Entrei na PD sozinho, mas errei a leitura da entrada e o caso-base.

| Versão | O que mudou | Resultado |
| --- | --- | --- |
| v1 | Li a posição inicial **antes** das maçãs | Wrong answer 70% |
| v2 | Passei a ler a posição inicial **depois** das maçãs (indicação do Kimi) | Wrong answer 40% |
| v3 | Exigi `j == 0 \|\| dp[j] > 0` para só partir de maçã alcançável (indicação do Kimi) | Wrong answer 95% |
| v4 / v5 | Testes de variação da ordem de leitura da posição inicial; não resolveram | continuaram errando |
| **final** | Troquei `dp[j] + (j > 0)` por `dp[j] + 1` | Aceito |

O erro real estava na linha `dp[j] + (j > 0)`. Quando j = 0 (posição inicial), `dp[0] = 0` e `(j > 0)` vale 0, então pegar a primeira maçã dava `0 + 0 = 0`, ou seja, "inalcançável". Com o teste de alcançabilidade, nenhuma maçã se tornava alcançável e a resposta ficava quase sempre 0, o que explica o 95%: a maioria dos casos de teste tinha resposta pequena. A correção é somar 1 sempre, porque pegar uma maçã vale 1 independentemente do estado anterior.

**Roleta Turca.** Minha primeira ideia foi tentar cada rotação e colocar as bolas coladas (posições `2j` e `2j+1`). Em v1 havia ainda um erro de digitação (`Y[...]` onde era `X[...]`), corrigido em v2; mesmo assim falhou (80%), porque a suposição de bolas coladas está errada: o enunciado permite espaços vazios entre as bolas. Depois de pedir ajuda, entendi que era preciso escolher onde cada bola vai, o que exige PD. Ao passar para o meu código a recorrência sugerida, copiei de forma incompleta (v3): faltou o caso-base `dp[0][k] = 0` e o laço estava `j < B` em vez de `j <= B`, então `dp[B][S]` ficava como "impossível". Com as duas correções, a versão final foi aceita.

**Troco.** foi um guloso: percorria as moedas na ordem dada, subtraindo as que cabiam. Tinha dois erros: o guloso não é correto para soma de subconjuntos, e a impressão estava invertida (`if(V)` imprimia `S` quando sobrava resto). Na versão final usei a PD `vet[]` com laço decrescente.

**Canhão.** Reconheci o problema como mochila. As primeiras versões deram erro de compilação. Em v3 compilou, mas o laço interno tinha `p++` em vez de `p--`, o que fazia o índice passar do limite do vetor; corrigido na versão final. 

### 4.2 Suporte / desenvolvimento acelerado por IA

| Questão | Ferramenta (modelo/versão) | Nº de prompts | Para que usei | O que a IA resolveu de fato |
| --- | --- | --- | --- | --- |
| Maçãs | Kimi K3 | 3 | Pedir para apontar erros no código | Achou a ordem de leitura e a necessidade de testar alcançabilidade; não achou o `(j > 0)` e, no último prompt, sugeriu reescrever com ordenação e `cin`/`cout` |
| Roleta Turca | Claude (Sonnet 5.5) | 2 | Entender o erro de modelagem e corrigir a cópia incompleta | Explicou que as bolas não são coladas, propôs a PD `dp[j][k]` com rotação, e apontou o caso-base e o `j < B` na minha cópia |


O registro completo está em `AndreKaled-Code03-IAGen`.

---

## 5. Principais dificuldades e sugestões

1. **Casos-base e estados inválidos.** Em Maçãs, o `(j > 0)` e a ambiguidade do valor 0 (início válido × maçã inalcançável) custaram a maior parte do tempo. Em Roleta, esqueci `dp[0][k] = 0`. Aprendizado: ao definir `dp`, escrever explicitamente o que o valor 0 (ou −∞) representa e testar com a instância toy à mão antes de submeter.
2. **Modelagem antes do código.** Em Roleta, a primeira versão estava correta para um problema diferente (bolas coladas). Ler o enunciado procurando suposições ("há espaços vazios?") teria evitado duas submissões.
3. **Guloso vs. PD.** Em Troco, o guloso parece natural, mas falha em contraexemplos simples como o da instância toy.
4. **Direção do laço na mochila.** Em Troco e Canhão, o sentido do laço (decrescente) decide se o item é usado uma vez ou várias; em Canhão, o erro `p++` mostra que um erro trivial em um laço muda tudo.
5. **Veredito "Wrong answer %" é pouco informativo.** O 95% de Maçãs sugeria um erro pequeno, mas era um erro de lógica que anulava quase todas as respostas. Sugestão: escrever meus próprios casos-limite (inclusive com resposta 1) e comparar com uma força bruta pequena.
6. **Uso crítico da IA.** A resposta do Kimi "a lógica está correta" estava errada; a IA não substitui verificar o código com a instância toy. Sugestão para a atividade: pedir, junto com o código, uns casos de testes mínimos que reproduza o erro.

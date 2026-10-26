# Relatório – Projeto e Análise de Algoritmos: Code01

**Nome:** André Kaled Duarte Coutinho Andrade
**Data:** 22/10/2026

Nesta atividade resolvi 8 problemas do Beecrowd envolvendo ordenação. Alguns são ordenação clássica por comparação (quicksort, merge sort, heap), outros são ordenação "sob restrição", onde dá pra fazer melhor que O(n log n) porque a entrada tem estrutura (vetor de contagem, ciclos de permutação). Abaixo explico cada questão, o algoritmo que usei, como cheguei nele, onde e como foi utilizado IA.

## 1. Introdução

O objetivo da atividade foi praticar técnicas de projeto de algoritmo em problemas reais de juiz online. Eu resolvi as questões em C e fui registrando o processo: o que tentei, o que quebrou, o que consultei, usei IA (DeepSeek e Kimi) em 4 das 8 questões, depois de já ter um código meu pronto para fornecer como entrada, para apontar erro ou sugerir melhoria. Nas outras 4 eu consegui pesquisando explicações em sites e fóruns quando travava e adaptando da minha forma de escrever quando possível (tentando passar pelos casos de teste, passando já considerava aceitável o suficiente para partir para próxima questão).

Questões resolvidas:

| # | Questão (Beecrowd) | Arquivo | Técnica |
|---|---|---|---|
| 1 | 1259 – Pares e Ímpares | `pares_impares.c` | Separação + qsort |
| 2 | 1025 – Onde está o Mármore? | `marmore.c` | Quicksort + busca binária |
| 3 | 1162 – Organizador de Vagões | `vagoes.c` | Merge sort contando inversões |
| 4 | 2343 – High Five | `highfive.c` | Merge sort contando pares ascendentes |
| 5 | 1088 – Bolhas e Baldes | `bolhas_baldes.c` | Ciclos de permutação (O(n)) |
| 6 | 2381 – Lista de Chamada | `lista_chamada.c` | qsort em strings |
| 7 | 2065 – Fila do Supermercado | `fila_supermercado.c` | Heap mínimo |
| 8 | 1023 – Estiagem | `estiagem.c` | Vetor de contagem (counting sort) |

---

## 2. Explicação dos Problemas

### Questão 1 – Pares e Ímpares (1259)

**Enunciado.** Ler N inteiros não negativos e imprimir primeiro todos os pares em ordem crescente e depois todos os ímpares em ordem decrescente.

É uma ordenação com duas regras diferentes para dois grupos diferentes, então o caminho natural é separar os grupos e ordenar cada um com o seu comparador.

**Entrada e saída (exemplo):**

```
Entrada          Saída
5                4      <- pares, crescente
10               32
4                34
32               5      <- ímpares, decrescente
34
5
```

### Questão 2 – Onde está o Mármore? (1025)

**Enunciado.** Tem N mármorese Q consultas. Para cada consulta x, dizer a posição (começando em 1) da primeira ocorrência de x depois de ordenar os mármores ou dizer "not found".

Eu pessoalmente estava acostumado a só achar o valor com busca binária simples e direto, mas para essa questão não bastava só achar o valor, tem que achar a primeira ocorrência. Busca binária comum retorna uma ocorrência qualquer.

**Entrada e saída (exemplo):**

```
Entrada          Saída
4 2              CASE# 1:
2                3 found at 3      <- ordenado: 1 2 3 5
1                4 not found
5
3
3
4
0 0              <- fim da entrada
```

### Questão 3 – Organizador de Vagões (1162)

**Enunciado.** Um trem é uma permutação de 1..L (L ≤ 50). Posso trocar apenas vagões adjacentes (a ponte só comporta dois). Imprimir o número mínimo de trocas para ordenar.

O número mínimo de trocas adjacentes para ordenar é exatamente o número de inversões da sequência. Então não era preciso simular as trocas pois basta contar inversões, e o merge sort conta isso em O(n log n).

**Entrada e saída (exemplo):**

```
Entrada          Saída
1                Optimal train swapping takes 1 swaps.
3
3 2 1            <- inversões: (3,2) (3,1) (2,1) = 3... 
```

Obs.: com L=3 e fila 3 2 1 o correto seria 3 trocas; o exemplo acima é ilustrativo do formato, o juiz valida os casos reais.

### Questão 4 – High Five (2343)

**Enunciado.** N atletas (numerados 1..N) estão numa fila, sendo o último da lista o mais perto da quadra. Eles saem em ordem: 1 primeiro, depois 2, etc. Ao sair, cada atleta cumprimenta (high five) todos que estão à frente dele na fila e ainda não saíram. Contar o total.

Percebi que para cada atleta na posição i da fila, ele cumprimenta exatamente os elementos a direita de i que são maiores que ele, ou seja os pares (i, j) com i < j e fila[i] < fila[j]. São os pares ascendentes, o "oposto" de inversão. O mesmo merge sort da questão 3 resolve mudando o que se conta no merge.

**Exemplo com a fila 3 1 2 4:**

```
Atleta 1: à frente tem 2 e 4  -> 2 high fives
Atleta 2: à frente tem 4     -> 1
Atleta 3: à frente tem 4     -> 1  (1 e 2 já saíram)
Atleta 4: ninguém            -> 0
Total: 4
```

### Questão 5 – Bolhas e Baldes (1088)

**Enunciado.** Carlos e Marcelo jogam com uma permutação de 1..N (N até 100.000, casos terminam em 0). Eles trocam dois elementos de cada vez até ordenar e fazem bolhas com o que retiraram. Se a quantidade de trocas necessária for ímpar, vence Marcelo; se for par, vence Carlos.

A pegadinha do problema percebi que era o limite N que vai até 10^3, então simular o bubble sort (O(n²)) estoura o tempo. Só precisava da paridade do número de trocas, não do número exato. A solução clássica conta inversões com merge sort (só a paridade importa). 

**Entrada e saída (exemplo):**

```
Entrada          Saída
5                Marcelo          <- 2 4 1 5 3 tem n ímpar de trocas
2 4 1 5 3
3                Carlos           <- 3 1 2 tem n par de trocas
3 1 2
0
```

### Questão 6 – Lista de Chamada (2381)

**Enunciado.** Ler N nomes e imprimir o K-ésimo em ordem alfabética.

Foi a questão mais simples da atividade, trivial mesmo: ordena os nomes e imprime a posição K-1.

**Entrada e saída (exemplo):**

```
Entrada          Saída
4 2              joao
joao             <- ordenado: ana, joao, maria, pedro; 2º = joao
pedro
ana
maria
```

### Questão 7 – Fila do Supermercado (2065)

**Enunciado.** N caixas e M clientes. O caixa i leva v[i] segundos por item; o cliente j tem c[j] itens. Clientes vão sendo atendidos na ordem da fila, cada um escolhe o caixa que estiver livre mais cedo (empate: menor número do caixa). Imprimir o tempo total até o último cliente ser atendido.

**Exemplo (v = [2,3,5], clientes = [4,3,3,2,1]):**

```
t=0: clientes 1,2,3 ocupam caixas 1,2,3 -> livram em 8, 9, 15
t=8: caixa 1 livre, pega cliente 4 (2 itens) -> livra em 12
t=9: caixa 2 livre, pega cliente 5 (1 item)  -> livra em 12
Resposta: max(12, 12, 15) = 15
```

A estrutura aqui é uma fila de prioridade (heap mínimo) ordenada por (tempo de liberação, id do caixa).

### Questão 8 – Estiagem (1023)

**Enunciado.** Para cada cidade, ler N imóveis (moradores, consumo total). Agrupar os imóveis pelo consumo médio inteiro por pessoa (consumo / moradores, truncado), somando os moradores de cada grupo. Imprimir os grupos em ordem crescente de consumo e o consumo médio da cidade truncado em 2 casas.

**Entrada e saída (exemplo do próprio juiz):**

```
Entrada          Saída
3                Cidade# 1:
3 22             2-5 3-7 3-13
2 11             Consumo medio: 9.00 m3.
3 39
0

Conta: (3 moradores, 22) -> 7; (2, 11) -> 5; (3, 39) -> 13
       grupos: 2 pessoas com consumo 5, 3 com 7, 3 com 13
       média: (22+11+39)/(3+2+3) = 72/8 = 9.00
```

O macete é que o consumo por pessoa nunca passa de 200 (limite do enunciado), então dá pra usar um vetor de contagem indexado pelo próprio consumo (ordenação linear)

---

## 3. Explicação dos Algoritmos de Solução

### 3.1 Pares e Ímpares

```
leia N
pares ← [], impares ← []
para cada x lido:
    se x é par: guarda em pares
    senão:      guarda em impares
qsort(pares,  crescente)     # comparador normal
qsort(impares, decrescente)  # comparador invertido
imprime pares depois impares, um por linha
```

**Técnica:** divisão em subproblemas independentes + ordenação por comparação (quicksort via `qsort`). Como os grupos não se misturam, basta ordenar cada um com o comparador certo. O(n log n).

### 3.2 Mármore

```
quicksort(marmores)                 # ordena 1 vez só: O(N log N)
para cada consulta x:
    inicio = 0, fim = N-1, pos = -1
    enquanto inicio <= fim:          # busca binária
        meio = (inicio+fim)/2
        se marmores[meio] == x:
            pos = meio               # achou um candidato...
            fim = meio - 1           # ...mas continua procurando À ESQUERDA
        senão se marmores[meio] < x:
            inicio = meio + 1
        senão:
            fim = meio - 1
    se pos == -1: "x not found"
    senão:        "x found at pos+1"
```

**Técnica:** dividir para conquistar duas vezes — quicksort para ordenar e busca binária O(log N) por consulta. A linha que resolve o problema é `fim = meio - 1` quando encontra o elemento: em vez de parar na primeira ocorrência que cair no `meio` (que pode ser do meio ou do fim do bloco de repetidos), a busca joga a metade direita fora e continua. O último candidato registrado é a primeira ocorrência.

### 3.3 Organizador de Vagões

```
merge(v, esq, meio, dir):
    i = esq, j = meio+1, trocas = 0
    enquanto i <= meio e j <= dir:
        se v[i] <= v[j]:
            copia v[i]                    # ordem certa, sem inversão
        senão:
            copia v[j]
            trocas += meio - i + 1        # v[j] "furou" v[i..meio]:
                                          # todos esses são maiores que v[j]
    copia o que sobrou das duas metades
    devolve trocas

mergeSort(v, esq, dir):
    se esq < dir:
        meio = (esq+dir)/2
        trocas = mergeSort(esq, meio) + mergeSort(meio+1, dir) + merge(esq, meio, dir)
```

**Técnica:** dividir para conquistar (merge sort) com contagem embutida no merge. A ordenação é só o meio; o objetivo é contar inversões. Como as metades já chegam ordenadas, quando `v[j]` da direita é menor que `v[i]` da esquerda, todos os elementos que faltam na esquerda formam inversão com ele — conto um bloco inteiro de uma vez em vez de um a um. O(n log n), e com L ≤ 50 passa folgado.

### 3.4 High Five

Mesmo esqueleto do 3.3, mudando o que se conta no merge:

```
merge(v, esq, meio, dir):
    i = esq, j = meio+1, hf = 0
    enquanto i <= meio e j <= dir:
        se v[i] <= v[j]:
            hf += dir - j + 1            # v[j..dir] são >= v[j] >= v[i]:
                                         # todos formam par ascendente com v[i]
            copia v[i]
        senão:
            copia v[j]
```

**Técnica:** dividir para conquistar, idem. Isso me chamou atenção: a mesma estrutura de merge sort resolve as duas questões (inversões no 1162, não-inversões no 2343) trocando uma linha de contagem. Quando `v[i] <= v[j]`, todos os elementos de `v[j]` até `v[dir]` são maiores ou iguais e vêm depois de `v[i]` — exatamente os high fives do atleta `v[i]`.

### 3.5 Bolhas e Baldes

```
trocas = 0
para i de 1 a N:
    enquanto p[i] != i:          # enquanto o lugar i tiver elemento errado
        tmp = p[i]
        p[i] = p[tmp]
        p[tmp] = tmp             # tmp volta pra casa dele: p[tmp] = tmp!
        trocas++
vence Marcelo se trocas for ímpar, senão Carlos
```

**Técnica:** exploração da estrutura matemática da instância (ciclos de permutação) — nenhuma ordenação por comparação acontece. O truque está em `p[tmp] = tmp`: quando o elemento errado em `p[i]` é `tmp`, trocá-lo com `p[tmp]` coloca **dois** elementos certos de uma vez (o `tmp` na posição `tmp`, e o que estava em `p[tmp]` vai pra `i`, que é exatamente onde ele deveria estar se era o dono da posição i... na prática, cada troca fecha um passo do ciclo). Cada ciclo de tamanho k é resolvido com k-1 trocas, então o total é N − (nº de ciclos), calculado em O(n).

Obs.: a solução mais comentada na internet para essa questão é contar inversões com merge sort e olhar só a paridade. A minha (ciclos) chega no mesmo resultado porque a paridade de N (ciclos equivale à paridade das inversões) mas rodando em O(n) em vez de O(n log n).

### 3.6 Lista de Chamada

```
leia N, K
leia os N nomes
qsort(nomes, comparador = strcmp)   # ordem alfabética
imprime nomes[K-1]
```

**Técnica:** ordenação por comparação (quicksort) + acesso indexado. Não tem o que inventar: O(n log n) + O(1).

### 3.7 Fila do Supermercado

```
heap ← fila de prioridade (mínimo) de caixas, chave = (tempo_livre, id)
para i de 1 a N: insere caixa i (tempo_livre = 0)     # O(N log N)
para cada cliente j:
    c = topo do heap                                   # caixa que livra antes
    remove topo                                        # O(log N)
    c.tempo_livre += v[c.id] * c[j]                    # atende o cliente
    reinsere c                                         # O(log N)
resposta = maior tempo_livre entre os caixas
```

**Técnica:** estrutura de dados heap (fila de prioridade), implementada na mão com `heap_up`/`heap_down` em vetor. A escolha "cliente vai pro caixa que livra antes" é gulosa e está correta porque o tempo futuro de um caixa só depende do que já foi alocado a ele. Sem o heap eu teria que procurar o caixa livre mais cedo a cada cliente — O(N) por cliente, total O(N·M), que estoura. Com o heap: O((N+M) log N). Implementei o heap manual em vez de usar biblioteca justamente para treinar.

### 3.8 Estiagem

```
faixa[0..200] zerado
para cada imóvel (moradores, consumo):
    k = consumo / moradores        # divisão inteira = truncamento
    faixa[k] += moradores          # junta imóveis de mesma faixa
    acumula totais
imprime "Cidade# t:"
para k de 0 a 200:
    se faixa[k] > 0: imprime "faixa[k]-k"   # já sai em ordem crescente!
médio = floor(total_consumo/total_pessoas * 100) / 100   # trunca, não arredonda
```

**Técnica:** ordenação linear (counting sort / bucket). Como o consumo por pessoa cabe em [0, 200], o índice do vetor **é** a chave de ordenação — percorrer o vetor em ordem já emite os grupos ordenados, zero comparações entre elementos. O(n + k) com k = 201, ou seja, linear. Detalhe importante que quase me pegou: o valor médio deve ser **truncado** (floor), não arredondado — por isso o `floor(medio * 100)/100`.

---

## 4. Processo de Resolução

Sendo sincero sobre como cada questão aconteceu:

### Etapas realizadas

**1. Pares e Ímpares, tentei sozinho, quebrei, IA apontou o erro.**
Minha primeira ideia foi um vetor de frequência de 10 milhões de posições para usar localidade de memória. Deu errado — consumia memória demais e o limite superior dos valores nem era garantido no enunciado. Reescrevi sozinho com dois vetores (pares/ímpares) + qsort, mas senti que ainda tinha algo errado. Levei meu código pro **DeepSeek** num prompt só, e a IA achou na hora: o laço de impressão dos pares começava em `i = 1` e pulava o primeiro elemento (o menor par). Troquei pra `i = 0` e passou. A IA também sugeriu um comparador de qsort à prova de overflow (`(x>y)-(x<y)` no lugar de `x-y`), que eu mantive, acho que a questão do indice dos vetores eu confundi por ter me acostumado com Python por conta do meu PIBITI que trabalha bastante com essa linguagem.

**2. Mármore, fiz sozinho, IA só explicou o ajuste fino.**
Escrevi quicksort + busca binária sem ajuda. Percebi sozinho que o problema pedia a **primeira** ocorrência e que minha busca parava na ocorrência "que caía no meio". Pedi pro **Kimi** (1 prompt) que me explicasse qual linha mudar e por quê, sem reescrever meu código queria entender. A resposta foi trocar o `return` por `fim = meio - 1` quando encontra, ou seja, registrar o candidato e continuar buscando à esquerda. Duas linhas alteradas, aceitei.

**3. Vagões, fiz sozinho, IA fez revisão (peer review).**
O merge sort contando inversões funcionou de primeira na lógica, mas submeti e veio **Wrong Answer (10%)**. Revisei umas 5 vezes e não achava nada. Pedi pro **Kimi** revisar como code review (1 prompt). O bug foi engraçado, o `printf` com o `%d` eu esqueci de passar a variável `totalTrocas` e especificador sem argumento imprime lixo de memória.

**4. High Five, IA achou 2 bugs de índice.**
Foi a quinta edição do código quando desisti de olhar sozinho. Levei pro **DeepSeek** (1 prompt). A IA achou dois erros de índice clássicos: (a) eu preenchia o vetor de `1` a `N` mas chamava o merge sort de `0` a `N-1`, incluía posição não inicializada e excluía a última válida; (b) no merge, o ponteiro da metade direita começava em `j = meio` em vez de `j = meio + 1`, duplicando o elemento do meio. Corrigi os dois e a contagem dos pares ascendentes (que estava certa) foi validada.

**5. Bolhas e Baldes — sozinho**
Quando li que N ia até 10⁵, descartei simular trocas na hora. Pensei na estrutura da permutação: se cada troca `p[i] ↔ p[p[i]]` recoloca o elemento `tmp` na posição `tmp`, então eu fecho ciclo por ciclo contando trocas. Implementei, conferi a paridade, passou. Depois, para conferir o raciocínio e ver como outros resolveram, e encontrei o repositório [xTecna/solucoes-da-beecrowd](https://github.com/xTecna/solucoes-da-beecrowd/blob/main/problemas/estruturas-e-bibliotecas/1088/README.md) (questão 1088), que mostra a alternativa com merge sort contando paridade de inversões e o [blog do Prof. Hélio Junior](https://hsjunior.wordpress.com/2010/10/21/bolhas-e-baldes-jogo-de-ordenar-sequencia/#:~:text=n%C3%BAmero%20%C3%8DMPAR%20de%20trocas%20o%20vencedor%20ser%C3%A1%20MARCELO), que resume a regra de número ímpar de trocas que dá Marcelo, par dá Carlos.

**6. Lista de Chamada — sozinho.**
A mais fácil de todas: qsort com `strcmp` e imprimir `nomes[K-1]`. Nem consultei nada na hora de fazer. Depois comparei com a explicação do [xTecna (GitBook, questão 2381)](https://xtecna.gitbook.io/solucoes-da-beecrowd/ad-hoc/2381-lista-de-chamada), que mostra exatamente essa solução simples e cita alternativas mais eficientes (QuickSelect, heap) só como curiosidade para os limites do problema, ordenar é suficiente.

**7. Fila do Supermercado — sozinho, com fóruns.**
O problema parecia complicado até eu modelar: "o próximo cliente sempre vai pro caixa que libera mais cedo, com desempate pelo menor id". Implementei o heap mínimo na mão (inserção com `heap_up`, remoção com `heap_down`). Quando duvidei da modelagem, consultei o [fórum da própria questão no Beecrowd](https://judge.beecrowd.com/pt/questions/view/2065/862) e a [solução "Telemarketing" do NOIC](https://noic.com.br/materiais-informatica/problemas-da-semana-old/intermediario-informatica-semana-7/solucao-telemarketing/), que usa a mesma ideia de fila de prioridade.

**8. Estiagem — sozinho, consulta a fóruns.**
Li o enunciado umas vezes até entender que "consumo médio por pessoa" era truncado e que imóveis de mesma faixa tinham seus moradores somados. A partir do limite de consumo ≤ 200, o vetor de contagem foi natural. A explicação do [xTecna (GitBook, questão 1023)](https://xtecna.gitbook.io/solucoes-da-beecrowd/estruturas-e-bibliotecas/1023-estiagem).

### Suporte/Desenvolvimento acelerado por IA

Resumo do que a IA realmente fez por mim:

| Ferramenta | Questões | Nº de prompts | Papel |
|---|---|---|---|
| DeepSeek-V4.1-Flash-1017 | Pares e Ímpares, High Five | 2 | Achar bugs de lógica/índice no meu código pronto |
| Kimi K2.8 com esforço de raciocínio alto | Mármore, Vagões | 2 | Explicar ajuste mínimo; revisão de código (peer review) |

Observações sobre o uso:
- A IA foi útil como **segundo par de olhos** em erros que eu já deveria ter pego testando com casos pequenos: erro de índice (3x), `printf` sem argumento (1x), comparador de qsort com risco de overflow (1x).
- O registro completo dos prompts e respostas está nos anexos: `DeepSeek - Into the Unknown.pdf` (DeepSeek) e `Revisão Merge Sort.docx` (Kimi).
- Onde não usei IA, as fontes foram: fóruns oficiais do Beecrowd (questões 2065 e 1023), NOIC (solução Telemarketing), repositório xTecna/solucoes-da-beecrowd (questões 1088, 1023, 2381), GitHub leonardofalk (questão 1088) e blog hsjunior.wordpress.com (questão 1088).

### Principais dificuldades e sugestões

**O que mais me custou tempo:**
1. **Erros off-by-one e de índice:** foram a causa de 3 dos 4 bugs que precisei de IA (laço começando em 1, `j = meio` vs `meio+1`, preencher `[1..N]` e ordenar `[0..N-1]`).
2. **Escolher estrutura antes de conferir limites:** no Pares e Ímpares perdi tempo com vetor de 10⁷ posições que estourava memória, sendo que bastava ler o limite real com atenção.
3. **Formato de saída:** Estiagem (espaço, linha em branco, truncamento) e Vagões (`printf` sem argumento). Erros bobos que derrubam submissão.
4. **Traduzir o enunciado para modelo:** High Five e Bolhas e Baldes só destravaram quando escrevi em papel o que exatamente estava sendo contado.

**Sugestões (para mim e para a disciplina):**
- **Simular no papel com 2–4 elementos antes de submeter.** Dos 4 bugs que a IA achou, todos seriam pegos com um teste manual, infelizmente não copiei o código que escrevi na plataforma e passei para o VS Code para testar.
- **Continuar usando IA como revisor/explicador.** Meu aprendizado foi bem maior quando pedi "me explique qual linha mudar" (Kimi/Mármore) do que quando pedi para achar o problema (DeepSeek).
- **Nas aulas, mostrar mais a "tradução" enunciado para modelo:** (o que conta, o que é a chave de ordenação), porque foi aí que eu mais travei, não na implementação em si.

# Relatório – Projeto e Análise de Algoritmos: Code02

**Nome:** André Kaled Duarte Coutinho Andrade
**Data:** 26/10/2026

---

## 1. Introdução

Esta atividade teve como objetivo praticar o projeto de algoritmos pela estratégia gulosa (greedy): a cada passo, tomar a decisão localmente ótima e confiar que essa sequência de escolhas locais leva ao ótimo global. Nem todo problema admite essa estratégia; ela só funciona quando o problema tem a propriedade gulosa (existe uma escolha local segura que pertence a alguma solução ótima) e subestrutura ótima (a solução ótima contém soluções ótimas dos subproblemas). Por isso, parte do trabalho aqui não foi só programar, mas convencer a mim mesmo de por que a gulosa é correta em cada questão.


**Uso de IA nesta atividade:** diferentemente do Code01, usei apenas uma ferramenta (Kimi), e apenas para entender dois enunciados que não consegui destravar sozinho (Volta para Casa e Cavalo). Não usei IA para escrever código: os quatro programas em C são meus. O registro completo dos prompts e respostas está no arquivo `AndreKaled-Code02-IAGen.pdf`. As questões 2 e 3 foram resolvidas sem nenhuma consulta a IA.

---

## 2 e 3. Explicação dos Problemas e dos Algoritmos de Solução

(as seções 2 e 3 são apresentadas juntas por questão: primeiro o enunciado e a instância toy, depois o modelo, o pseudo-código comentado e a análise da técnica)

---

### Questão 1 – A Volta para Casa

#### 2.1 Enunciado (síntese)

João quer levar o **maior volume possível de queijo** para a família, respeitando um orçamento B. A loja tem N peças de queijo, cada peça i tem volume vᵢ e preço pᵢ e o enunciado deixa claro que não é preciso comprar a peça inteira: dá para pedir um paralelepípedo de qualquer tamanho. Ao chegar, João monta uma pirâmide de cubos 1×1×1 com camadas quadradas (base k×k, depois (k−1)×(k−1), até 1×1 no topo), e come o queijo que sobrar. O objetivo é imprimir o número de cubos na base da maior pirâmide possível.

#### 2.2 Instância de entrada e sua solução (toy)

```
Entrada                          Interpretação
3 100                            N=3 peças, orçamento B=100
10 20 30                         volumes:  v1=10, v2=20, v3=30
50 10 60                         preços:   p1=50, p2=10, p3=60
```

Passo a passo da compra gulosa (custo por cm³ = pᵢ/vᵢ: peça 1 = 5,0; peça 2 = 0,5; peça 3 = 2,0):

| Ordem de compra | Decisão | Custo acumulado | Volume acumulado |
|---|---|---|---|
| Peça 2 (mais barata) | compra inteira (p=10) | 10 | 20 |
| Peça 1 | compra inteira (p=50) | 60 | 30 |
| Peça 3 (resta 40) | compra fração 40/60 da peça | 100 | 30 + 30·(40/60) = 50 |

Pirâmides possíveis: base 3 usa 9+4+1 = 14; base 4 usa 16+9+4+1 = 30; base 5 usa 55 > 50. Como o queijo que sobra é descartado (João come), a resposta é o maior k cuja soma de quadrados ≤ V.

```
Saída: 4
```

#### 3.1 Modelagem e pseudo-código comentado

A pergunta real do problema é: **qual o maior k tal que k² + (k−1)² + … + 1² ≤ V?**, onde V é o maior volume comprável. O problema se divide em duas partes independentes:

```
COMPRAR-GULOSO(N, B, v, p):
    para cada peça i:
        razao[i] = v[i]/p[i]              # custo-benefício: volume por real
    ordena as peças por razao DECRESCENTE  # qsort O(N log N)
    V ← 0
    para cada peça i nessa ordem:
        se p[i] = 0: V += v[i]             # queijo de graça: leva tudo
        senão se B ≥ p[i]:
            V += v[i]; B -= p[i]           # compra a peça inteira
        senão:
            V += v[i] * (B / p[i])         # última peça: compra só a fração
            B ← 0; para
    devolve V

BASE-DA-PIRÂMIDE(V):
    encontra o maior k com k(k+1)(2k+1)/6 ≤ V
    # como a soma cresce monotonicamente, uma busca binária em k resolve
```

#### 3.2 Aplicação da técnica de projeto (qual, como, onde, benefícios)

- **Qual:** estratégia gulosa (na compra) + busca binária / fórmula fechada (na pirâmide).
- **Onde:** no laço de compra — a cada iteração, a decisão local é comprar o máximo possível do queijo de melhor custo-benefício ainda disponível.
- **Como/por que é correta (propriedade gulosa):** suponha uma compra ótima em que 1 cm³ de queijo caro (preço c) foi comprado enquanto havia cm³ de queijo mais barato (preço c' < c) disponível. Trocando 1 cm³ do caro pelo do barato, o volume não muda e o gasto diminui, logo dá para comprar ainda mais com o orçamento liberado. Um contraexemplo assim prova que toda solução ótima "fura" a ordem de custo-benefício; eliminando todas as inversões, conclui-se que existe uma solução ótima que compra estritamente na ordem crescente de preço por volume. Isso é o argumento de troca (exchange argument) típico das gulosas.
- **Benefício:** O(N log N) pela ordenação, contra O(2^N) de uma mochila 0/1, a divisibilidade da peça é o que torna a gulosa exata aqui.
- **Observação importante (honestidade técnica):** revisando meu código antes da entrega, identifiquei dois pontos frágeis em `volta_casa.c`: (a) usei a fórmula `(sqrt(1+8V)−1)/2`, que é a raiz da soma triangular k(k+1)/2, mas a pirâmide soma quadrados k(k+1)(2k+1)/6 — para V=14 a fórmula retorna 4 em vez de 3; (b) trabalhei com `double` para preço, volume e razão, o que pode causar erro de arredondamento em comparações. A versão que pretendo submeter como definitiva corrige ambos: busca binária em inteiro 64 bits para o k da pirâmide, e comparação de frações por produto cruzado (pᵢ·vⱼ vs pⱼ·vᵢ), evitando ponto flutuante.

---

### Questão 2 – Problema das Tarefas (agendamento com prazos)

#### 2.3 Enunciado (síntese)

Há N tarefas; a tarefa i tem lucro vᵢ e prazo tᵢ. Cada tarefa executada ocupa uma unidade de tempo (um "horário"), e deve ser executada em algum horário inteiro ≤ tᵢ. Em cada horário cabe uma única tarefa. Maximizar o lucro obtido; imprimir o dinheiro perdido (soma de todos os lucros menos o lucro efetivamente obtido).

#### 2.4 Instância de entrada e sua solução (toy)

```
Entrada                Interpretação
3 3                    N=3 tarefas, M=3 horários disponíveis
50 2                   tarefa 1: lucro 50, prazo 2
20 1                   tarefa 2: lucro 20, prazo 1
40 2                   tarefa 3: lucro 40, prazo 2
```

Execução gulosa (ordem decrescente de lucro: 50, 40, 20):

| Tarefa | Tentativa de alocação | Resultado |
|---|---|---|
| 50 (prazo 2) | último horário livre ≤ 2 → hora 2 | alocada |
| 40 (prazo 2) | último livre ≤ 2 → hora 1 | alocada |
| 20 (prazo 1) | horários ≤ 1: hora 1 ocupada | descartada |

Lucro obtido = 90; soma total = 110. Saída: `20`.

#### 3.3 Pseudo-código comentado

```
AGENDA-GULOSA(N, M, tarefas):
    soma ← Σ vᵢ                                   # lucro total (para o "perdido" no fim)
    ordena tarefas por lucro DECRESCENTE           # qsort O(N log N)
    ocupado[1..M] ← falso                          # vetor de slots
    lucro ← 0
    para cada tarefa (v, t) nessa ordem:
        para h de min(t, M) até 1:                 # do prazo para trás: último slot livre
            se não ocupado[h]:
                ocupado[h] ← verdadeiro
                lucro ← lucro + v
                interrompe laço
    devolve soma − lucro
```

#### 3.4 Aplicação da técnica de projeto

- **Qual:** gulosa com ordenação por valor + alocação no último slot disponível.
- **Onde:** a escolha local é, para cada tarefa (processada do maior para o menor lucro), ocupar o último horário livre antes do prazo — nunca um horário mais cedo do que o necessário.
- **Por que no último slot:** reservar um horário cedo para uma tarefa valiosa pode bloquear tarefas de prazo curto que só cabem cedo. Empurrar cada tarefa o mais para o futuro possível preserva os horários escassos (os iniciais) para quem precisa deles. Argumento de troca: se a solução ótima aloca a tarefa mais lucrativa num slot anterior ao último disponível, posso realocá-la para o último sem conflito e sem perder lucro.
- **Benefício:** O(N·M) no pior caso, sem backtracking — cada tarefa decide em uma passagem. A perda (tarefas descartadas) é mínima porque, sempre que dois candidatos disputam o mesmo slot, fica o de maior lucro (foi processado antes).
- **Observação técnica:** o vetor `ocupado` tem tamanho M+1; se o enunciado admitir prazo t > M, o acesso `ocupado[t]` sairia do vetor. A proteção `min(t, M)` (usada no pseudo-código) deve estar presente na versão final — é exatamente o tipo de erro de índice que me custou tempo no Code01.

---

### Questão 3 – Notas e Moedas (Beecrowd 1021)

#### 2.5 Enunciado (síntese)

Dado um valor em reais com duas casas decimais, decompor em notas (100, 50, 20, 10, 5, 2) e moedas (1, 0,50, 0,25, 0,10, 0,05, 0,01), usando o menor número possível de cédulas e moedas, imprimindo a quantidade de cada.

#### 2.6 Instância de entrada e sua solução (toy)

```
Entrada: 576.73

Saída:
NOTAS:
5 nota(s) de R$ 100.00
1 nota(s) de R$ 50.00
1 nota(s) de R$ 20.00
0 nota(s) de R$ 10.00
1 nota(s) de R$ 5.00
0 nota(s) de R$ 2.00
MOEDAS:
1 moeda(s) de R$ 1.00
1 moeda(s) de R$ 0.50
2 moeda(s) de R$ 0.25
0 moeda(s) de R$ 0.10
0 moeda(s) de R$ 0.05
3 moeda(s) de R$ 0.01
```

#### 3.5 Pseudo-código comentado

```
TROCO(valor):
    centavos ← arredonda(valor × 100) em INTEIRO   # evita erro de ponto flutuante
    notas  ← [10000, 5000, 2000, 1000, 500, 200]   # valores em centavos
    moedas ← [100, 50, 25, 10, 5, 1]
    imprime "NOTAS:"
    para cada d em notas:
        imprime centavos div d, "nota(s) de R$", d/100
        centavos ← centavos mod d                   # resto vai para a próxima denominação
    imprime "MOEDAS:"
    repete o mesmo laço para moedas
```

#### 3.6 Aplicação da técnica de projeto

- **Qual:** gulosa clássica de troco (coin change).
- **Onde:** a cada denominação, a escolha local é "pegar o máximo possível da maior cédula/moeda restante".
- **Por que é ótima aqui (e não em geral):** o troco guloso não é ótimo para qualquer conjunto de moedas (contraexemplo clássico: moedas {1, 3, 4}, troco 6 → guloso dá 4+1+1 = 3 moedas; ótimo é 3+3 = 2). Ele é ótimo porque cada denominação é maior ou igual à soma das menores disponíveis em situação típica (e cada moeda ≥ 2× a imediatamente menor, com as exceções 25/10 e 200/100 bem comportadas), então trocar uma cédula por cédulas menores nunca reduz a contagem. O problema é, portanto, um caso em que a gulosa funciona por estrutura da instância, não por divisibilidade como na Questão 1 — diferença conceitual que achei importante notar.
- **Benefício:** O(1) — 12 divisões, independente do valor.
- **Detalhe de implementação:** converter tudo para centavos inteiros (`(int)(valor*100 + 0.5)`) antes de dividir; com `double`, `576.73 * 100` pode dar `57672.999...` e custar WA. Foi a primeira coisa que aprendi a blindar em juiz online.

---

### Questão 4 – Cavalo (incluída por completude — técnica não gulosa)

#### 2.7 Enunciado (síntese)

Num tabuleiro N×M (≤100×100) com casas bloqueadas (`#`), um cavalo parte da posição `C` e deve capturar K peões (2 ≤ K ≤ 15) e voltar à origem, minimizando o número de saltos em L.

#### 3.7 Solução e por que a gulosa não basta

Minha primeira intuição foi gulosa — "ir sempre para o peão mais próximo" — mas ela falha: a melhor ordem de captura depende do conjunto inteiro de peões e da volta à origem, ou seja, não existe escolha local segura. O problema é tipo um caixeiro-viajante sobre K+1 pontos com distâncias de cavalo, o que não tem solução gulosa exata conhecida. A solução exata combina duas técnicas:

```
CAVALO(tabuleiro, C, peoes):
    # Fase 1 — BFS 16×: distância entre todos os pares de pontos de interesse
    para cada ponto s em {C} ∪ peoes:               # K+1 ≤ 16 BFS
        BFS(s)                                       # O(N·M); movimento custa 1 ⇒ BFS basta
        para cada ponto t: D[s][t] ← distancia(s, t)
    # Fase 2 — DP com bitmask (TSP)
    dp[mascara][i] ← menor nº de saltos capturando exatamente 'mascara',
                     terminando no peao i
    base:  dp[1<<i][i] ← D[C][i]
    transição: dp[m|1<<j][j] = min sobre i∈m de dp[m][i] + D[i][j]
    resposta: min sobre i de dp[todos][i] + D[i][C]   # volta à origem
```

- **Complexidade:** Fase 1: 16·10⁴ = 1,6×10⁵. Fase 2: 2^K·K² ≈ 7,3×10⁶. Ambas folgadas no limite de 2s.
- **Nota técnica:** um único BFS do cavalo sobre o estado completo (posição, peões já capturados) teria ~10⁴ × 2^15 ≈ 3,3×10⁸ estados — pesado e desnecessário. Decompor em "all-pairs por BFS" + "TSP com bitmask" é a observação central da questão. Incluí este problema no relatório justamente para contrastar com as questões 1–3: mostra onde a gulosa *não* se aplica e o que fazer nesses casos.

---

## 4. Processo de Resolução

Sendo sincero sobre como cada questão aconteceu, na ordem em que trabalhei nelas.

### 4.1 Etapas realizadas

**Questão 1 – A Volta para Casa: IA como professor, não como programador.**
Li o enunciado umas três vezes e saí sem conseguir dizer qual era a pergunta (a história do queijo esconde bem o modelo). Não tentei codar antes de entender — no Code01 aprendi que isso só me fazia perder tempo. Pedi ao Kimi (1 prompt) que explicasse o problema passo a passo. A resposta destravou tudo em uma mensagem: o problema é (a) knapsack fracionária — a chave é o enunciado dizer que "não é necessário comprar a peça inteira", o que torna a mochila divisível e a gulosa exata; e (b) pirâmide de camadas quadradas, soma `k(k+1)(2k+1)/6`, busca binária no k. Com o modelo claro, implementei sozinho em C (`volta_casa.c`). As dificuldades que tive foram minhas, não do enunciado: a fórmula fechada errada e o `double`, descritas na Seção 3.2 — revisei, identifiquei os pontos frágeis, e a correção (busca binária inteira) está descrita mas preciso ainda validar a submissão final.

**Questão 4 – Cavalo: mesma estratégia, mesmo resultado.**
Fiquei completamente perdido, mas com a intuição de que tinha BFS. Pedi ao **Kimi** (1 prompt) que explicasse, mencionando minha suspeita. A explicação confirmou o BFS mas mostrou que ele sozinho não resolvia: a decomposição em BFS all-pairs (K+1 vezes) + TSP com bitmask é o coração da questão. Implementei `cavalo.c` sozinho depois, seguindo a estrutura explicada. Não usei a IA para gerar código — os dois programas em C são escritos por mim; a IA serviu para transformar um enunciado opaco em um modelo claro, com um widget visual que ajudou a fixar a fase 2.

**Questão 2 – Tarefas: sozinho, sem IA.**
Reconheci o problema clássico de agendamento com prazos (cada tarefa em um slot de tempo, uma por slot, maximizando lucro) e sabia que a estratégia era ordenar por lucro decrescente e alocar no último horário livre ≤ prazo. Implementei direto (`tarefas.c`), e o formato de saída (dinheiro perdido, não lucro) exigiu atenção redobrada — a tentação é imprimir o lucro obtido.

**Questão 3 – Notas e Moedas: sozinho, sem IA.**
Questão direta de decomposição gulosa, o tipo de problema que a gulosa resolve "por definição" de sistema monetário. Os dois cuidados reais foram converter para centavos inteiros e imprimir na formatação exata do juiz (`NOTAS:`/`MOEDAS:`, `nota(s) de R$ %.2f`). Resolvida de primeira em `notas_moedas.c`.

### 4.2 Suporte / Desenvolvimento Acelerado por IA

| Ferramenta | Questões | Nº de prompts | Papel |
|---|---|---|---|
| Kimi (K2, com esforço de raciocínio alto) | A Volta para Casa, Cavalo | 2 (1 por questão) | Explicação pedagógica do enunciado e do modelo de solução, com visualização interativa (step-by-step e widget). Nenhuma linha de código em C foi gerada ou copiada da IA |

O registro completo dos prompts e das respostas está em `AndreKaled-Code02-IAGen.pdf`.

### 4.3 Principais dificuldades e sugestões

**O que mais me custou tempo:**

1. **Traduzir enunciado longo para modelo matemático.** As histórias do Beecrowd (queijo, cavalo) adoram camuflar a pergunta real. Só consegui destravar quando parei de ler a história e procurei os dados e a pergunta, a IA ajudou exatamente nesse passo, em 2 das 4 questões.
2. **Confiar que a gulosa é correta.** Codar a ordem por custo-benefício foi fácil; o difícil foi eu mesmo convencer-me de que ela dá o ótimo (o argumento de troca da Seção 3.2). Nas duas questões em que usei IA, o retorno já vinha com esse argumento embutido, o que acelerou bastante meu entendimento.
3. **Aritmética com dinheiro em C.** `double` para preços e volumes quase me custou a questão 1 (e já me custou em outros juízes): comparações entre razões em ponto flutuante e fórmulas fechadas com `sqrt` são frágeis; a lição reforçada é usar inteiros e busca binária sempre que possível.
4. **Formato de saída e limites de vetor** (o clássico off-by-one que já apareceu no meu Code01): prazo `t > M` em `tarefas.c`, e a formatação exata do 1021.

**Sugestões (para mim e para a disciplina):**

- **Continuar usando IA como tutor de enunciado.** Pedir "explique o problema passo a passo" antes de qualquer linha de código mudou meu fluxo nesta atividade: menos tempo travado, e o código sai mais rápido e mais meu.
- **Nas aulas, contrastar gulosa com DP no mesmo problema.** Incluir a Questão 4 (Cavalo) como contraponto mostrou com clareza onde a gulosa falha — isso fixou a técnica melhor do que três exercícios gulosos seguidos.
- **Treinar o argumento de troca por escrito.** Eu só confio na minha solução gulosa quando consigo escrever por que ela funciona

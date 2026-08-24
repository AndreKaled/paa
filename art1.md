# É fácil ou é difícil? Perguntas básicas na teorica da complexidade computacional

Problemas P fazem parte de **polinomiais** (ou problemas de P :p) e esse tipo de problema pode ser resolvido em tempo polinomial em relação ao tamanho da entrada, ou seja, a quantidade de cômputos necessários para resolver cresce como alguma potência de `n`, algo tipo `O(n)`, `O(n²)`, `O(n³)` etc.

Problemas NP fazem parte de **polinômio não-determinístico** (problemas de NP), e são problemas cujas soluções podem ser verificadas em tempo polinomial.

Uma coisa interessante é que um problema pode ser difícil de resolver, mas depois que se tem uma solução é relativamente fácil verificar se ela está correta, isto é: um problema pode ter uma **verificação simples mesmo quando encontrar a solução é difícil**.

Isso me lembra, em partes, refutação por contraexemplo, provar que "para todo X, a propriedade P(x) é verdadeira" é muito mais complicado do que encontrar apenas um x (contraexemplo) para derrubar a afirmação inteira, como por exemplo a afirmação "Todo número primo é impar", e temos o número 2 que é coincidentemente primo e par ao mesmo tempo, simples assim a afirmação se prova ser falsa, também me lembrou demonstração por contradição, que é meu método preferido em argumentação :D

`obs: a analogia nao é uma equivalência, mas a ideia de que encontrar algo pode ser mais difícil do que verificar uma evidência é parecida`

## Definições
- **Problema computacional:** problema que recebe uma entrada e possui uma ou mais soluções válidas para essa entrada. Resolver computacionalmente significa encontrar uma forma de chegar a uma solução a partir da entrada.
- **Algoritmo:** uma sequência finita de operações executadas sobre uma entrada para chegar a um resultado.
- **Complexidade computacional:** estudo de quanto tempo/recursos são necessários para resolver um problema, especialmente como esse custo cresce conforme aumenta o tamanho da entrada.
- **Tempo polinomial:** quando o número de operações necessárias pode ser limitado por algum polinômio em n, como `O(n)`, `O(n²)`, `O(n³)` etc.
- **Exponencial:** a quantidade de operações pode crescer como `2^n`, fazendo o custo explodir conforme a entrada aumenta. O exemplo da pizza mostra isso bem: com `n` coberturas existem `2^n` combinações.
- **P:** classe dos problemas que podem ser resolvidos em tempo polinomial.
- **NP:** classe dos problemas cujas soluções podem ser verificadas em tempo polinomial.
- **P ⊆ NP:** todo problema que pode ser resolvido eficientemente também pode ter sua solução verificada eficientemente.
- **P = NP?:** questão em aberto sobre se todo problema cuja solução pode ser verificada eficientemente também pode ser resolvido eficientemente.
- **Complexidade depende do tamanho da entrada:** não basta dizer que um algoritmo é "rápido" ou "lento"; interessa muito mais como o custo cresce quando n aumenta. Um `O(n²)` pode ser tranquilo enquanto um `O(2^n)` rapidamente fica inviável.
- **Difícil ≠ impossível:** o artigo trata bastante da diferença entre não termos encontrado uma solução eficiente e provar que não existe solução eficiente.
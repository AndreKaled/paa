# Prova parcial 1 - PAA
## 1. Sobre a busca sequencial em vetor de tamanho n, assinale a INCORRETA e justifique: 
(a) Melhor caso: O(1). 
(b) Pior caso: O(n). 
(c) Caso médio: O(n). 
**(d) Limite inferior do problema: $\Omega(\log(n))$.**
(e) A versão iterativa usa espaço O(1).

Incorreta é a alternativa **D**.
a) Melhor caso é O(1) pois o elemento está na primeira posição
b) pior caso é O(n) pois o elemento está na ultima posição ou não existe
c) Caso médio O(n) o elemento está em posição aleatória (espera-se $n/2$ comparações)
**d) o limite inferior do problema de busca em um vetor desordenado é $\Omega(n)$, pois qualquer algoritmo precisa no pior caso, inspecionar todos os elementos**
e) A versão iterativa usa espaço O(1), usando apenas algumas variáveis auxiliares

## 2. Sobre o fatorial de n, assinale a INCORRETA e justifique: 
(a) Versão iterativa: tempo O(n), espaço O(1). 
(b) Versão recursiva: tempo O(n), espaço O(n). 
(c) Limite inferior do problema: Ω(n). 
**(d) A versão recursiva é assintoticamente mais rápida que a iterativa.**
(e) Ambas têm MC, CM e PC iguais.

Incorreta é a alternativa **D**
A versão recursiva não é assintoticamente mais rápida, ambas são O(n). Recursão só adiciona custo de chamadas na pilha (constante por chamada), sem mudar a complexidade de tempo.

## 3.(Discursiva) Selecione entre: gerar todas as permutações de uma lista, encontrar o máximo e o mínimo de uma lista de n elementos. Descreva o melhor algoritmo em pseudo-código (recursivo e não recursivo), dê MC e PC (comente sobre CM):
Versão não recursiva:
```c
MaxMinIterativo(A[1..n]):
    max <- A[1]; min <- A[1]
    PARA i DE 2 ATE n FAÇA
        SE A[i] > max ENTAO max <- A[i]
        SE A[i] < min ENTAO min <- A[i]
    RETORNE (max, min)
```

Versão recursiva:
```c
MaxMinRec(A[i..j]):
    SE i = j ENTAO RETORNE (A[i], A[i])
    SE j = i+1 ENTAO
        SE A[i] > A[j] ENTAO RETORNE (A[i], A[j])
        SENAO RETORNE (A[j], A[i])
    meio <- (i + j) / 2
    (maxE, minE) <- MaxMinRec(A[i..meio])
    (maxD, minD) <- MaxMinRec(A[i..meio])
    RETORNE (max(maxE, maxD), min(minE, minD))
```

A versão não recursiva faz $2(n-1)$ comparações, MC = PC = $\theta(n)$
A versão recursiva com 1 comparação no caso base de 2 elementos e as 2 comparações na combinação tem $T(n) = 2T(n/2) +2$, com caso base $T(2) = 1$, que dá 3n/2 -2 comparações, com MC = PC = $\theta(n)$.
Caso médio também é $\theta(n)$ pois qualquer algoritmo precisa verificar cada elemento pelo menos uma vez, então não tem mudança entre os casos.

## 4. Analise o trecho abaixo e assinale a complexidade correta. Justifique:
(a) $O(n^2)$. **(b) $O(n^3)$**. (c) $O(n^4)$. (d) $O(n^3 log n)$ (e)$O(2^n)$.

$$\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^i 1 = \sum_{i=1}^n n*i = n* \frac{n(n+1)}{2} = \frac{n^2(n+1)}{2} = \theta(n^3)$$

## 5. Seja $T(n) = 2T(n/2) + n^2$. Assinale a complexidade correta. Justifique: 
(a) $O(n)$. (b) $O(n \log(n))$. **(c) $O(n^2)$**. (d) $O(n^2 \log(n))$. (e) $O(n^3)$

$$T(n) = 2T(n/2) + n^2$$

$$T(n) = 2[2T(n/2^2) +(\frac{n}{2})^2] + n^2 = 4T(n/4) +(\frac{n}{2})^2 + n^2$$

Após k passos:

$$T(n) = 2^kT(n/2^k) + n^2 \sum_{i=0}^{k-1} (\frac{1}{2})^i$$

Quando $\frac{n}{2^k} = 1$, temos que $k = \log(n)$, substituindo:
$$T(n) = 2^{\log(n)}T(1) +n^2 \sum_{i=0}^{\log(n)-1} (\frac{1}{2})^i = n * T(1) + n^2 \sum_{i=0}^{\log(n)-1} (\frac{1}{2})^i$$

Temos que:
$$\sum_{i=0}^{\log(n)-1} (\frac{1}{2})^i = 2 - \frac{2}{n}$$

Portanto:

$$T(n) = 2^{\log(n)}T(1) +n^2 (2 - \frac{2}{n}) = 2n^2 - 2n +n * T(1)$$

O termo dominante é 2n^2, portanto por analise assintotica é $\theta(n^2)$.

## 6. (Discursiva) Explique o Teorema Mestre e aplique-o para resolver T(n) = 9T(n/3) + n. Determine também a complexidade de T(n) = 3T(n/4) + n log n.


## 7. O valor de $\sum_{i=1}^{n} \frac{1}{i(i+1)}$ é: 
**(a) $\frac{n}{n+1}$** (b) $\frac{n+1}{n}$ (c) $\frac{1}{n}$ (d) $\log(n)$ (e) $n$


Usando frações parciais:

$$\frac{1}{i(i+1)} = \frac{1}{i} - \frac{1}{i+1}$$

Logo a soma é:

$$\sum_{i=1}^{n}\left(\frac{1}{i} - \frac{1}{i+1}\right) = 1 - \frac{1}{2} + \frac{1}{2} - \frac{1}{3} + \cdots + \frac{1}{n} - \frac{1}{n+1} = 1 - \frac{1}{n+1} = \frac{n}{n+1}$$

## 8. Resolva T(n) = T(n − 1) + n, com T(1) = 1. A complexidade é: 
(a) $O(n)$ (b) $O(n \log(n))$ **(c) $O(n^2)$** (d) $O(2^n)$ (e) $O(\log(n))$


Expandindo recorrências:

$$T(n) = T(n-1) + n = T(n-2) + (n-1) + n = \cdots = T(1) + 2 + 3 + \cdots + n = 1 + 2 + \cdots + n = \frac{n(n+1)}{2}$$

Portanto $T(n) = \frac{n(n+1)}{2} = \Theta(n^2)$.

## 9. (Discursiva) Resolva T(n) = 2T(n/2) + n log n usando árvore de recursão e Teorema Mestre. Compare com T(n) = 2T(n/2) + n.

## 10. No problema de Josephus com k = 2 e n = 10, o sobrevivente é: (a) 1 (b) 3 (c) 5 (d) 7 (e) 9

## 11. (Discursiva) Escolha um tópico: (a) Fibonacci e razão áurea; (b) série harmônica e escala musical; (c) números primos e criptografia. Discorra sobre aplicações e aspectos de complexidade computacional.

A criptografia moderna, que protege desde conversas em aplicativos de mensagem até transações bancárias na internet, tem nos números primos um de seus pilares fundamentais. Um número primo é aquele que só é divisível por 1 e por ele mesmo (2, 3, 5, 7, 11, 13...), e apesar dessa definição simples, primos possuem propriedades que os tornam extremamente úteis para construir sistemas seguros.

A segurança desses sistemas se apoia em assimetria computacional: existem operações que são muito fáceis de fazer em um sentido, mas extraordinariamente difíceis de inverter. No caso dos primos, multiplicar dois primos grandes é uma operação simples e rápida para qualquer computador, mas dado apenas o resultado dessa multiplicação, descobrir quais foram os primos originais é um problema que pode levar anos, mesmo para as máquinas mais potentes do mundo.

Imagine que duas pessoas A e B, querem trocar mensagens sem que ninguém mais consiga ler. Elas combinam dois números primos grandes, p e q, e multiplicam, gerando $n = pq$. As mensagens são cifradas usando n, e só podem ser decifradas por quem conhece p e q separadamente, pois a partir deles é possível calcular a chave privada. Agora entra um terceiro T (que pode ser um espião, um governo, um hacker, qualquer um que definitivamente A e B não gostariam que lessem as mensagens), que interceptou as mensagens e conhece n. Para decifrá-las, ela precisa descobrir os primos p e q que originaram n, ou seja ele precisa fatorar n. Como p e q são números primos grandes (centenas de digitos), a complexidade dessa tarefa é enorme, com complexidade que levariam anos para descobrir n, isso considerando os computadores comuns modernos (acessíveis ao público geral), enquanto A e B conversam tranquilamente, T simplesmente não tem poder computacional suficiente para quebrar a proteção, pois a tarefa de descobrir o primo é difícil demais para as máquinas disponíveis.

A diferença entre a facilidade de multiplicar e a dificuldade de fatorar está na ordem de complexidade, a multiplicação de dois números de tamanho log n é polinomial, enquanto a fatoração é subexponencial, muito além de qualquer polinônio prático para entradas grandes. Curiosamente, testar se um número é primo é fácil, então gerar chaves é rápido. Portanto é fácil gerar um segredo e fácil de usar praticamente, mas extremamente difícil de descobrir sem a informação secreta, e é nessa lacuna de complexidade que garante a privacidade da comunicação digital atualmente.
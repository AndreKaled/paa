# Versão Interativa

Hanoi Interativo
```
A = [N, N-1, ..., 1]
B = []
C = []
MOVIMENTOS = 0
PILHA = []

// função pra mover o disco do topo de origem para destino
função Mover(origem, destino):
    se origem está vazio então
        Erro: "Origem sem disco"
    fim se

    disco = topo(origem)

    // só pode mover se o destino estiver vazio ou
    // se o disco do topo do destino for maior que o disco a mover
    se destino não vazio E topo(destino) < disco então
        Erro: "Mmvimento inválido: disco maior sobre menor"
    fim se

    desempilhar(origem)          // remove o topo da origem
    empilhar(destino, disco)     // coloca no destino
    MOVIMENTOS = MOVIMENTOS + 1
fim função

// empilha o problema inicial
empilhar(PILHA, (N, A, B, C))

enquanto PILHA não vazia faça
    // tira o último subproblema empilhado
    (qtd, origem, auxiliar, destino) = desempilhar(PILHA)

    se qtd == 1 então
        // subproblema de tamanho 1 executa o movimento
        Mover(origem, destino)
    senão
        // quebra o problema em 3 partes, empilhando na ordem inversa
        // para que a primeira a ser executada seja a última a entrar.

        // mover qtd-1 do auxiliar -> destino
        empilhar(PILHA, (qtd-1, auxiliar, origem, destino))

        // mover o disco maior da origem -> destino
        empilhar(PILHA, (1, origem, auxiliar, destino))

        // mover qtd-1 da origem -> auxiliar
        empilhar(PILHA, (qtd-1, origem, destino, auxiliar))
    fim se
fim enquanto

```
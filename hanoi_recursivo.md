# Versão Recursiva

Hanoi Recursivo
```
// inicia os pinos como vetores
A = [N, N-1, ..., 1]   // exemplo: N=3 -> A = [3, 2, 1]
B = []                 // vazio
C = []                 // vazio

// contador p movimentos
MOVIMENTOS = 0

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

função HanoiRec(qtd, origem, auxiliar, destino):
    se qtd == 1 então
        // caso base
        Mover(origem, destino)
    senão
        // move os qtd-1 discos de cima da origem para o auxiliar
        HanoiRec(qtd-1, origem, destino, auxiliar)
        
        // move o disco maior (qnt, que ficou na base) da origem para o destino
        mover(origem, destino)
        
        // move os qtd-1 discos do auxiliar para o destino
        HanoiRec(qtd-1, auxiliar, origem, destino)
    fim se
fim função

// Chamada inicial:
// HanoiRec(N, A, B, C)
```
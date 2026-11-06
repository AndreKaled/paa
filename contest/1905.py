#problem: https://judge.beecrowd.com/pt/problems/view/1905
from collections import deque

def aaa():
    matriz = []
    # le matriz 5x5
    while len(matriz) < 5:
        linha = input().split()
        if linha:
            matriz.append([int(x) for x in linha])
            
    # se inicio ou fim tiver bloqueado
    # os policiais ja perderam
    if matriz[0][0] == 1 or matriz[4][4]==1:
        return "ROBBERS"
        
    # fila pra BFS
    fila = deque([(0, 0)])
    visitado = [[False] * 5 for _ in range(5)]
    visitado[0][0] = True
    
    # baixo, cima, direita e esquerda
    direcoes = [(1,0),(-1,0),(0,1),(0,-1)]
    
    while fila:
        l, c = fila.popleft()
        
        if l == 4 and c == 4:
            return "COPS"
            
        for dl, dc in direcoes:
            nl, nc = l + dl, c + dc
            
            if 0 <= nl < 5 and 0 <= nc < 5 and matriz[nl][nc] == 0 and not visitado[nl][nc]:
                visitado[nl][nc] = True
                fila.append((nl,nc))
                
    return "ROBBERS"
    
t = int(input())
for _ in range(t):
    result = aaa()
    print(result)
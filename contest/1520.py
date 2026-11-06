#problem: https://judge.beecrowd.com/pt/problems/view/1520
import sys

# le tudo de uma vez
linhas = sys.stdin.read().splitlines()

ponteiro = 0
totallinhas = len(linhas)

while ponteiro < totallinhas:
    if not linhas[ponteiro].strip():
        ponteiro +=1
        continue
    n = int(linhas[ponteiro])
    ponteiro += 1
    
    produtos = []
    
    for _ in range(n):
        x, y = map(int, linhas[ponteiro].split())
        ponteiro += 1
        
        # add parafuso em [x, y]
        produtos.extend(range(x, y+1))
        
    produtos.sort()
    
    # numero da pesquisa
    num = int(linhas[ponteiro])
    ponteiro +=1
    
    if num in produtos:
        inicio = produtos.index(num)
        fim = inicio + produtos.count(num) -1
        print(f"{num} found from {inicio} to {fim}")
    else:
        print(f"{num} not found")
        
        
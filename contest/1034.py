# nao passou
# problem: https://judge.beecrowd.com/pt/problems/view/1034

n = int(input())

resultados = []
for c in range(n):
    elementos = input().split()
    objetivo = int(elementos[1])

    blocos = input().split()
    blocos = map(int, blocos)
    blocos = list(blocos)
    blocos.sort(reverse=True)

    i = 0
    resultado = 0 
    while objetivo:
        while(blocos[i] > objetivo):
            i += 1
        resultado += objetivo // blocos[i]
        objetivo = objetivo % blocos[i]
    resultados.append(resultado)


for res in resultados:
    print(res)

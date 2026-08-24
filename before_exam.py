d, somaTempo = map(int, input().split())
agenda = []
maximos = []
minTotal = 0
maxTotal =0
for _ in range(d):
    mn,mx = map(int, input().split())
    agenda.append(mn)
    maximos.append(mx)
    minTotal+= mn
    maxTotal+= mx
if somaTempo < minTotal or somaTempo > maxTotal:
    print("NO")
else:
    resto = somaTempo - minTotal
    for i in range(d):
        add = min(resto, maximos[i] - agenda[i])
        agenda[i] += add
        resto -= add
    print("YES")
    print(*agenda)
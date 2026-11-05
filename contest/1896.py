#problem: https://judge.beecrowd.com/pt/problems/view/1896
# pegando os primeiros elementos
pl = input().split()
cartas = []

# pegandos as cartas
for _ in range(int(pl[0])):
    cartas.append(input().split()) 

# parte de fazer analise se é possivel fazer analise

cartas_i = [[], [], []]

for c in range(3):

    for carta in cartas:
        cartas_i[c].append(carta[c])


certo = True
for e in range(3):
    objetivo = int(pl[e+1])

    cartas_atual = map(int, cartas_i[e])

    cartas_atual = list(cartas_atual)
    cartas_atual.sort(reverse=True)

    acumulador = objetivo
    contador = 0 
    for i in cartas_atual:
        contador += 1
        if ((acumulador - int(i))<0):
            break
        elif ((acumulador - int(i))==0 and contador > 1):
            acumulador = acumulador - int(i)

            break

        elif ((acumulador - int(i))==0 and contador < 2):
            continue

        acumulador = acumulador - int(i)


    if(acumulador):
        certo = False
        print("N")
        break

if certo:
    print("Y")
       

n, k, t = map(int,input().split())

total = n*k*t //100
resto = total % k
cont = total // k
resp = []
while cont:
    cont-=1
    resp.append(f"{k}")

if(len(resp) < n):
    resp.append(f"{resto}")

while len(resp) < n:
    resp.append("0")

print(" ".join(resp))

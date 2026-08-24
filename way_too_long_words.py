n = int(input())
resp = []
while n:
    x = input()
    if(len(x)-1 < 10):
        resp.append(x)
    else:
        resp.append(f"{x[0]}{len(x)-2}{x[-1]}")
    n -= 1

for r in resp:
    print(r)
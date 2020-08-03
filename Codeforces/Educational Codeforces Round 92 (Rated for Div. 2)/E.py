import sys

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

t = int(sys.stdin.readline())
i = 0
while i < t:
    i = i + 1
    m, d, w = map(int, sys.stdin.readline().split())
    
    w = w // gcd(d - 1, w)
    mi = min(m, d)
    x = mi // w
    ans = (2 * (mi - w) - w * (x - 1)) * x // 2
    print(ans)
    
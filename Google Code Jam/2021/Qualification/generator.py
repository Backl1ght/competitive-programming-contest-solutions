import numpy as np

n = 100
m = 10000
T = 50  # 50
P = 86

f = open('a.in', 'w')


def sigmoid(x):
    return 1. / (1. + np.exp(-x))


def genCase(case):
    cheater = np.random.randint(0, n)
    Q = np.random.uniform(-3., 3., (m, ))
    # print(Q)
    # print(np.min(Q), np.max(Q))
    S = np.random.uniform(-3., 3., (n, ))
    # print(S)
    # print(np.min(S), np.max(S))
    for i in range(n):
        res = []
        if i == cheater:
            for j in range(m):
                x = np.random.uniform(0, 1)
                if x < 0.5:
                    res.append(1)
                else:
                    p = sigmoid(S[i] - Q[j])
                    x = np.random.uniform(0, 1.)
                    if x < p:
                        res.append(1)
                    else:
                        res.append(0)
        else:
            for j in range(m):
                p = sigmoid(S[i] - Q[j])
                x = np.random.uniform(0, 1.)
                if x < p:
                    res.append(1)
                else:
                    res.append(0)
        res = ['0' if ch == 0 else '1' for ch in res]
        res = ''.join(res)
        f.write(f'{res}\n')
    f.write(f'{cheater + 1}\n')


def main():
    f.write(f'{T}\n')
    f.write(f'{P}\n')
    for i in range(T):
        genCase(i)


if __name__ == '__main__':
    main()
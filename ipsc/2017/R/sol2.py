import numpy as np

def gcd(a, b):
    while b > 0:
        a, b = b, a % b
    return a


def solve(n, c, k):
    a = [1.]

    for i in range(2, n + 1):
        a = [0.] + a

        for j in range(i):
            a[j] *= (i - 1) / c

        b = [0.] * i
        p = -(1. - (i - 1) / c)
        det = 1. - (-p)**( i // gcd(i,k) )

        if k % i == 0:
            for j in range(i):
                b[j] = a[j] / (1. + p)
        else:
            for j in range(i):
                pos = j
                x = 1. / det

                while True:
                    b[j] += x * a[pos]
                    x *= -p

                    pos = ((pos - k) % i + i) % i

                    if pos == j:
                        break

        a = b
        # print(a)

    best = -1
    value = 0

    for j in range(n):
        if a[j] > value:
            value, best = a[j], j

    print(best, round(value,12))
    

def test():
    solve(4, 5, 2)

def main():
    t = int( input() )

    for i in range(t):
        input()
        n, c, k = map(int, input().split())
        #print("tc", i + 1, end=" ")
        solve(n, c, k)

if __name__ == '__main__':
    main()

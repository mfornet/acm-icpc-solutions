from euler import *
from pprint import pprint
import time

from fractions import Fraction

import numpy as np

num = Fraction
I = 1
II = 2

size = None
adj = None
dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]


def prec(n):
    global size, adj
    size = [[0] * n for i in range(n)]
    adj = [[[] for j in range(n)] for i in range(n)]

    for i in range(n):
        for j in range(n):
            for k in range(4):
                x = i + dx[k]
                y = j + dy[k]

                if 0 <= x < n and 0 <= y < n:
                    adj[i][j].append((x,y))
                    size[i][j] += 1

def build_I(n, A):
    for i in range(n):
        for j in range(n):
            pos = i * n + j
            A[pos][pos] = num(1) / num(size[i][j] + 1) - num(1)

            for x, y in adj[i][j]:
                tpos = x * n + y
                A[pos][tpos] = num(1) / num(size[x][y] + 1)


def build_II(n, A):
    for i in range(n):
        for j in range(n):
            pos = i * n + j
            A[pos][pos] = num(1) / num(2) - num(1)

            for x, y in adj[i][j]:
                tpos = x * n + y
                A[pos][tpos] = num(1) / num(2) / num(size[x][y])


def cancel(a, b, col):
    assert(col in b)
    assert(b[col] != num(0))

    fak = -a.get(col, num(0)) / b[col]
    if fak == num(0): return
    for p in b:
        a[p] = a.get(p, num(0)) + fak * b[p]


def solve(N):
    prec(N)
    answer = 0

    for mode in (I, II):
        A = [{} for i in range(N * N)]
        build_I(N, A) if mode == I else build_II(N, A)

        for i in range(N * N):
            A[N - 1][i] = 1

        for r in range(N):
            for piv in range(N, N * N + r):
                cancel(A[r], A[piv % (N * N)], piv - N)

        X = [num(0)] * (N * N)
        X[-1] = num(1)

        r = N - 1
        for i in range(N * N - 1, -1, -1):
            for p in A[r]:
                if p > i:
                    X[i] -= X[p] * A[r][p]
            X[i] /= A[r][i]
            r = r - 1 if r > 0 else N * N - 1

        curvalue = 0

        # for i in range(N * N):
        #     print(X[i], end = " ")
        #     if (i + 1) % N == 0: print()
        # print()
        # print(float(X[0]), float(X[1]), float(X[N + 1]))

        for i in range(1, N + 1):
            curvalue += X[i * i - 1]

        answer += curvalue

    return answer / 2


def best(n):
    answer = 0

    m = [ [-2/3, 1/2, 0],
          [0, -1/4, 1/5],
          [4, 4 * (n - 2), (n-2)**2]
        ]
    x = np.linalg.solve(m, [0, 0, 1])
    # print(x)

    for i in range(1, n + 1):
        v = i * i - 1
        px = v % n
        py = v // n

        a = px == 0 or px == n - 1
        b = py == 0 or py == n - 1

        if a and b:
            answer += x[0]
        elif a or b:
            answer += x[1]
        else:
            answer += x[2]

    m = [ [-1/2, 1/3, 0],
          [0, -1/6, 1/8],
          [4, 4 * (n - 2), (n-2)**2]
        ]

    x = np.linalg.solve(m, [0, 0, 1])
    # print(x)

    for i in range(1, n + 1):
        v = i * i - 1
        px = v % n
        py = v // n

        a = px == 0 or px == n - 1
        b = py == 0 or py == n - 1

        if a and b:
            answer += x[0]
        elif a or b:
            answer += x[1]
        else:
            answer += x[2]

    return answer / 2


def solution(n=1000):
    value2 = best(n)
    return str(round(value2, 12))


def test():
    pass
    for i in range(5, 20):
        print(round(float(solve(i)), 12), round(best(i), 12))


def main():
    sol_start = time.time()
    answer = solution()
    sol_end = time.time()

    print("=======================")
    print("solution:", answer)
    print("time:", round(sol_end - sol_start, 5))
    print("=======================")


if __name__ == '__main__':
    # test()
    main()
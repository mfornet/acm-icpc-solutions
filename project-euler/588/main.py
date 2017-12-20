from euler import *
from scipy import *
import numpy as np
import time


"""
P^8 = x^8 * P
P^(k) = P^(8 * q + r) = P
P^80 = P^10
P^10 = P^(8+2) = P^8 * P^2

P(x)^8 = P(x^8)

P(x)^(8 * q + r) = P(x)^r * P(x^8)^q

P(x^t)^8 = P

P = (x^5 - 1) / (x - 1)
"""

class SparseBase2Polinomia:
    def __init__(self, P=[]):
        self.coef = set()
        for i in range(len(P)):
            if P[i] == 1:
                self.coef.add(i)


    def __mul__(self, P):
        coef = set()
        for x in self.coef:
            for y in P.coef:
                v = x + y
                if v in coef:
                    coef.remove(v)
                else:
                    coef.add(v)
        ans = SparseBase2Polinomia()
        ans.coef = coef
        return ans


    def size(self):
        return len(self.coef)


def solve(n):
    while n % 8 == 0:
        n //= 8
    a = SparseBase2Polinomia([1])
    b = SparseBase2Polinomia([1,1,1,1,1])
    while n:
        if n & 1:
            a = a * b
        n >>= 1
        b = b * b
        # print(b.size())
    return a.size()


def solution():
    for i in range(1, 19):
        print(i, solve(10**i))
    return 0

    # print(get(8))
    # print(polymul(pw(8), P))
    # prec()

    # Really cool (and fast) code here...
    k = 30
    p = [1, 1, 1, 1, 1]
    a = [1]

    pol = SparseBase2Polinomia(p)
    pola = SparseBase2Polinomia([1])

    for i in range(k):
        a = polymul(a, p)
        pola = pola * pol

        for j in range(len(a)):
            a[j] = a[j] % 2

        if (i+1) % 8 == 0:
            # print(i+1,end=" ")
            # for x in a:
            #     print(x,end="")
            # print()

            # last = 0
            # for j in range(1, len(a)):
            #     if a[j] == 1:
            #         print(j - last, end = " ")
            #         last = j
            # print()
            # print(i + 1, sum(a), sum(solve(i+1)))
            pass

        print(i+1, sum(a), pola.size(), solve(i+1))

        # print(list(a))
        # print(i+1, sum(a))


def test():
    for k in range(3, 19):
        a = 10**k
        v = a // 8 * 8
        print(a, v)


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
from euler import *
from fractions import Fraction as num
from itertools import permutations
from math import factorial
import time


"""
2 [0, 1, 1]
3 [0, 1, 2, 3]
4 [0, 1, 3, 9, 11]
5 [0, 1, 4, 18, 44, 53]
6 [0, 1, 5, 30, 110, 265, 309]
7 [0, 1, 6, 45, 220, 795, 1854, 2119]
8 [0, 1, 7, 63, 385, 1855, 6489, 14833, 16687]
9 [0, 1, 8, 84, 616, 3710, 17304, 59332, 133496, 148329]
10 [0, 1, 9, 108, 924, 6678, 38934, 177996, 600732, 1334961, 1468457]

"""


def solution():
    N = 52

    # Really cool (and fast) code here...
    E = [num(0)] * (N + 1)
    S = [num(0)] * (N + 1)
    magic = [num(1)] * (N + 1)

    for i in range(2, N + 1):
        k = num()

        # freq = [0] * (i + 1)

        # for p in permutations(range(i)):
        #     t = i
        #     for j in range(1,len(p)):
        #         if p[j] == p[j-1]+1:
        #             t -= 1
        #     freq[t] += 1

        fak = num(factorial(i))
        # print(i, freq, sum(freq), fak)

        _freq = [0] * (i + 1)
        for j in range(1, i):
            _freq[j] = magic[j] * comb(i - 1, i - j)
        magic[i] = fak - sum(_freq)
        _freq[i] = magic[i]

        a, b = fak, fak - _freq[i]
        for j in range(1, i):
            a += _freq[j] * S[j]

        S[i] = a / b
        print(i, float(S[i] - 1))
        # E[i] = S[i] - 1
        # print(i, S[i], E[i])

    return str(round(float(S[N]-1),16))


def test():
    for n in range(2, 7):
        for i in range(n+1):
            print(comb(n-1,n - i), end=" ")
        print()


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
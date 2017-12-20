from euler import *
from itertools import repeat, product
import time


def mega_brute(n):
    answer = 0
    for a, b, c, d, e, f in product(*repeat(range(1,n-4), 6)):
        if a + b + c + d + e + f > n: continue
        if d - a != b - e: continue
        if d - a != f - c: continue
        # print(a, b, c, d, e, f)
        answer += 1
    return answer


def brute(n):
    answer = 0
    for a in range(1, n+1):
        for c in range(a, n-a+1):
            for e in range(c, n-a-c+1):
                value = max(0, (n-2*(a+c+e))//3 + min(a, c, e))

                if value > 0:
                    answer += value
                    print(a + c + e, min(a, c, e), value, "::", a, c, e)

    return answer


def solution(n):
    # Really cool (and fast) code here...
    answer = 0
    for s in range(3, n - 2):
        c = (n - 2 * s) // 3

        if s % 3 == 0:
            B = s // 3
            answer += s // 3
        else:
            B = s // 3 + 1

        f1 = lambda x : (x + 1) * x // 2
        f2 = lambda x : (2 * x + 1) * (x + 1) * x // 6

        A = max(1, 1 - c)

        answer += 3 * ( s * c * (B - A) + (s - 3 * c) * (f1(B - 1) - f1(A-1))
                        -3 * (f2(B - 1) - f2(A-1)))

    return answer


def test():
    for i in range(6, 13):
        print(i, brute(i))
    # check_equal(solution, brute, ((i,) for i in range(500)))
    # value = brute(12)
    # print(value)
    # value = solution(12)
    # print(value)


def main():
    sol_start = time.time()
    answer = solution(100)
    sol_end = time.time()

    print("=======================")
    print("solution:", answer)
    print("time:", round(sol_end - sol_start, 5))
    print("=======================")


if __name__ == '__main__':
    test()
    # main()
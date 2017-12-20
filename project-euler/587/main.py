from euler import *
import numpy as np
from scipy.integrate import simps
import time


def get_area(n):
    x0 = (1 + 1 / n - (2 / n)**.5) / (1 + 1 / n / n)
    area_1 = x0**2 / 2 / n

    x_r = np.linspace(x0, 1, 10000)
    y_r = (lambda x : 1 - (1 - (x - 1)**2)**.5)(x_r)

    area_2 = simps(y_r, x_r)

    return area_1 + area_2


def solution(ratio=0.001):
    # Really cool (and fast) code here...

    t_area = 1 - np.pi / 4
    lo, hi = 1, 1

    while get_area(hi) / t_area > ratio:
        hi *= 2

    while lo + 1 < hi:
        mid = (lo + hi) >> 1
        if get_area(mid) / t_area < ratio:
            hi = mid
        else:
            lo = mid

    return hi


def test():
    for i in range(1, 10):
        print(get_area(i))


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
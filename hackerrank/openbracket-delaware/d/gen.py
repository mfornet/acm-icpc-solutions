import random
import sys


def gen(n, m):
    print(n, m)
    for i in range(n):
        for j in range(m):
            print(random.randint(1, 10**7), end=" ")
        print()


if __name__ == '__main__':
    n, m = map(int, sys.argv[1:])
    gen(n, m)
from random import *


def generate(N, Q, M=100):
    print(N, Q)

    for i in range(N):
        print(randint(1, M), end=" ")
    print()

    for i in range(Q):
        print(randint(1, M), randint(1, M))


def main():
    generate(8000, 10**5, 1000)
    # generate(100, 100, 100)


if __name__ == '__main__':
    main()

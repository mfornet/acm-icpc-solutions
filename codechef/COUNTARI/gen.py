import random

MAX = 30000

def gen(N):
    print(N)
    for i in range(N):
        print(random.randint(1, MAX), end=" ")
    print()


def main():
    gen(100000)


if __name__ == '__main__':
    main()

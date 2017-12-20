import random

def generate(N, M):
    print(N)
    for i in range(2, N + 1):
        print(i, random.randint(1, i - 1))

    for i in range(N):
        print(random.randint(0, M))


def main():
    generate(1000,1000)


if __name__ == '__main__':
    main()
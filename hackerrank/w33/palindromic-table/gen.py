import random

NM = 10**5
SQRTNM = int(NM**.5)

# N = random.randint(int(SQRTNM / 2), min(NM, 2 * SQRTNM))
N = random.randint(1, NM)
M = NM // N


def gen():
    global N, M
    if random.randint(0, 1) == 1:
        N, M = M, N

    print(N, M)
    for i in range(N):
        for j in range(M):
            print(random.randint(0, 9), end=" ")
        print()


def main():
    gen()


if __name__ == '__main__':
    main()

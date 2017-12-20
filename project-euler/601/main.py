from euler import *


def streak(n):
    i = 1
    while (n - 1) % i == 0:
        i += 1
    return i - 1


def P(s, N):
    v = 1
    for i in range(2, s + 1):
        v = lcm(v, i)
    k = lcm(v, s + 1)
    N -= 2

    return N // v - N // k 


def C(s, N):
    answer = 0
    for i in range(2, N):
        answer += int(streak(i) == s)
    return answer
    

def test():
    for s in range(1, 7):
        for i in range(2, 200):
            if C(s, i) != P(s, i):
                print("bad: ", s, i)

    for i in range(2, 200):
        print(i, streak(i))

    print(P(3, 14))
    print(P(6, 10**6))


def solution():
    answer = 0
    for i in range(1, 32):
        answer += P(i, 4**i)
    print(answer)


def main():
    #test()

    print("solution")
    solution()

    pass

if __name__ == '__main__':
    main()

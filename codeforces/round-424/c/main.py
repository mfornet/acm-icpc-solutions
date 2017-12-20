import random

def gen(n):
    print(n, random.randint(1, 10**9))
    for i in range(n):
        print(10**9 - 10**6 * i, end = " ")
    # for i in range(n):
    #     print( random.randint(1, 10**9), end = " " )
    print()


gen(100)

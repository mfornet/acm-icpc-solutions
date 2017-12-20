import random

def g(n):
    print(n)
    for i in range(n):
        print(random.randint(1, 2), end = " ")
    print()


g(20)

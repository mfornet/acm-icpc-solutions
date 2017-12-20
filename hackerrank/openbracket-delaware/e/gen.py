import random
import sys

def gen(n):
    assert(n%2 == 0)

    print(n)

    for i in range(2, n+1):
        print(i-1, end=" ")
        # print(random.randint(1,i-1), end=" ")
    print()

    A = list(range(1, n //2 +1))
    A += A
    random.shuffle(A)
    print(' '.join(str(x) for x in A))


gen(int(sys.argv[1]))

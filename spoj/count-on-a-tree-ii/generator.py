import random
import sys


n = int(sys.argv[1])
q = int(sys.argv[2])
m = int(sys.argv[3])

def generate():
    print(n, q)
    print(' '.join(str(random.randint(1, m)) for i in range(n)))
    for i in range(2, n+1):
        print(random.randint(1, i - 1), i)

    for i in range(q):
        print(random.randint(1,n), random.randint(1,n))

if __name__ == '__main__':
    generate()

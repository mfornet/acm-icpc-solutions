import random
import sys


class TestCase:
    def __init__(self, n, q, seed=None):
        self.n = n
        self.q = q
        self.rnd = random.Random( seed )


    def r2010(self):
        value = self.rnd.randint(0, 2009)
        if value <= 10:
            value = 1
        return value


    def generate(self):
        n, q = self.n, self.q
        print(n)

        for i in range(n):
            print( self.r2010(), end = " ")

        print()
        print(q)

        for i in range(q):
            m = self.rnd.randint(1, 2)
            u = self.rnd.randint(1, n)
            v = self.rnd.randint(1, n)
            if u > v:
                u, v = v, u
            print(m, u, v)


def main():
    n, q = int(sys.argv[1]), int(sys.argv[2])
    tc = TestCase(n, q)
    tc.generate()

if __name__ == '__main__':
    main()


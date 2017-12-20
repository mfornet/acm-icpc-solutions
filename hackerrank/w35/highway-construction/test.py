from math import factorial as f


def memoize(func):
    memo = {}

    def g(*args):
        if not args in memo:
            memo[args] = func(*args)
        return memo[args]

    return g

@memoize
def comb(n, k):
    return f(n) // f(k) // f(n-k)


@memoize
def s(a, n):
    return ((n+1)**(a+1)-1)//(a+1) - sum(comb(a+1,r) * s(r,n) for r in range(a)) // (a+1)


def brute(a,n):
    return sum(k**a for k in range(1,n+1))


for i in range(50):
    for j in range(50):
        # print(i,j, s(i,j), brute(i,j))
        assert(s(i,j) == brute(i,j))

def r(a):
    return [1 - x for x in a]


def f(n):
    if n == 1:
        return [0]
    a = f(n - 1)
    return a + r(a)

def h(a, p, m=2**32):
    v = 0
    for x in a:
        v = (v * p + x) % m
    return v


for i in range(1, 30):
    print(i, h(f(i), 17))

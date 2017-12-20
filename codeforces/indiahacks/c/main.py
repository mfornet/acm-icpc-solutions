def memoize(func):
    memo = {}
    def g(*args):
        if not args in memo:
            memo[args] = func(*args)
        return memo[args]
    return g

@memoize
def solve(a, b):
    if a == 0 and b == 0: return False
    if a == 0 or b == 0: return True


    for i in range(1, max(a,b)+ 1):
        x = a - i
        y = b - i
        if x < 0: x = a
        if y < 0: y = b
        if not solve(x, y):
            return True

    return False


for i in range(100):
    for j in range(100):
        if not solve(i,j):
            print(i, j, solve(i, j))


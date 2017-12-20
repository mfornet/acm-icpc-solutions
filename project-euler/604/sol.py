def f(n):
    beg = 2
    answer = 0
    total = 0

    while beg + 1 + total <= n:
        total += beg + 1
        beg += 1
        answer += 2

    return answer

L = [1, 3, 9, 11, 100, 50000]

for x in L:
    print(x, f(x))

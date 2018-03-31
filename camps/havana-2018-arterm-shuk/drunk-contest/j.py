import itertools

n = int(input())

s = [input() for _ in range(n)]

best = None

for x in itertools.permutations("abcdefghij"):
    value = 0

    t = s[:]

    for idx, c in enumerate(x):
        for i in range(len(t)):
            t[i] = t[i].replace(c, str(idx))

    for num in t:
        value += int(num)

    if best is None or value < best:
        best = value

print(best)
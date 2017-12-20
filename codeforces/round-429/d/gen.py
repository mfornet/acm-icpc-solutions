import random

n = 3*10**5
q = 3*10**5
# n = 5
# q = 5

print(n, q)

for i in range(n):
    print(random.randint(1, n), end = " ")

for i in range(q):
    u = random.randint(1, n)
    v = random.randint(1, n)
    k = random.randint(1, 5)
    if u > v: u, v = v, u
    print(u, v, k)

import random

MAXVALUE = 5

def gen(n, q):
    adj = [[] for i in range(n)]
    value = [random.randint(1, MAXVALUE) for i in range(n)]

    for i in range(n - 1):
        u, v = i, random.randint(i + 1, n - 1)
        adj[u].append(v)
        adj[v].append(u)

    query = []

    def gettotal(u, v):
        return 2
        def dfs(s, p):
            if s == v:
                return {value[s]}

            for x in adj[s]:
                if x == p:
                    continue

                cur = dfs(x, s)

                if cur is False:
                    continue
                cur.add(value[s])
                return cur

            return False

        return len(dfs(u, u))

    for i in range(q):
        u, v = random.randint(0, n - 1), random.randint(0, n - 1)
        total = gettotal(u, v)
        query.append((u, v, random.randint(1, total)))

    print(n, q)
    print(' '.join(map(str, value)))

    for i in range(n):
        for u in adj[i]:
            if i < u:
                print(i + 1, u + 1)

    for u, v, k in query:
        print(u + 1, v + 1, k)


def main():
    gen(50000, 50000)


if __name__ == '__main__':
    main()

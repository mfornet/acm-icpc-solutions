# def memoize(f):
#     S = {}
#     def g(*args):
#         if not args in S:
#             S[args] = f(*args)
#         return S[args]
#     return g
import itertools


def go(value, seen):
    for i in range(len(value) - 1):
        if value[i] > 0 and value[i + 1] > 0:
            nvalue = value[:]
            if i + 2 == len(value):
                nvalue.append(0)
            nvalue[i] -= 1
            nvalue[i + 1] -= 1
            nvalue[i + 2] += 1
            if tuple(nvalue) in seen:
                continue

            seen.add(tuple(nvalue))
            go(nvalue, seen)

def main(ini):
    # ini = [2, 2]
    seen = {tuple(ini)}
    go(ini, seen)
    return len(seen)


if __name__ == '__main__':
    t = int(input())
    for i in range(t):
        input()
        ini = list(int(x) for x in input().split())
        print(main(ini))
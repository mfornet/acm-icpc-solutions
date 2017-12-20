

import random
import sys
import io


SEED = 'educational-round-27'
GOOD = [24887, 321933]


def go(arr, shuffle=True, no=False, rnd=None):
    test_case = io.StringIO()
    assert(len(arr) % 2 == 0)
    n = len(arr) // 2

    if no:
        arr.sort()
        arr[n] = arr[n - 1]

    if shuffle:
        rnd.shuffle(arr)

    print(n, file=test_case)
    print(' '.join(map(str, arr)), file=test_case)
    return test_case.getvalue()


def generate(num):
    rnd = random.Random(SEED)

    if num == 0:
        return go([1, 2, 3, 4], shuffle=False)
    elif num == 1:
        return go([999] * 101 + [1000] * 99, rnd=rnd)
    elif num == 2:
        return go(list(range(1, 201)), rnd=rnd)
    elif num == 3:
        return go(list(range(1, 201)), no=True, rnd=rnd)
    elif num == 4:
        return go([2, 1, 1, 2], shuffle=False)
    elif num == 5:
        return go([999] * 100 + [1000] * 100, rnd=rnd)
    elif num == 6:
        return go([1, 2, 2, 1], shuffle=False)

    rnd = random.Random(rnd.randint(1, 10**9) * num)

    n = rnd.randint(97, 100)
    arr = [rnd.randint(1, 1000) for x in range(2 * n)]
    no = bool(rnd.randint(0, 1))
    return go(arr, no=no, rnd=rnd)


def main():
    num = int(sys.argv[1])
    print(generate(num))


if __name__ == '__main__':
    main()

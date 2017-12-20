

def solve():
    input()
    n = int( input() )

    l = list( map(int, input().split() ) )
    l = [1] + l

    answer = 0
    acc = 1

    for x in l:
        acc *= x
        answer += acc

    answer = 1
    print(answer)


def main():
    t = int( input() )

    for i in range(t):
        solve()


if __name__ == '__main__':
    main()

mod = 2010

def main():
    l = set()
    for i in range(1, mod):
        s = {}
        n = i
        idx = 0

        while not n in s:
            print(n, end = " ")
            s[ n ] = idx
            idx += 1
            n = n * n % mod

        print(n, "size:", idx - s[n])
        l.add( idx - s[n] )

    print(l)

if __name__ == '__main__':
    main()

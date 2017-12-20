def p(n, k):
    m = [["0"] * n for i in range(n)]

    for i in range(n):
        m[i][i] = "1"
        m[i][((i - k)%n+n)%n] = "p"

    print("inverse {", end=" ")
    for r in range(n):
        print("{",end="")
        for v in range(n):
            print(m[r][v], end="")
            if v + 1 == n: print("}",end="")
            else: print(",",end="")
        if r + 1 == n: print(" }", end="")
        else: print(", ", end="")

p(6, 2)

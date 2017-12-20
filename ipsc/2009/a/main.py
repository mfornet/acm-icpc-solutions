n = int( input() )

for i in range(n):
    input()
    s = input()
    s = s.replace("=", "")
    s = s.replace("+", ")+")
    s = s.replace("*", ")*")
    s = s.replace("-", ")-")
    s = s.replace("/", ")/")
    s = "(" * s.count(")") + s
    print(s)

    print( eval(s) )
    exit(0)

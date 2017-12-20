import random

def g(n):
    print(n)
    print(1, end = " ")
    for i in range(2, n + 1):
        if i % 2 == 0:
            print("-", end = " ")
        else:
            print("+", end = " ")
        print(i, end = " ")

    print()

# g(30)

def p():
    n = 30
    print(n)
    print("0 - 0", end = " ")
    for i in range(n - 2):
        print(" - %d"%(100 - i), end = "")
    print()


def k():
    n = 30
    print(30)
    print("0 - 0", end ="")
    for i in range(n - 2):
        print(" - %d"%random.randint(1, 100), end="")
    print()
    

def main():
    k()

if __name__ == '__main__':
    main()

import random
import os

def run(T):
    with open('input.in', 'w') as f:
        f.write(T)

    os.system('./prog < input.in > sol.out')
    os.system('./oth < input.in > oth.out')

    value = os.system('diff sol.out oth.out')

    return value != 0


def main():
    os.system("g++ -std=c++11 oth.cpp -o oth")
    A = [24887, 321933] + random.sample(range(10**6), 1000)
    for i in A:
        print(i)
        value = "%0.6d"%i
        if run(value):
            print("FAIL: ", value)
            exit(0)
    print("GOOD :'(")

if __name__ == '__main__':
    main()

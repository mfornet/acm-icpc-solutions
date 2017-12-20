import random
import sys


SEED = 'educational-round-27'


def generate(num):
    if num == 0: return print('000000')
    elif num == 1: return print('123456')

    rnd = random.Random(SEED)
    TEST = GOOD + rnd.sample(range(10**6), 1000)
    print("%0.6d"%TEST[num])


def main():
    num = int(sys.argv[1])
    print(generate(num))


if __name__ == '__main__':
    main()

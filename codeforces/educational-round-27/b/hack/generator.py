import random
import sys


SEED = 'educational-round-27'
GOOD = [0, 0, 24887, 321933, 887024, 933321]


def generate(num):
    if num == 0: return print('000000')
    elif num == 1: return print('123456')

    rnd = random.Random(SEED)
    TEST = GOOD + rnd.sample(range(10**6), 1000)
    print("%0.6d"%TEST[num])


def main():
    num = int(sys.argv[1])
    generate(num)


if __name__ == '__main__':
    main()

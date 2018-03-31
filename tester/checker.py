import sys


def equal(inp, brute, target):
    with open(brute) as f:
        brute_data = f.read()

    with open(target) as f:
        target_data = f.read()

    if brute_data != target_data:
        exit(1)


def main():
    _, inp, brute, target = sys.argv
    equal(inp, brute, target)


if __name__ == '__main__':
    main()
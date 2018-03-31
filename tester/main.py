import os
import time
from os.path import splitext
cmd = os.system

BRUTE = 'brute.cpp'
TARGET = 'target.cpp'
GENERATOR = 'generator.py'
CHECKER = 'checker.py'

TMP_IN = 'tmp.in'
TARGET_OUT = 'target.out'
BRUTE_OUT = 'brute.out'

def get_name(name):
    return splitext(name)[0]

def iscpp(name):
    return splitext(name)[-1] == '.cpp'

def ispy(name):
    return splitext(name)[-1] == '.py'

def init():
    for x in [BRUTE, TARGET, GENERATOR]:
        if iscpp(x):
            cmd('g++ -std=c++11 {} -o {}'.format(x, get_name(x)))

def sample():
    # Generate test case
    print("Generating input test case...")
    if iscpp(GENERATOR):
        cmd('{}.exe > {}'.format(get_name(GENERATOR), TMP_IN))
    else:
        cmd('python {} > {}'.format(GENERATOR, TMP_IN))

    # Generate brute solutions
    start_brute = time.clock()
    print("Generating brute solution...")
    if iscpp(BRUTE):
        cmd('{}.exe < {} > {}'.format(get_name(BRUTE), TMP_IN, BRUTE_OUT))
    else:
        cmd('python {} < {} > {}'.format(BRUTE, TMP_IN, BRUTE_OUT))
    print("Execution time:", time.clock() - start_brute)

    # Generate target solutions
    start_target = time.clock()
    print("Generating target solution...")
    if iscpp(TARGET):
        cmd('{}.exe < {} > {}'.format(get_name(TARGET), TMP_IN, TARGET_OUT))
    else:
        cmd('python {} < {} > {}'.format(TARGET, TMP_IN, TARGET_OUT))
    print("Execution time:", time.clock() - start_target)

    # Check solutions
    print("Checking solutions")
    code = cmd('python {} {} {} {}'.format(CHECKER, TMP_IN, BRUTE_OUT, TARGET_OUT))

    return code == 0

def main():
    print("Initializing data...")
    init()

    while sample():
        print('OK!')

    print('BAD!!!!!')

if __name__ == '__main__':
    main()
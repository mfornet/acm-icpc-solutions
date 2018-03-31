import io
import sys

data = sys.stdin.read().replace('\n', ' ').split(' ')
rdata = [x for x in data if len(x) > 0]

if len(rdata) != 3:
    Y = [1, 1]
    while True:
        Y.append(Y[-1] + Y[-2])

b0 = int(rdata[0])
num = int(rdata[1], b0)
b1 = int(rdata[2])

if num == 0:
    print(0)
    exit(0)

value = [b1]

while value[-1] <= num:
    value.append(value[-1]**2)

abuff = io.StringIO()
start = True

def solve(num, index, total):
    global start
    if num == 0:
        if not start:
            abuff.write( u'' + ('0' * total))
        return

    if total == 1:
        start = False
        abuff.write(u'' + str(num))
        return

    D = num // value[index]
    N = num - D * value[index]

    solve(D, index - 1, total // 2)
    solve(N, index - 1, total // 2)

solve(num, -1, 2**len(value))
print(abuff.getvalue())

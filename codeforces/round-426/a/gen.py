import random

n = 10**5
m = 10**3

def gen():
    print(n)
    for i in range(n):
        x = random.randint(1,m)
        y = random.randint(1,m)
        print(x*y*y,y*x*x)
        #print(random.randint(1,m), random.randint(1,m))

gen()

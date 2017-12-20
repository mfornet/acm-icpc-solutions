import random


def gcd(a, b):
	while b > 0:
		a, b = b, a % b
	return a


def modpow(a, n, m):
	b = 1
	while n > 0:
		if n & 1:
			b = a * b % m
		a = a * a % m
		n >>= 1
	return b


def witness(a, s, d, n):
	x = modpow(a, d, n)
	if x == 1 or x == n - 1:
		return False
	for i in xrange(s - 1):
		x = x * x % n
		if x == 1: return True
		if x == n - 1: return False
	return True


def miller_rabin(n):
	if n < 2: return False
	if n == 2: return True
	if n % 2 == 0: return False
	d, s = n - 1, 0
	while d % 2 == 0:
		s += 1
		d /= 2
	test = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37)
	for p in test:
		if p >= n: break
		elif witness(p, s, d, n):
			return False
	return True


def pollard_rho(n):
	a = 2048
	c = 123121

	f = lambda x : (a * x * x + c) % n

	x, y = 1, 1

	while True:
		x = random.randint(1, n - 1) 
		y = random.randint(1, n - 1)
		k = gcd( abs(x - y), n )
		if 1 < k < n:
			return k

P = []

def factorize(n):
	if miller_rabin(n):
		P.append(n)
		return
	k = pollard_rho(n)
	factorize(k)
	factorize(n // k)


def test():
	A = [x for x in range(10**9, 10**9 + 1000) if miller_rabin(x)]
	it = 0

	for x in A:
		for y in A:
			print( it, x, y, pollard_rho(x * y) )
			it += 1

def main():
	global P
	t = input()
	for i in xrange(t):
		P = []
		n = input()
		factorize(n)
		P.sort()
		print ' '.join(str(x) for x in P)

main()

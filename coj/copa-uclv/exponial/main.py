
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


def phi(m):
	it, ans = 2, m

	while it * it <= m:
		if m % it == 0:
			ans = ans * (it - 1) // it
			while m % it == 0:
				m //= it
		it += 1
	if m > 1:
		ans = ans * (m - 1) // m
	return ans

def G(n, m):
	while True:
		g = gcd(n, m)
		if g == 1:
			return m
		m //= g

def calc(n, m):
	if m == 1: return 0

	if n <= 7:
		v = 1
		for i in range(2, n + 1):
			v = i**v
		return v % m

	m1 = G(n, m)
	m2 = m // m1
	pm1 = phi(m1)
	e = calc(n - 1, pm1)
	x = modpow(n, e, m1)

	ans = x * m2 * modpow(m2, pm1 - 1, m1) % m 
	return ans

while True:
    try:
        n, m = map(int, raw_input().split())
        print calc(n, m)
    except: 
        break

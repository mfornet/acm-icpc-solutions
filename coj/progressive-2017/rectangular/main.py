from sympy import *
n, k, i = symbols('n k i')

s = summation( (k - i) / 2 * (k - i + 1 + (n - i) * (n - i - 1)), (i, 0, k - 1))

print(s.simplify())

def g(n):
	return n * (n + 1) / 2

t = g(g(n))
print(t.simplify())

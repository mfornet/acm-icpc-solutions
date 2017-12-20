from sympy import *

def next(a, b, c):
	A = 4 * a - 3 * b - 3 * c
	B = 5 * a - 4 * b - 4 * c
	C = b - a
	return A, B, C

def test(n, a, b, c):
	for i in range(n):
		print(i, a,',', b,',', c)
		a, b, c = next(a, b, c)

def main():
	x, y, z = symbols("x y z")
	test(20, x, y, z)


if __name__ == '__main__':
	main()

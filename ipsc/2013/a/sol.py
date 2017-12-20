def memoize(f):
	S = {}
	def g(*args):
		if not args in S:
			S[args] = f(*args)
		return S[args]
	return g

@memoize
def solve(n):
	if n <= 1: return 0
	
	k = 2
	answer = solve(1) + solve(n - 1) + n - 1
	while True:
		v = n // k
		if k > v: break
		answer = max(
			answer,
			solve(v) + solve(n - v) + v * (n - v),
			solve(k) + solve(n - k) + k * (n - k)
			)
		k += 1
	return answer

for i in range(2, 20):
	print(i, solve(i), i * (i - 1) // 2)


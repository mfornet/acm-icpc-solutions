def prime(n):
	it = 2
	while it * it <= n:
		if n % it == 0:
			return False
		it += 1
	return True

A = [x for x in range(10**9, 10**9 + 1000) if prime(x)]

B = []

for i in range(len(A)):
	for j in range(i, len(A)):
		B.append( A[i] * A[j] )

print( len(B) )
for x in B:
	print(x)

def main():
	F = [1, 1]
	while F[-1] < 2**64:
		F.append( F[-1] + F[-2] )
	while F[-1] > 2**63 - 1:
		F = F[:-1]

	print(len(F))
	print(F[-1])



main()

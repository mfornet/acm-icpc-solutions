import random

def main():
	t = 1000
	k = 1000
	n = 10**11

	print(t + k)
	for i in range(t):
		print(n - i)

	for i in range(k):
		print(random.randint(1, 10**11));
	

if __name__ == '__main__':
	main()

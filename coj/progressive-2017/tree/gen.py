from random import randint as randi, shuffle, sample
import sys

max_capacity = 100


def gen_tree(n):
	edges = []

	for i in range(2, n+1):
		edges.append( (i, randi(1, i - 1), randi(1, max_capacity)) )

	shuffle(edges)

	return edges


def gen_query(n, q):
	qList = []
	for i in range(q):
		mode = randi(1, 2)
		u, v = randi(1, n), randi(1, n)
		qList.append( (mode, u, v) )
	return qList


def large_tree(n):
	return [(i, i + 1, randi(1, max_capacity)) for i in range(1, n)]

def large_query(n, q):
	upd = q // 2
	ask = q - upd
	return [(1, 1, n) for i in range(upd)] + [(2, 1, n) for i in range(ask)]


def generate(n, q):
	tree = gen_tree(n)
	qry  = gen_query(n, q)

	print(n)
	for u, v, c in tree: print(u, v, c)
	
	print(q)
	for m, u, v in qry:
		print(m, u, v)


if __name__ == '__main__':
	n, q = int(sys.argv[1]), int(sys.argv[2])
	generate(n, q)
	

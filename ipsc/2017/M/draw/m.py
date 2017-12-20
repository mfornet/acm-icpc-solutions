from PIL.Image import *

# a = open("m.png")

# n = 3640
# m = 3673

# s = set()

x0, x1 = 94, 3633
y0, y1 = 127, 3666

sizeX = (x1 - x0 + 1) // 10
sizeY = (y1 - y0 + 1) // 10

# for i in range(10):
# 	for j,c in enumerate("abcdefghij"):
# 		a.crop((x0 + sizeX * i, y0 + sizeY * i, x0 + sizeX * (i + 1), y0 + sizeY * (i + 1))).save(c+str(i)+".png")

def get(a, b, k):
	return int(k * a[0] + (1. - k) * b[0]), int(k * a[1] + (1. - k) * b[1])

def test(name):
	a = open( name )
	P = [(147,64), (249,82), (291,175), (247,266),(148,292),(68,228),(70,127)]

	vertex = (1000, 1000)

	for i in range(20,sizeX):
		for j in range(20,sizeY):
			if a.getpixel((i,j))[1] != 0:
				vertex = min(vertex, (i,j))
	
	# print(vertex)
	vertex = vertex[0] + 4, vertex[1] + 4
	# print(vertex)
	delta = P[-1][0] - vertex[0], P[-1][1] - vertex[1]
	for i in range(7):
		P[i] = P[i][0] - delta[0], P[i][1] - delta[1]
	# print(P)


	size = 100
	threshold = 170.

	edges = []

	for i in range(7):
		for j in range(i):
			
			value = 0
			total = 0
			L = [0]

			for k in range(size + 1):
				t = get(P[i], P[j], 1. * k / size)

				for dx in L:
					for dy in L:
						cx, cy = dx + t[0], dy + t[1]
						value += 255 - a.getpixel((cx,cy))[1]
						total += 1

			value = 1. * value / total

			print(i,j,value)
			
			if value < threshold:
				edges.append( (i,j) )

	# print(name[:2])
	# print(len(edges))
	# for e in edges:
	# 	print(e[0], e[1])


test("a0.png")
exit(0)

for i in range(10):
	for j,c in enumerate("abcdefghij"):
		name = c + str(i) + '.png'
		test(c + str(i) + '.png')
		# exit(0)

	
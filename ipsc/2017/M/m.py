from PIL.Image import *

a = open("m.png")

# n = 3640
# m = 3673

# s = set()

x0, x1 = 94, 3633
y0, y1 = 127, 3666

sizeX = (x1 - x0 + 1) // 10
sizeY = (y1 - y0 + 1) // 10

for i in range(10):
	for j,c in enumerate("abcdefghij"):
		a.crop((x0 + sizeX * i, y0 + sizeY * j, x0 + sizeX * (i + 1), y0 + sizeY * (j + 1))).save("draw/"+c+str(i)+".png")

def get(a, b, k):
	return int(k * a[0] + (1. - k) * b[0]), int(k * a[1] + (1. - k) * b[1])

def test(name):
	a = open( name )
	P = [(147,64), (249,82), (291,175), (247,266),(148,292),(68,228),(70,127)]

	value = 0
	for i in range(sizeX):
		for j in range(sizeY):
			value += a.getpixel((i,j))[0]

	print("value")

	size = 100
	threshold = 250.

	edges = []

	for i in range(7):
		for j in range(i):
			value = 0
			for k in range(size + 1):
				t = get(P[i], P[j], 1. * k / size)
				value += 255 - a.getpixel(t)[1]
			value = 1. * value / (size + 1)
			
			if value >= threshold:
				edges.append( (i,j) )

	print(name[:2])
	print(len(edges))
	for e in edges:
		print(e[0], e[1])



# for i in range(10):
# 	for j,c in enumerate("abcdefghij"):
# 		name = c + str(i) + '.png'
# 		print(name)
# 		test(c + str(i) + '.png')

	
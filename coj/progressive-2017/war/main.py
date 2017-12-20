from math import *
import matplotlib.pyplot as plt
import numpy as np

g = 9.8

def func(x, y, v, theta):
	A = -1. / 2 * g / x / x * v * v
	B = v * v / 2 / x
	C = -y

	return A * np.cos(theta) ** 2 + B * np.sin( 2 * theta ) + C


x = np.linspace(0, 2 * pi, 100)
y = func( 100, 0, 50, x )

plt.plot(x, y)
plt.show()


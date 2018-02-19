import matplotlib.pyplot as plt

X = [3, 4, 5, 9, 10]
Y = [4, 9, 7, 4, 5]

for x, y in zip(X, Y):
    plt.plot([0, x], [0, y])

plt.show()
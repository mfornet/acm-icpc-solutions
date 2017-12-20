import numpy as np

T = 10**7

sam = [10 * np.random.randn() + 70 for i in range(T)]
print(np.mean(sam))
print(np.std(sam))

print(100 * sum(x > 80 for x in sam) / len(sam))
print(100 * sum(x > 60 for x in sam) / len(sam))
print(100 * sum(x < 60 for x in sam) / len(sam))

import random
import time

res = {i : 0 for i in range(1, 7)}

a = time.time()

for n in range(100000000):
    res[random.randint(1, 6)] += 1

b = time.time()

print(res)
print(b - a)

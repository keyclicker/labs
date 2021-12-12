import math
import numpy as np

E = 0.01


def iterations(f1, f2):
    x, y = 0, 0

    i = 0
    while True:
        i += 1
        px, py = x, y
        x, y = f2(y), f1(x)
        print(x, y, i)

        if abs(px - x) < E and abs(py - y) < E:
            return x, y, i


f1 = lambda x: math.sin(x - 0.6) - 1.6
f2 = lambda y: 0.3 + math.cos(y) / 3

print(iterations(f1, f2))

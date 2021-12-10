from random import random
import numpy as np


def gauss(a_):
    a = np.copy(a_)
    n = a.shape[0]
    x = np.zeros(n)

    for i in range(n):
        for j in range(i + 1, n):
            ratio = a[j, i] / a[i, i]
            for k in range(n + 1):
                a[j, k] = a[j, k] - ratio * a[i, k]

    x[n - 1] = a[n - 1, n] / a[n - 1, n - 1]
    for i in range(n - 2, -1, -1):
        x[i] = a[i, n]
        for j in range(i + 1, n):
            x[i] = x[i] - a[i, j] * x[j]
        x[i] = x[i] / a[i, i]

    return x


def jacobi(a):
    n = a.shape[0]
    x = np.zeros(n)

    i = 0
    while True:
        i += 1
        nx = np.zeros(n)
        for i in range(n):
            nx[i] = a[i, n]
            for j in range(n):
                if j != i:
                    nx[i] -= a[i, j] * x[j]
            nx[i] /= a[i, i]

        if np.allclose(x, nx, atol=1e-4, rtol=0.) or i >= 20:
            break

        x = nx.copy()
    return x, i


def det(a):
    n = a.shape[0]

    if a.shape == (n, n):
        return a[0, 0] * a[1, 1] - a[1, 0] * a[0, 1]

    res = 0
    for i in range(n):
        res += (-1)**(i+1) * det()

    return res


np.set_printoptions(precision=2)

# a = np.array([
#     [3, -1, 1, 1],
#     [-1, 2, 0.5, 1.75],
#     [1, 0.5, 3, 2.5],
# ], dtype=float)
a = np.array([
    [30, -1, 1, 1, 5],
    [-1, 20, 0.5, 1.75, 60],
    [1, 0.5, 30, 2.5, 8],
    [3, 5, 2, 10, 42],
], dtype=float)

print("matrix:")
print(a)
print("det:")
print(np.linalg.det(a[:,:4]))
print(det(a[:,:4]))
print("gauss:")
print(gauss(a))
print(jacobi(a))
import numpy as np
from matplotlib import pyplot as plt


def get_A(n):
    res = np.zeros((n - 2, n - 2))
    for i in range(0, n - 2):
        cur = np.zeros(n - 2)
        for j in range(i - 1, i + 2):
            if j == i:
                cur[j] = 2 / 3
            elif j >= 0 and j < n - 2:
                cur[j] = 1 / 6
        res[i] = cur
    return res


def get_H(n):
    res = np.zeros((n - 2, n))
    for i in range(0, n - 2):
        cur = np.zeros(n)
        for j in range(i, i + 3):
            if j == i + 1:
                cur[j] = -2
            elif j < n:
                cur[j] = 1
        res[i] = cur
    return res


def get_m(n, f):
    A = get_A(n)
    H = get_H(n)
    return np.concatenate(([0], np.linalg.inv(A) @ H @ f, [0]))

# cubic spline
def get_s(x, f):
    M = get_m(x.size, f)
    s = lambda p, i: M[i - 1] * ((x[i] - p) ** 3) / 6 + M[i] * ((p - x[i - 1]) ** 3) / 6 + (f[i - 1] - M[i - 1]) * (
                x[i] - p) / 6 + (f[i] - M[i]) * (p - x[i - 1]) / 6
    return s

# fist degree polynomial
def get_L(x, f):
    def L(p, i):
        return (f[i - 1] * (x[i] - p) + f[i] * (p - x[i - 1])) / (x[i] - x[i - 1])

    return L


if __name__ == "__main__":
    xx, step = np.linspace(-5, 4, 10, retstep=True)

    assert step == 1
    yy = np.random.randint(50, size=10)
    print(yy)
    s = get_s(xx, yy)
    L = get_L(xx, yy)

    pairs = list(zip(xx, xx[1:]))

    for i in range(len(pairs)):
        first, second = pairs[i]
        x_hat = np.linspace(first, second, num=50)
        y_hat = [s(x, i + 1) for x in x_hat]
        plt.plot(x_hat, y_hat)
    plt.show()

    for i in range(len(pairs)):
        first, second = pairs[i]
        x_hat = np.linspace(first, second, num=50)
        y_hat = [L(x, i + 1) for x in x_hat]
        plt.plot(x_hat, y_hat)

    plt.show()
    plt.plot(xx, yy)
    plt.show()

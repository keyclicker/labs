import math

E = 0.0001


def iterations(p1, p2):
    x, y, i = 0, 0, 0
    while True:
        i += 1
        px, py = x, y
        print(x, y, i)
        x, y = p1(x), p2(y)
        if abs(px - x) < E and abs(py - y) < E:
            return x, y, i

#
# def phi1(x):
#     return math.sin(x - 0.6) - 1.6
#
#
# def phi2(y):
#     return 0.3 + math.cos(y) / 3


def phi2(y):
    return math.sin((0.3 + math.cos(y) / 3) - 0.6) - 1.6


def phi1(x):
    return 0.3 + math.cos(math.sin(x - 0.6) - 1.6) / 3


print(iterations(phi1, phi2))
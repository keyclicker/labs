import math

E = 10**(-4)


def dichotomy(f, a, b):
    i = 0
    x = b
    while True:
        i += 1
        prev_x = x
        x = (a + b) / 2

        if abs(x - prev_x) < E:
            return x, i

        if (f(a) > 0) == (f(x) > 0):
            a = x
        if (f(b) > 0) == (f(x) > 0):
            b = x


# evaluates iteration count
def eval_dichotomy(a, b):
    return math.floor(math.log2((b-a) / E)) + 1


def fi(f, x, t):
    return x - t * f(x)


def calc_t(df, a, b):
    return 2 / (df(a) + df(b))


def relaxation(f, df, a, b):
    t = calc_t(df, a, b)
    x = b
    i = 0
    while True:
        i += 1
        prev_x = x
        x = fi(f, x, t)

        if abs(x - prev_x) < E:
            return x, i


# evaluates iteration count
# def eval_relaxation(df, a, b):
#     z =
#     q = abs(df(a) - df(b)) / (df(a) + df(b))
#     return math.floor(math.log(z / E) / math.log(1 / q)) + 1


def fun(x):
    return x ** 3 + 4 * x - 6


def dfun(x):
    return 3 * x ** 2 + 4


a, b = 0, 2
print(dichotomy(fun, a, b), eval_dichotomy(a, b))
print(relaxation(fun, dfun, a, b))





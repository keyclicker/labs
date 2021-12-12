import numpy as np

E = 0.1


def eigenvalue(A, v):
    Av = A.dot(v)
    return v.dot(Av)


def power_iteration(a):
    d = a.shape[0]

    v = np.ones(d) / np.sqrt(d)
    ev = eigenvalue(a, v)

    while True:
        Av = a.dot(v)
        v_new = Av / np.linalg.norm(Av)
        ev_new = eigenvalue(a, v_new)

        print(ev, v)
        if np.abs(ev - ev_new) < 0.01:
            break

        v = v_new
        ev = ev_new

    return ev_new, v_new


a = np.array([
    [30, -1, 1, 1],
    [-1, 20, 0.5, 1.75],
    [1, 0.5, 30, 2.5],
    [3, 5, 2, 10],
], dtype=float)


print(power_iteration(a))

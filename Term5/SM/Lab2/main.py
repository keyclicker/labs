import numpy as np

from matplotlib import image
import matplotlib.pyplot as plt


def greville(M):
    M = np.array(M, dtype=float)
    ai = M[0:1]
    
    if np.count_nonzero(ai[0]) == 0:
        res = np.zeros_like(ai.T)
    else:
        res = ai.T/(ai @ ai.T)

    n = M.shape[0]
    for i in range(1, n):
        z_a = np.eye(res.shape[0]) - (res @ M[:i])
        r_a = res @ res.T
        ai = M[i:i+1]

        condition = (ai @ z_a) @ ai.T
        if np.count_nonzero(condition) != 1:
            a_inv = (r_a @ ai.T) / (1 + (ai @ r_a) @ ai.T)
        else:
            a_inv = (z_a @ ai.T) / condition

        res -= a_inv @ (ai @ res)
        res = np.concatenate((res, a_inv), axis=1)
    return res


def moore_penrose(M, sigma0, eps=1e-5):
    M = np.array(M, dtype=float)
    e = np.eye(M.shape[0])
    sigma_k = sigma0

    plus_matrix = M.T @ np.linalg.inv(M @ M.T + sigma0 * e)
    
    while True:
        sigma_k = sigma_k / 2
        previous = plus_matrix
        plus_matrix = M.T @ np.linalg.inv(M @ M.T + sigma_k * e)
        if np.linalg.norm(plus_matrix - previous) < eps:
            return plus_matrix



X, Y = image.imread('x2.bmp'), image.imread('y2.bmp')

MP = moore_penrose(X, 1)
G = greville(X)
A_moore = Y @ MP
A_greville = Y @ G

fig = plt.figure()

ax = fig.add_subplot(2, 2, 1)
ax.set_title('x2')
plt.imshow(X, cmap='gray')
plt.axis('off')

ax = fig.add_subplot(2, 2, 2)
ax.set_title('y2')
plt.imshow(Y, cmap='gray')
plt.axis('off')

ax = fig.add_subplot(2, 2, 3)
ax.set_title('greville')
plt.imshow(A_greville @ X, cmap='gray')
plt.axis('off')

ax = fig.add_subplot(2, 2, 4)
ax.set_title('moore penrose')
plt.imshow(A_moore @ X, cmap='gray')
plt.axis('off')


plt.show()


print("greville: ", np.linalg.norm(X @ G @ X - X))
print("greville: ", np.linalg.norm(G @ X @ G - G))
print("greville: ", np.linalg.norm(X @ G - (X @ G).T))
print("greville: ", np.linalg.norm(G @ X - (G @ X).T))

print("moore penrose: ", np.linalg.norm(X @ MP @ X - X))
print("moore penrose: ", np.linalg.norm(MP @ X @ MP - MP))
print("moore penrose: ", np.linalg.norm(X @ MP - (X @ MP).T))
print("moore penrose: ", np.linalg.norm(MP @ X - (MP @ X).T))


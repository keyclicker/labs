import numpy as np
from scipy.signal import argrelextrema
import matplotlib.pyplot as plt


signal = np.array(open("./f11.txt").read().split(), float)

T = 5
DT = 0.01
time = np.arange(0, T + DT, DT)

# Fourier transforms
n = time.shape[0]
n_range = np.arange(n)
k = n_range.reshape((n, 1))
M = np.exp(-2j * np.pi * k * n_range / n)

tr_signal = np.dot(M, signal) / n
tr_half = tr_signal[:tr_signal.shape[0] // 2 - 1]

extrema = np.array(argrelextrema(tr_half, np.less))

freq = extrema[0][0] / T
print("Frequency: ", freq)
 
# Applying least squares method
b = np.array([
    np.sum(signal * time ** 3), 
    np.sum(signal * time ** 2), 
    np.sum(signal * time), 
    np.sum(signal * np.sin(2. * np.pi * freq * time)), 
    np.sum(signal)
])

a = np.zeros((b.shape[0], b.shape[0]))

funcs = [
    time ** 3, time ** 2, time, 
    np.sin(2. * np.pi * freq * time), 
    np.ones(n)
]

for i in range(b.shape[0]):
    for j in range(b.shape[0]):
        a[i, j] = np.sum(funcs[i] * funcs[j])

solution = np.matmul(np.linalg.inv(a), b.T)
print("Solution:", solution)

approximated_func = np.dot(solution, funcs)

# Displaying a chart
fig, axs = plt.subplots(2)

plt.grid(True)

fig.suptitle("Data and approximation")

axs[0].plot(time, signal)
axs[1].plot(time, approximated_func)

plt.show()

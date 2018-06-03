#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

def Jacobi(axis):
    return(axis / x + 2.0 * np.sqrt(x / axis) * np.sqrt(1.0 - y * y))


fig = plt.figure(figsize=(8, 6), dpi=100)


X_MESH = 2000
Y_MESH = 5000


x = [i/X_MESH for i in range(int(0.5*X_MESH), int(1.5*X_MESH)+1)]
y = [i/Y_MESH for i in range(int(0.2*Y_MESH)+1)]
x, y = np.meshgrid(x, y)

print(x, y)


plt.contour(x, y, Jacobi(0.8), colors=["g"], levels=[3.0], linestyles="dashed", linewidths=0.5).clabel(fmt="%1.1f")
plt.contour(x, y, Jacobi(1.0), colors=["g"], levels=[3.0], linestyles="dashed", linewidths=0.5).clabel(fmt="%1.1f")
plt.contour(x, y, Jacobi(1.2), colors=["g"], levels=[3.0], linestyles="dashed", linewidths=0.5).clabel(fmt="%1.1f")


plt.xlim([0.5, 1.5])
plt.ylim([0, 0.2])


plt.show()

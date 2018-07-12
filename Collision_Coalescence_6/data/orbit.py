#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import matplotlib.pyplot as plt
import numpy as np


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


######################################################################
# directory = "N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1/"
# directory = "N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/"
# directory = "N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1/"
# directory = "N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/"
directory = "N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1/"

subdirectory = "orbit/"

if not (os.path.isdir(directory + subdirectory)):
    os.mkdir(directory + subdirectory)

N_p = 25


LINE = 100001  # 10^8yr


time = np.empty([N_p+1, LINE], dtype=float)  # (ファイル番号,行数)
ecc = np.empty([N_p+1, LINE], dtype=float)
axis = np.empty([N_p+1, LINE], dtype=float)
u = np.empty([N_p+1, LINE], dtype=float)
inc = np.empty([N_p+1, LINE], dtype=float)
Omega = np.empty([N_p+1, LINE], dtype=float)
omega = np.empty([N_p+1, LINE], dtype=float)
r_h = np.empty([N_p+1, LINE], dtype=float)
radius = np.empty([N_p+1, LINE], dtype=float)
mass = np.empty([N_p+1, LINE], dtype=float)

Px = np.empty([N_p+1, LINE], dtype=float)
Py = np.empty([N_p+1, LINE], dtype=float)
Pz = np.empty([N_p+1, LINE], dtype=float)
Qx = np.empty([N_p+1, LINE], dtype=float)
Qy = np.empty([N_p+1, LINE], dtype=float)
Qz = np.empty([N_p+1, LINE], dtype=float)
X = np.empty([N_p+1, LINE], dtype=float)
Y = np.empty([N_p+1, LINE], dtype=float)
Z = np.empty([N_p+1, LINE], dtype=float)
orbit_X = np.empty([N_p+1, LINE, 100], dtype=float)
orbit_Y = np.empty([N_p+1, LINE, 100], dtype=float)
orbit_Z = np.empty([N_p+1, LINE, 100], dtype=float)
#####


####################################################
for n in range(1, N_p+1):
    arr = np.genfromtxt(directory + "Planet%02d.dat" % n, dtype=np.float, delimiter="\t")
    if(LINE - arr.shape[0] > 0):
        print(n, "padding")
        arr = np.pad(arr, [(0, LINE - arr.shape[0]), (0, 0)], 'constant', constant_values=np.nan)
        # print(arr)

    time[n, :] = arr[:, 0]
    ecc[n, :] = arr[:, 1]
    axis[n, :] = arr[:, 2]
    u[n, :] = arr[:, 3]
    inc[n, :] = arr[:, 4]
    Omega[n, :] = arr[:, 5]
    omega[n, :] = arr[:, 6]
    r_h[n, :] = arr[:, 7]
    radius[n, :] = arr[:, 8]
    mass[n, :] = arr[:, 9]
    print(n, time[n, 1], axis[n, 1], ecc[n, 1], inc[n, 1])

    #####

    Px[n, :] = np.cos(omega[n, :]) * np.cos(Omega[n, :]) - np.sin(omega[n, :]) * np.sin(Omega[n, :]) * np.cos(inc[n, :])
    Qx[n, :] = - np.sin(omega[n, :]) * np.cos(Omega[n, :]) - np.cos(omega[n, :]) * np.sin(Omega[n, :]) * np.cos(inc[n, :])
    X[n, :] = axis[n, :] * Px[n, :] * (np.cos(u[n, :]) - ecc[n, :]) + axis[n, :] * np.sqrt(1.0 - ecc[n, :]*ecc[n, :]) * Qx[n, :] * np.sin(u[n, :])

    Py[n, :] = np.cos(omega[n, :]) * np.sin(Omega[n, :]) + np.sin(omega[n, :]) * np.cos(Omega[n, :]) * np.cos(inc[n, :])
    Qy[n, :] = - np.sin(omega[n, :]) * np.sin(Omega[n, :]) + np.cos(omega[n, :]) * np.cos(Omega[n, :]) * np.cos(inc[n, :])
    Y[n, :] = axis[n, :] * Py[n, :] * (np.cos(u[n, :]) - ecc[n, :]) + axis[n, :] * np.sqrt(1.0 - ecc[n, :]*ecc[n, :]) * Qy[n, :] * np.sin(u[n, :])

    Pz[n, :] = np.sin(omega[n, :]) * np.sin(inc[n, :])
    Qz[n, :] = np.cos(omega[n, :]) * np.sin(inc[n, :])
    Z[n, :] = axis[n, :] * Pz[n, :] * (np.cos(u[n, :]) - ecc[n, :]) + axis[n, :] * np.sqrt(1.0 - ecc[n, :]*ecc[n, :]) * Qz[n, :] * np.sin(u[n, :])

####################################################
if (N_p == 15):
    X[1, LINE-1] = X[1, LINE-2]
    Y[1, LINE-1] = Y[1, LINE-2]
    Z[1, LINE-1] = Z[1, LINE-2]
    ecc[1, LINE-1] = ecc[1, LINE-2]
    axis[1, LINE-1] = axis[1, LINE-2]
    u[1, LINE-1] = u[1, LINE-2]
    inc[1, LINE-1] = inc[1, LINE-2]
    Omega[1, LINE-1] = Omega[1, LINE-2]
    omega[1, LINE-1] = omega[1, LINE-2]
    r_h[1, LINE-1] = r_h[1, LINE-2]
    radius[1, LINE-1] = radius[1, LINE-2]
    mass[1, LINE-1] = mass[1, LINE-2]
    Px[1, LINE-1] = Px[1, LINE-2]
    Py[1, LINE-1] = Py[1, LINE-2]
    Pz[1, LINE-1] = Pz[1, LINE-2]
    Qx[1, LINE-1] = Qx[1, LINE-2]
    Qy[1, LINE-1] = Qy[1, LINE-2]
    Qz[1, LINE-1] = Qz[1, LINE-2]

    X[3, LINE-1] = X[3, LINE-2]
    Y[3, LINE-1] = Y[3, LINE-2]
    Z[3, LINE-1] = Z[3, LINE-2]
    ecc[3, LINE-1] = ecc[3, LINE-2]
    axis[3, LINE-1] = axis[3, LINE-2]
    u[3, LINE-1] = u[3, LINE-2]
    inc[3, LINE-1] = inc[3, LINE-2]
    Omega[3, LINE-1] = Omega[3, LINE-2]
    omega[3, LINE-1] = omega[3, LINE-2]
    r_h[3, LINE-1] = r_h[3, LINE-2]
    radius[3, LINE-1] = radius[3, LINE-2]
    mass[3, LINE-1] = mass[3, LINE-2]
    Px[3, LINE-1] = Px[3, LINE-2]
    Py[3, LINE-1] = Py[3, LINE-2]
    Pz[3, LINE-1] = Pz[3, LINE-2]
    Qx[3, LINE-1] = Qx[3, LINE-2]
    Qy[3, LINE-1] = Qy[3, LINE-2]
    Qz[3, LINE-1] = Qz[3, LINE-2]

    X[13, LINE-1] = X[13, LINE-2]
    Y[13, LINE-1] = Y[13, LINE-2]
    Z[13, LINE-1] = Z[13, LINE-2]
    ecc[13, LINE-1] = ecc[13, LINE-2]
    axis[13, LINE-1] = axis[13, LINE-2]
    u[13, LINE-1] = u[13, LINE-2]
    inc[13, LINE-1] = inc[13, LINE-2]
    Omega[13, LINE-1] = Omega[13, LINE-2]
    omega[13, LINE-1] = omega[13, LINE-2]
    r_h[13, LINE-1] = r_h[13, LINE-2]
    radius[13, LINE-1] = radius[13, LINE-2]
    mass[13, LINE-1] = mass[13, LINE-2]
    Px[13, LINE-1] = Px[13, LINE-2]
    Py[13, LINE-1] = Py[13, LINE-2]
    Pz[13, LINE-1] = Pz[13, LINE-2]
    Qx[13, LINE-1] = Qx[13, LINE-2]
    Qy[13, LINE-1] = Qy[13, LINE-2]
    Qz[13, LINE-1] = Qz[13, LINE-2]

    X[15, LINE-1] = X[15, LINE-2]
    Y[15, LINE-1] = Y[15, LINE-2]
    Z[15, LINE-1] = Z[15, LINE-2]
    ecc[15, LINE-1] = ecc[15, LINE-2]
    axis[15, LINE-1] = axis[15, LINE-2]
    u[15, LINE-1] = u[15, LINE-2]
    inc[15, LINE-1] = inc[15, LINE-2]
    Omega[15, LINE-1] = Omega[15, LINE-2]
    omega[15, LINE-1] = omega[15, LINE-2]
    r_h[15, LINE-1] = r_h[15, LINE-2]
    radius[15, LINE-1] = radius[15, LINE-2]
    mass[15, LINE-1] = mass[15, LINE-2]
    Px[15, LINE-1] = Px[15, LINE-2]
    Py[15, LINE-1] = Py[15, LINE-2]
    Pz[15, LINE-1] = Pz[15, LINE-2]
    Qx[15, LINE-1] = Qx[15, LINE-2]
    Qy[15, LINE-1] = Qy[15, LINE-2]
    Qz[15, LINE-1] = Qz[15, LINE-2]

if (N_p == 18):
    X[1, LINE-1] = X[1, LINE-2]
    Y[1, LINE-1] = Y[1, LINE-2]
    Z[1, LINE-1] = Z[1, LINE-2]
    ecc[1, LINE-1] = ecc[1, LINE-2]
    axis[1, LINE-1] = axis[1, LINE-2]
    u[1, LINE-1] = u[1, LINE-2]
    inc[1, LINE-1] = inc[1, LINE-2]
    Omega[1, LINE-1] = Omega[1, LINE-2]
    omega[1, LINE-1] = omega[1, LINE-2]
    r_h[1, LINE-1] = r_h[1, LINE-2]
    radius[1, LINE-1] = radius[1, LINE-2]
    mass[1, LINE-1] = mass[1, LINE-2]
    Px[1, LINE-1] = Px[1, LINE-2]
    Py[1, LINE-1] = Py[1, LINE-2]
    Pz[1, LINE-1] = Pz[1, LINE-2]
    Qx[1, LINE-1] = Qx[1, LINE-2]
    Qy[1, LINE-1] = Qy[1, LINE-2]
    Qz[1, LINE-1] = Qz[1, LINE-2]

    X[2, LINE-1] = X[2, LINE-2]
    Y[2, LINE-1] = Y[2, LINE-2]
    Z[2, LINE-1] = Z[2, LINE-2]
    ecc[2, LINE-1] = ecc[2, LINE-2]
    axis[2, LINE-1] = axis[2, LINE-2]
    u[2, LINE-1] = u[2, LINE-2]
    inc[2, LINE-1] = inc[2, LINE-2]
    Omega[2, LINE-1] = Omega[2, LINE-2]
    omega[2, LINE-1] = omega[2, LINE-2]
    r_h[2, LINE-1] = r_h[2, LINE-2]
    radius[2, LINE-1] = radius[2, LINE-2]
    mass[2, LINE-1] = mass[2, LINE-2]
    Px[2, LINE-1] = Px[2, LINE-2]
    Py[2, LINE-1] = Py[2, LINE-2]
    Pz[2, LINE-1] = Pz[2, LINE-2]
    Qx[2, LINE-1] = Qx[2, LINE-2]
    Qy[2, LINE-1] = Qy[2, LINE-2]
    Qz[2, LINE-1] = Qz[2, LINE-2]

    X[14, LINE-1] = X[14, LINE-2]
    Y[14, LINE-1] = Y[14, LINE-2]
    Z[14, LINE-1] = Z[14, LINE-2]
    ecc[14, LINE-1] = ecc[14, LINE-2]
    axis[14, LINE-1] = axis[14, LINE-2]
    u[14, LINE-1] = u[14, LINE-2]
    inc[14, LINE-1] = inc[14, LINE-2]
    Omega[14, LINE-1] = Omega[14, LINE-2]
    omega[14, LINE-1] = omega[14, LINE-2]
    r_h[14, LINE-1] = r_h[14, LINE-2]
    radius[14, LINE-1] = radius[14, LINE-2]
    mass[14, LINE-1] = mass[14, LINE-2]
    Px[14, LINE-1] = Px[14, LINE-2]
    Py[14, LINE-1] = Py[14, LINE-2]
    Pz[14, LINE-1] = Pz[14, LINE-2]
    Qx[14, LINE-1] = Qx[14, LINE-2]
    Qy[14, LINE-1] = Qy[14, LINE-2]
    Qz[14, LINE-1] = Qz[14, LINE-2]

    X[17, LINE-1] = X[17, LINE-2]
    Y[17, LINE-1] = Y[17, LINE-2]
    Z[17, LINE-1] = Z[17, LINE-2]
    ecc[17, LINE-1] = ecc[17, LINE-2]
    axis[17, LINE-1] = axis[17, LINE-2]
    u[17, LINE-1] = u[17, LINE-2]
    inc[17, LINE-1] = inc[17, LINE-2]
    Omega[17, LINE-1] = Omega[17, LINE-2]
    omega[17, LINE-1] = omega[17, LINE-2]
    r_h[17, LINE-1] = r_h[17, LINE-2]
    radius[17, LINE-1] = radius[17, LINE-2]
    mass[17, LINE-1] = mass[17, LINE-2]
    Px[17, LINE-1] = Px[17, LINE-2]
    Py[17, LINE-1] = Py[17, LINE-2]
    Pz[17, LINE-1] = Pz[17, LINE-2]
    Qx[17, LINE-1] = Qx[17, LINE-2]
    Qy[17, LINE-1] = Qy[17, LINE-2]
    Qz[17, LINE-1] = Qz[17, LINE-2]


# 100個(10^5yr)ごと
"""
for T in range(0, LINE, 100):

    with open(directory + subdirectory + "Planet_orbit.dat.%04d" % int(T/100), 'w') as fp:
        fp.write("# n\tx\ty\tz\n")

    for n in range(1, N_p+1):
        orbit_X[n, T, :] = axis[n, T] * Px[n, T] * (np.cos(np.linspace(0.0, 2.0*np.pi, 100)) - ecc[n, T]) + axis[n, T] * np.sqrt(1.0 - ecc[n, T]*ecc[n, T]) * Qx[n, T] * np.sin(np.linspace(0.0, 2.0*np.pi, 100))
        orbit_Y[n, T, :] = axis[n, T] * Py[n, T] * (np.cos(np.linspace(0.0, 2.0*np.pi, 100)) - ecc[n, T]) + axis[n, T] * np.sqrt(1.0 - ecc[n, T]*ecc[n, T]) * Qy[n, T] * np.sin(np.linspace(0.0, 2.0*np.pi, 100))
        orbit_Z[n, T, :] = axis[n, T] * Pz[n, T] * (np.cos(np.linspace(0.0, 2.0*np.pi, 100)) - ecc[n, T]) + axis[n, T] * np.sqrt(1.0 - ecc[n, T]*ecc[n, T]) * Qz[n, T] * np.sin(np.linspace(0.0, 2.0*np.pi, 100))

        with open(directory + subdirectory + "Planet_orbit.dat.%04d" % int(T/100), 'ab') as fp:
            arr3 = np.empty([100, 4], dtype=float)
            arr3[:, 0] = np.repeat([float(n)], 100)
            arr3[:, 1] = orbit_X[n, T, :]
            arr3[:, 2] = orbit_Y[n, T, :]
            arr3[:, 3] = orbit_Z[n, T, :]
            np.savetxt(fp, arr3, fmt="%.15f", delimiter="\t", newline="\n")

        with open(directory + subdirectory + "Planet_orbit.dat.%04d" % int(T/100), 'a') as fp:
            fp.write("\n\n")

    print(T)
"""

# logっぽく
timelist = list(range(0, 10, 1))
timelist += list(range(10, 100, 10))
timelist += list(range(100, 1000, 100))
timelist += list(range(1000, 10000, 1000))
timelist += list(range(10000, 100000, 10000))
timelist += list([LINE - 1])

for T in timelist:
    with open(directory + subdirectory + "Planet_orbit.dat.%06d" % T, 'w') as fp:
        fp.write("# n\tx\ty\tz\n")

    for n in range(1, N_p+1):
        orbit_X[n, T, :] = axis[n, T] * Px[n, T] * (np.cos(np.linspace(0.0, 2.0*np.pi, 100)) - ecc[n, T]) + axis[n, T] * np.sqrt(1.0 - ecc[n, T]*ecc[n, T]) * Qx[n, T] * np.sin(np.linspace(0.0, 2.0*np.pi, 100))
        orbit_Y[n, T, :] = axis[n, T] * Py[n, T] * (np.cos(np.linspace(0.0, 2.0*np.pi, 100)) - ecc[n, T]) + axis[n, T] * np.sqrt(1.0 - ecc[n, T]*ecc[n, T]) * Qy[n, T] * np.sin(np.linspace(0.0, 2.0*np.pi, 100))
        orbit_Z[n, T, :] = axis[n, T] * Pz[n, T] * (np.cos(np.linspace(0.0, 2.0*np.pi, 100)) - ecc[n, T]) + axis[n, T] * np.sqrt(1.0 - ecc[n, T]*ecc[n, T]) * Qz[n, T] * np.sin(np.linspace(0.0, 2.0*np.pi, 100))

        with open(directory + subdirectory + "Planet_orbit.dat.%06d" % T, 'ab') as fp:
            arr3 = np.empty([100, 4], dtype=float)
            arr3[:, 0] = np.repeat([float(n)], 100)
            arr3[:, 1] = orbit_X[n, T, :]
            arr3[:, 2] = orbit_Y[n, T, :]
            arr3[:, 3] = orbit_Z[n, T, :]
            np.savetxt(fp, arr3, fmt="%.15f", delimiter="\t", newline="\n")

        with open(directory + subdirectory + "Planet_orbit.dat.%06d" % T, 'a') as fp:
            fp.write("\n\n")

    print(T)

"""
for T in range(0, LINE):
    #####
    plt.figure(figsize=(10, 8), dpi=100)
    # plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}},{\rm time}: %.3e {\rm yr}$" % time[1, T], fontsize=18)
    # plt.xlim([0.8, 1.2])
    # plt.ylim([0, 0.35])

    plt.xlabel('x [AU]', fontsize=25)
    plt.ylabel('y [AU]', fontsize=25)

    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)
    plt.grid(True)

    for n in range(1, N_p+1):
        plt.scatter(X[n, T], Y[n, T], color="b", s=20, label="Planet%02d" % n)
    plt.legend(loc="upper left", fontsize=15)
    # plt.tight_layout()

    print(time[1, T])
    plt.show()

    filename = "../image/" + directory + "orbit_T%06d.png" % T
    plt.savefig(filename)
    plt.close()
    #####
"""


for n in range(1, N_p+1):
    arr2 = np.empty([LINE, 7], dtype=float)
    arr2[:, 0] = np.linspace(0.0, 1.0E8, LINE)
    arr2[:, 1] = X[n, :]
    arr2[:, 2] = Y[n, :]
    arr2[:, 3] = Z[n, :]
    arr2[:, 4] = r_h[n, :]
    arr2[:, 5] = radius[n, :]
    arr2[:, 6] = mass[n, :]
    np.savetxt(directory + "Planet%02d_position.dat" % n, arr2, fmt="%.15e", delimiter="\t", newline="\n", header="time\tx\ty\tz\tr_h\tradius\tmass")

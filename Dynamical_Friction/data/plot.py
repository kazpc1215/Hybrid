#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
# import matplotlib.animation as animation

# plt.figure(figsize=(10, 8), dpi=100)


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


######################################################################
path = "/Users/isoya.kazuhide/Dynamical_Friction/data/Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand4_ver2//"

LINE = 2001

N_p = 1
N_tr = 1000

time = np.empty([N_p+N_tr+1, LINE], dtype=float)  # (ファイル番号,行数)
ecc = np.empty([N_p+N_tr+1, LINE], dtype=float)
axis = np.empty([N_p+N_tr+1, LINE], dtype=float)
u = np.empty([N_p+N_tr+1, LINE], dtype=float)
inc = np.empty([N_p+N_tr+1, LINE], dtype=float)
Omega = np.empty([N_p+N_tr+1, LINE], dtype=float)
omega = np.empty([N_p+N_tr+1, LINE], dtype=float)
r_h = np.empty([N_p+N_tr+1, LINE], dtype=float)
radius = np.empty([N_p+N_tr+1, LINE], dtype=float)
mass = np.empty([N_p+N_tr+1, LINE], dtype=float)
#####
for n in range(1, N_p+1):
    arr = np.genfromtxt(path + "Planet%02d.dat" % n, dtype=np.float, delimiter="\t")

    time[n, :] = arr[:, 0]
    ecc[n, :] = arr[:, 1]
    axis[n, :] = arr[:, 2]
    # u[n, :] = arr[:, 3]
    inc[n, :] = arr[:, 4]
    # Omega[n, :] = arr[:, 5]
    # omega[n, :] = arr[:, 6]
    # r_h[n, :] = arr[:, 7]
    # radius[n, :] = arr[:, 8]
    # mass[n, :] = arr[:, 9]
    print(n, time[n, 1], axis[n, 1], ecc[n, 1], inc[n, 1])

#####
for n in range(N_p+1, N_p+N_tr+1):
    arr = np.genfromtxt(path + "tracer%06d.dat" % (n-N_p), dtype=np.float, delimiter="\t")

    time[n, :] = arr[:, 0]
    ecc[n, :] = arr[:, 1]
    axis[n, :] = arr[:, 2]
    # u[n, :] = arr[:, 3]
    inc[n, :] = arr[:, 4]
    # Omega[n, :] = arr[:, 5]
    # omega[n, :] = arr[:, 6]
    # r_h[n, :] = arr[:, 7]
    # radius[n, :] = arr[:, 8]
    # mass[n, :] = arr[:, 9]
    print(n, time[n, 1], axis[n, 1], ecc[n, 1], inc[n, 1])

#####

for T in range(0, 2001):
    plt.figure(figsize=(10, 8), dpi=100)
    plt.xlim([0.9, 1.1])
    plt.ylim([0, 0.1])
    plt.xlabel('semi-major axis [AU]', fontsize=25)
    plt.ylabel('ecc', fontsize=25)
    plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}},{\rm time}: %04.0f {\rm yr}$" % time[1, T], fontsize=18)
    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)
    plt.scatter(axis[2:, T], ecc[2:, T], color="b", s=5, label="Tracer")
    plt.scatter(axis[1, T], ecc[1, T], color="r", s=20, label="Planet")
    plt.legend(loc="upper left", fontsize=15)
    plt.tight_layout()
    filename = "../image/Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand4_ver2/axis_ecc_T%04.0fyr.png" % time[1, T]
    plt.grid(True)
    plt.savefig(filename)
    plt.close()

    plt.figure(figsize=(10, 8), dpi=100)
    plt.xlim([0.9, 1.1])
    plt.ylim([0, 0.05])
    plt.xlabel('semi-major axis [AU]', fontsize=25)
    plt.ylabel('inc [rad]', fontsize=25)
    plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}},{\rm time}: %04.0f {\rm yr}$" % time[1, T], fontsize=18)
    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)
    plt.scatter(axis[2:, T], inc[2:, T], color="b", s=5, label="Tracer")
    plt.scatter(axis[1, T], inc[1, T], color="r", s=20, label="Planet")
    plt.legend(loc="upper left", fontsize=15)
    plt.tight_layout()
    filename = "../image/Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand4_ver2/axis_inc_T%04.0fyr.png" % time[1, T]
    plt.grid(True)
    plt.savefig(filename)
    plt.close()

    print(time[1, T])
    # plt.show()

#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
# import matplotlib.animation as animation

plt.figure(figsize=(10, 8), dpi=100)


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


######################################################################
path = "/Users/isoya.kazuhide/Master1/Dynamical_Friction/data/*****//"

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
#####
for n in range(1, N_p+1):
    arr = np.genfromtxt(path + "Planet%02d.dat" % n, dtype=np.float, delimiter="\t")

    time[n, :] = arr[:, 0]
    ecc[n, :] = arr[:, 1]
    axis[n, :] = arr[:, 2]
    u[n, :] = arr[:, 3]
    inc[n, :] = arr[:, 4]
    Omega[n, :] = arr[:, 5]
    omega[n, :] = arr[:, 6]
    r_h[n, :] = arr[:, 7]
    # print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(LINE, dtype=float)
# print ecc_2
for n in range(1, N_p+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_p
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1, :], ecc_rms, color="b", label="run1")

inc_2 = np.zeros(LINE, dtype=float)
# print inc_2
for n in range(1, N_p+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_p
inc_rms = np.sqrt(inc_2_mean)
# print inc_rms
plt.plot(time[1, :], inc_rms, color="b")

#####
for n in range(N_p+1, N_p+N_tr+1):
    arr = np.genfromtxt(path + "tracer%06d.dat" % (n-N_p), dtype=np.float, delimiter="\t")

    time[n, :] = arr[:, 0]
    ecc[n, :] = arr[:, 1]
    axis[n, :] = arr[:, 2]
    u[n, :] = arr[:, 3]
    inc[n, :] = arr[:, 4]
    Omega[n, :] = arr[:, 5]
    omega[n, :] = arr[:, 6]
    r_h[n, :] = arr[:, 7]
    # print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(LINE, dtype=float)
# print ecc_2
for n in range(N_p+1, N_p+N_tr+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_tr
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1, :], ecc_rms, color="b")

inc_2 = np.zeros(LINE, dtype=float)
# print inc_2
for n in range(N_p+1, N_p+N_tr+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_tr
inc_rms = np.sqrt(inc_2_mean)
# print inc_rms
plt.plot(time[1, :], inc_rms, color="b")
######################################################################


plt.xlim([0, 2000])
plt.ylim([0, 0.006])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
# plt.yscale("log")
plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('ecc,inc', fontsize=25)
plt.grid(True)
plt.tight_layout()
plt.legend(bbox_to_anchor=(0.49, 0.48), borderaxespad=0, fontsize=15, ncol=3)
# plt.legend(bbox_to_anchor=(1.0, 0.6),fontsize=15)
# plt.title("time=%d"%time[1,j],fontsize=18)


plt.show()

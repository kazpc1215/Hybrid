#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
# import matplotlib.animation as animation

plt.figure(figsize=(10, 8), dpi=100)


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


######################################################################
path = "/Users/isoya.kazuhide/Dynamical_Friction/data/Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand3//"

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
    # axis[n, :] = arr[:, 2]
    # u[n, :] = arr[:, 3]
    inc[n, :] = arr[:, 4]
    # Omega[n, :] = arr[:, 5]
    # omega[n, :] = arr[:, 6]
    # r_h[n, :] = arr[:, 7]
    # radius[n, :] = arr[:, 8]
    # mass[n, :] = arr[:, 9]
    print(n, time[n, 1], axis[n, 1], ecc[n, 1], inc[n, 1])


ecc_2 = np.zeros(LINE, dtype=float)
for n in range(1, N_p+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_p
ecc_rms_p = np.sqrt(ecc_2_mean)
# plt.plot(time[1, :], ecc_rms_p, color="g", label=r"$e_{\rm p}$")

inc_2 = np.zeros(LINE, dtype=float)
for n in range(1, N_p+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_p
inc_rms_p = np.sqrt(inc_2_mean)
# plt.plot(time[1, :], inc_rms_p, color="g", label=r"$i_{\rm p}$")

#####
for n in range(N_p+1, N_p+N_tr+1):
    arr = np.genfromtxt(path + "tracer%06d.dat" % (n-N_p), dtype=np.float, delimiter="\t")

    time[n, :] = arr[:, 0]
    ecc[n, :] = arr[:, 1]
    # axis[n, :] = arr[:, 2]
    # u[n, :] = arr[:, 3]
    inc[n, :] = arr[:, 4]
    # Omega[n, :] = arr[:, 5]
    # omega[n, :] = arr[:, 6]
    # r_h[n, :] = arr[:, 7]
    # radius[n, :] = arr[:, 8]
    # mass[n, :] = arr[:, 9]
    print(n, time[n, 1], axis[n, 1], ecc[n, 1], inc[n, 1])


ecc_2 = np.zeros(LINE, dtype=float)
for n in range(N_p+1, N_p+N_tr+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_tr
ecc_rms_tr = np.sqrt(ecc_2_mean)
# plt.plot(time[1, :], ecc_rms_tr, color="b", label=r"$e_{\rm rms}$")

inc_2 = np.zeros(LINE, dtype=float)
for n in range(N_p+1, N_p+N_tr+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_tr
inc_rms_tr = np.sqrt(inc_2_mean)
# plt.plot(time[1, :], inc_rms_tr, color="b", label=r"$i_{\rm rms}$")
######################################################################


plt.xlim([0, 2000])
plt.ylim([0, 0.06])
# plt.ylim([0, 0.025])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
# plt.xscale("log")
# plt.yscale("log")
plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('ecc', fontsize=25)
# plt.ylabel('inc [rad]', fontsize=25)
plt.grid(True)
plt.legend(loc="upper left", fontsize=15)
# plt.legend(bbox_to_anchor=(1.0, 0.6),fontsize=15)
plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}}$", fontsize=18)
plt.tight_layout()

# plt.show()

arr2 = np.empty([LINE, 5], dtype=float)
arr2[:, 0] = time[1, :]
arr2[:, 1] = ecc_rms_p
arr2[:, 2] = inc_rms_p
arr2[:, 3] = ecc_rms_tr
arr2[:, 4] = inc_rms_tr


np.savetxt(path + "RMS.dat", arr2, fmt="%.15e", delimiter="\t", newline="\n", header="time\tecc_p\tinc_p\tecc_rms_tr\tinc_rms_tr")

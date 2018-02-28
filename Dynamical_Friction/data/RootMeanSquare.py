#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
# import matplotlib.animation as animation


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


######################################################################
path = "/Users/isoya.kazuhide/Dynamical_Friction/data/Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1//"

LINE = 10001

N_p = 3
N_tr = 3000

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
    print(n, time[n, 1], ecc[n, 1], inc[n, 1])


ecc_2 = np.zeros(LINE, dtype=float)
for n in range(1, N_p+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_p
ecc_rms_p = np.sqrt(ecc_2_mean)


inc_2 = np.zeros(LINE, dtype=float)
for n in range(1, N_p+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_p
inc_rms_p = np.sqrt(inc_2_mean)


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
    print(n, time[n, 1], ecc[n, 1], inc[n, 1])


ecc_2 = np.zeros(LINE, dtype=float)
for n in range(N_p+1, N_p+N_tr+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_tr
ecc_rms_tr = np.sqrt(ecc_2_mean)


inc_2 = np.zeros(LINE, dtype=float)
for n in range(N_p+1, N_p+N_tr+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_tr
inc_rms_tr = np.sqrt(inc_2_mean)


######################################################################
plt.figure(figsize=(10, 8), dpi=100)

plt.plot(time[1, :], ecc_rms_p, color="g", label=r"$e_{\rm p,rms}$")
plt.plot(time[1, :], ecc[1, :], color="c", label=r"$e_{\rm p,1}$")  # N3E3用に付け足し
plt.plot(time[1, :], ecc[2, :], color="m", label=r"$e_{\rm p,2}$")
plt.plot(time[1, :], ecc[3, :], color="y", label=r"$e_{\rm p,3}$")
plt.plot(time[1, :], ecc_rms_tr, color="b", label=r"$e_{\rm tr,rms}$")


plt.xlim([0, 10000])
plt.ylim([0, 0.12])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)

plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('ecc', fontsize=25)
plt.grid(True)
plt.legend(loc="upper left", fontsize=15)

plt.title(r"$N_{\rm tr}=3000,M_{\rm tot}=30 {\rm M_{\oplus}}$", fontsize=18)
plt.tight_layout()

plt.show()

plt.close()

#####################################################################
plt.figure(figsize=(10, 8), dpi=100)

plt.plot(time[1, :], inc_rms_p, color="g", label=r"$i_{\rm p,rms}$")
plt.plot(time[1, :], inc[1, :], color="c", label=r"$i_{\rm p,1}$")  # N3E3用に付け足し
plt.plot(time[1, :], inc[2, :], color="m", label=r"$i_{\rm p,2}$")
plt.plot(time[1, :], inc[3, :], color="y", label=r"$i_{\rm p,3}$")
plt.plot(time[1, :], inc_rms_tr, color="b", label=r"$i_{\rm tr,rms}$")

plt.xlim([0, 10000])
plt.ylim([0, 0.07])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)

plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('inc [rad]', fontsize=25)
plt.grid(True)
plt.legend(loc="upper left", fontsize=15)

plt.title(r"$N_{\rm tr}=3000,M_{\rm tot}=30 {\rm M_{\oplus}}$", fontsize=18)
plt.tight_layout()

plt.show()

plt.close()

#####################################################################
"""
arr2 = np.empty([LINE, 5], dtype=float)
arr2[:, 0] = time[1, :]
arr2[:, 1] = ecc_rms_p
arr2[:, 2] = inc_rms_p
arr2[:, 3] = ecc_rms_tr
arr2[:, 4] = inc_rms_tr

np.savetxt(path + "RMS.dat", arr2, fmt="%.15e", delimiter="\t", newline="\n", header="time\tecc_p\tinc_p\tecc_rms_tr\tinc_rms_tr")
"""


arr2 = np.empty([LINE, 11], dtype=float)
arr2[:, 0] = time[1, :]
arr2[:, 1] = ecc_rms_p
arr2[:, 2] = inc_rms_p
arr2[:, 3] = ecc_rms_tr
arr2[:, 4] = inc_rms_tr
arr2[:, 5] = ecc[1, :]
arr2[:, 6] = ecc[2, :]
arr2[:, 7] = ecc[3, :]
arr2[:, 8] = inc[1, :]
arr2[:, 9] = inc[2, :]
arr2[:, 10] = inc[3, :]

np.savetxt(path + "RMS_ver2.dat", arr2, fmt="%.15e", delimiter="\t", newline="\n", header="time\tecc_rms_p\tinc_rms_p\tecc_rms_tr\tinc_rms_tr\tecc_p=1\tecc_p=2\tecc_p=3\tinc_p=1\tinc_p=2\tinc_p=3")

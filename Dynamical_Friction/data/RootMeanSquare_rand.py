#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
# import matplotlib.animation as animation


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


######################################################################
# path = "/Users/isoya.kazuhide/Dynamical_Friction/data/"
directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/"


N_p = 3
N_tr = 3000

if(N_p == 1):
    LINE = 42  # 10000yr
    SUBDIR_NUM = 40
elif(N_p == 3):
    LINE = 34  # 1000yr
    SUBDIR_NUM = 13


time = np.empty([SUBDIR_NUM, LINE], dtype=float)  # (ファイル番号,行数)
ecc_1 = np.empty([SUBDIR_NUM, LINE], dtype=float)
ecc_p_rms = np.empty([SUBDIR_NUM, LINE], dtype=float)
ecc_tr_rms = np.empty([SUBDIR_NUM, LINE], dtype=float)
inc_1 = np.empty([SUBDIR_NUM, LINE], dtype=float)
inc_p_rms = np.empty([SUBDIR_NUM, LINE], dtype=float)
inc_tr_rms = np.empty([SUBDIR_NUM, LINE], dtype=float)
if(N_p == 3):
    ecc_2 = np.empty([SUBDIR_NUM, LINE], dtype=float)
    ecc_3 = np.empty([SUBDIR_NUM, LINE], dtype=float)
    inc_2 = np.empty([SUBDIR_NUM, LINE], dtype=float)
    inc_3 = np.empty([SUBDIR_NUM, LINE], dtype=float)
#####


for subnum in range(1, SUBDIR_NUM+1):
    subdirectory = "rand%02d/" % subnum

    arr = np.genfromtxt(directory + subdirectory + "RMS_Ntr%4d.dat" % N_tr, dtype=np.float, delimiter="\t")
    print(arr.shape)

    if(N_p == 1):
        time[subnum-1, :] = arr[:, 0]
        ecc_1[subnum-1, :] = arr[:, 1]
        ecc_p_rms[subnum-1, :] = arr[:, 2]
        ecc_tr_rms[subnum-1, :] = arr[:, 3]
        inc_1[subnum-1, :] = arr[:, 4]
        inc_p_rms[subnum-1, :] = arr[:, 5]
        inc_tr_rms[subnum-1, :] = arr[:, 6]
    elif(N_p == 3):
        time[subnum-1, :] = arr[:, 0]
        ecc_1[subnum-1, :] = arr[:, 1]
        ecc_2[subnum-1, :] = arr[:, 2]
        ecc_3[subnum-1, :] = arr[:, 3]
        ecc_p_rms[subnum-1, :] = arr[:, 4]
        ecc_tr_rms[subnum-1, :] = arr[:, 5]
        inc_1[subnum-1, :] = arr[:, 6]
        inc_2[subnum-1, :] = arr[:, 7]
        inc_3[subnum-1, :] = arr[:, 8]
        inc_p_rms[subnum-1, :] = arr[:, 9]
        inc_tr_rms[subnum-1, :] = arr[:, 10]

    print(subnum, time[subnum-1, 1], ecc_p_rms[subnum-1, 1], inc_p_rms[subnum-1, 1])


######################################################################
if(N_p == 1):
    rand_rms = np.zeros([7, LINE], dtype=float)
    for subnum in range(0, SUBDIR_NUM):
        rand_rms[1, :] = rand_rms[1, :] + ecc_1[subnum, :] * ecc_1[subnum, :]
        rand_rms[2, :] = rand_rms[2, :] + ecc_p_rms[subnum, :] * ecc_p_rms[subnum, :]
        rand_rms[3, :] = rand_rms[3, :] + ecc_tr_rms[subnum, :] * ecc_tr_rms[subnum, :]
        rand_rms[4, :] = rand_rms[4, :] + inc_1[subnum, :] * inc_1[subnum, :]
        rand_rms[5, :] = rand_rms[5, :] + inc_p_rms[subnum, :] * inc_p_rms[subnum, :]
        rand_rms[6, :] = rand_rms[6, :] + inc_tr_rms[subnum, :] * inc_tr_rms[subnum, :]
    rand_rms = rand_rms / SUBDIR_NUM
    rand_rms = np.sqrt(rand_rms)
elif(N_p == 3):
    rand_rms = np.zeros([11, LINE], dtype=float)
    for subnum in range(0, SUBDIR_NUM):
        rand_rms[1, :] = rand_rms[1, :] + ecc_1[subnum, :] * ecc_1[subnum, :]
        rand_rms[2, :] = rand_rms[2, :] + ecc_2[subnum, :] * ecc_2[subnum, :]
        rand_rms[3, :] = rand_rms[3, :] + ecc_3[subnum, :] * ecc_3[subnum, :]
        rand_rms[4, :] = rand_rms[4, :] + ecc_p_rms[subnum, :] * ecc_p_rms[subnum, :]
        rand_rms[5, :] = rand_rms[5, :] + ecc_tr_rms[subnum, :] * ecc_tr_rms[subnum, :]
        rand_rms[6, :] = rand_rms[6, :] + inc_1[subnum, :] * inc_1[subnum, :]
        rand_rms[7, :] = rand_rms[7, :] + inc_2[subnum, :] * inc_2[subnum, :]
        rand_rms[8, :] = rand_rms[8, :] + inc_3[subnum, :] * inc_3[subnum, :]
        rand_rms[9, :] = rand_rms[9, :] + inc_p_rms[subnum, :] * inc_p_rms[subnum, :]
        rand_rms[10, :] = rand_rms[10, :] + inc_tr_rms[subnum, :] * inc_tr_rms[subnum, :]
    rand_rms = rand_rms / SUBDIR_NUM
    rand_rms = np.sqrt(rand_rms)

rand_rms[0, :] = time[0, :]
######################################################################
plt.figure(figsize=(10, 8), dpi=100)

if(N_p == 1):
    plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], rand_rms[2, :], color="r", label=r"$e_{\rm p}$")
    plt.plot(time[1, :], rand_rms[3, :], color="b", label=r"$e_{\rm tr,rms}$")
elif(N_p == 3):
    plt.title(r"$N_{\rm tr}=3000,M_{\rm tot}=30 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], rand_rms[1, :], color="c", linestyle="dashed", linewidth=0.5, label=r"$e_{\rm p,1}$")
    plt.plot(time[1, :], rand_rms[2, :], color="m", linestyle="dashed", linewidth=0.5, label=r"$e_{\rm p,2}$")
    plt.plot(time[1, :], rand_rms[3, :], color="y", linestyle="dashed", linewidth=0.5, label=r"$e_{\rm p,3}$")
    plt.plot(time[1, :], rand_rms[4, :], color="r", label=r"$e_{\rm p,rms}$")
    plt.plot(time[1, :], rand_rms[5, :], color="b", label=r"$e_{\rm tr,rms}$")

plt.xscale("log")
plt.yscale("log")
plt.xlim([0.1, 10000])
# plt.ylim([0.03, 0.12])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)

plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('ecc', fontsize=25)
plt.grid(True)
plt.legend(loc="upper left", fontsize=15)

plt.tight_layout()

# plt.show()

plt.close()

#####################################################################
plt.figure(figsize=(10, 8), dpi=100)

if(N_p == 1):
    plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], rand_rms[5, :], color="r", label=r"$i_{\rm p}$")
    plt.plot(time[1, :], rand_rms[6, :], color="b", label=r"$i_{\rm tr,rms}$")
elif(N_p == 3):
    plt.title(r"$N_{\rm tr}=3000,M_{\rm tot}=30 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], rand_rms[6, :], color="c", linestyle="dashed", linewidth=0.5, label=r"$i_{\rm p,1}$")
    plt.plot(time[1, :], rand_rms[7, :], color="m", linestyle="dashed", linewidth=0.5, label=r"$i_{\rm p,2}$")
    plt.plot(time[1, :], rand_rms[8, :], color="y", linestyle="dashed", linewidth=0.5, label=r"$i_{\rm p,3}$")
    plt.plot(time[1, :], rand_rms[9, :], color="r", label=r"$i_{\rm p,rms}$")
    plt.plot(time[1, :], rand_rms[10, :], color="b", label=r"$i_{\rm tr,rms}$")


plt.xscale("log")
plt.yscale("log")
plt.xlim([0.1, 10000])
# plt.ylim([0.03, 0.06])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)

plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('inc [rad]', fontsize=25)
plt.grid(True)
plt.legend(loc="upper left", fontsize=15)


plt.tight_layout()

# plt.show()

plt.close()

#####################################################################

if (N_p == 1):
    np.savetxt(directory + "RMS_randall.dat", rand_rms.T, fmt="%.15e", delimiter="\t", newline="\n", header="time\tecc_1\tecc_p_rms\tecc_tr_rms\tinc_1\tinc_p_rms\tinc_tr_rms")
elif (N_p == 3):
    np.savetxt(directory + "RMS_randall.dat", rand_rms.T, fmt="%.15e", delimiter="\t", newline="\n", header="time\tecc_1\tecc_2\tecc_3\tecc_p_rms\tecc_tr_rms\tinc_1\tinc_2\tinc_3\tinc_p_rms\tinc_tr_rms")

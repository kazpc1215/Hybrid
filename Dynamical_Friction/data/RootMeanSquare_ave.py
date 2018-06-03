#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
# import matplotlib.animation as animation


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


def Mutual_Hill(x):
    return((1.0/x + 0.5*np.cbrt(2.0E-6))/(1.0/x - 0.5*np.cbrt(2.0E-6)))


######################################################################
path = "/Users/isoya.kazuhide/Dynamical_Friction/data/Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1//"

LINE = 10001
N_p = 1
N_tr = 1000

T_ave_range_ratio = 0.5

#####
r_min = 1.0 / Mutual_Hill(5)  # 面密度計算用.
r_max = 1.0 * Mutual_Hill(5)
area = np.pi * (r_max*r_max - r_min*r_min)
print(r_min, r_max, area)
mass_tot = np.zeros(LINE, dtype=float)
sigma = np.zeros(LINE, dtype=float)
num = np.zeros(LINE, dtype=int)
#####


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

#####
ecc_2 = np.zeros(LINE, dtype=float)
for n in range(1, N_p+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_p
ecc_rms_p = np.sqrt(ecc_2_mean)


ecc_2_mean_timeave = np.zeros(LINE, dtype=float)
for n in range(1, LINE):

    if(n*(1.0-T_ave_range_ratio) >= 0 and n*(1.0+T_ave_range_ratio) <= LINE-1):
        if((n*(1.0-T_ave_range_ratio)).is_integer()):  # int(t_min)に+1がいらなくなる.
            # print("integer!")
            ecc_2_mean_timeave[n] = np.sum(ecc_2_mean[int(n*(1.0-T_ave_range_ratio)):int(n*(1.0+T_ave_range_ratio))+1]) / (int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio))+1)
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio))+1)
            # print(ecc_2_mean[int(n*(1.0-T_ave_range_ratio)):int(n*(1.0+T_ave_range_ratio))+1], "\n", ecc_2_mean_timeave[n])
        else:
            ecc_2_mean_timeave[n] = np.sum(ecc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:int(n*(1.0+T_ave_range_ratio))+1]) / (int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio)))
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio)))
            # print(ecc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:int(n*(1.0+T_ave_range_ratio))+1], "\n", ecc_2_mean_timeave[n])

    elif(n*(1.0+T_ave_range_ratio) > LINE-1):
        if((n*(1.0-T_ave_range_ratio)).is_integer()):  # int(t_min)に+1がいらなくなる.
            # print("integer!")
            ecc_2_mean_timeave[n] = np.sum(ecc_2_mean[int(n*(1.0-T_ave_range_ratio)):LINE]) / (LINE-int(n*(1.0-T_ave_range_ratio)))
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", LINE-int(n*(1.0-T_ave_range_ratio)))
            # print(ecc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:LINE], "\n", ecc_2_mean_timeave[n])
        else:
            ecc_2_mean_timeave[n] = np.sum(ecc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:LINE]) / (LINE-int(n*(1.0-T_ave_range_ratio))-1)
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", LINE-int(n*(1.0-T_ave_range_ratio))-1)
            # print(ecc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:LINE], "\n", ecc_2_mean_timeave[n])

    else:
        print("time average error")
ecc_rms_p_timeave = np.sqrt(ecc_2_mean_timeave)
#####


#####
inc_2 = np.zeros(LINE, dtype=float)
for n in range(1, N_p+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_p
inc_rms_p = np.sqrt(inc_2_mean)


inc_2_mean_timeave = np.zeros(LINE, dtype=float)
for n in range(1, LINE):

    if(n*(1.0-T_ave_range_ratio) >= 0 and n*(1.0+T_ave_range_ratio) <= LINE-1):
        if((n*(1.0-T_ave_range_ratio)).is_integer()):  # int(t_min)に+1がいらなくなる.
            # print("integer!")
            inc_2_mean_timeave[n] = np.sum(inc_2_mean[int(n*(1.0-T_ave_range_ratio)):int(n*(1.0+T_ave_range_ratio))+1]) / (int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio))+1)
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio))+1)
            # print(inc_2_mean[int(n*(1.0-T_ave_range_ratio)):int(n*(1.0+T_ave_range_ratio))+1], "\n", inc_2_mean_timeave[n])
        else:
            inc_2_mean_timeave[n] = np.sum(inc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:int(n*(1.0+T_ave_range_ratio))+1]) / (int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio)))
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", int(n*(1.0+T_ave_range_ratio))-int(n*(1.0-T_ave_range_ratio)))
            # print(inc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:int(n*(1.0+T_ave_range_ratio))+1], "\n", inc_2_mean_timeave[n])

    elif(n*(1.0+T_ave_range_ratio) > LINE-1):
        if((n*(1.0-T_ave_range_ratio)).is_integer()):  # int(t_min)に+1がいらなくなる.
            # print("integer!")
            inc_2_mean_timeave[n] = np.sum(inc_2_mean[int(n*(1.0-T_ave_range_ratio)):LINE]) / (LINE-int(n*(1.0-T_ave_range_ratio)))
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", LINE-int(n*(1.0-T_ave_range_ratio)))
            # print(inc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:LINE], "\n", inc_2_mean_timeave[n])
        else:
            inc_2_mean_timeave[n] = np.sum(inc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:LINE]) / (LINE-int(n*(1.0-T_ave_range_ratio))-1)
            # print("t_min = ", n*(1.0-T_ave_range_ratio), "t_max = ", n*(1.0+T_ave_range_ratio), "size = ", LINE-int(n*(1.0-T_ave_range_ratio))-1)
            # print(inc_2_mean[int(n*(1.0-T_ave_range_ratio))+1:LINE], "\n", inc_2_mean_timeave[n])

    else:
        print("time average error")
inc_rms_p_timeave = np.sqrt(inc_2_mean_timeave)
#####


################################


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
    mass[n, :] = arr[:, 9]
    print(n, time[n, 1], ecc[n, 1], inc[n, 1])

#####
ecc_2 = np.zeros(LINE, dtype=float)
for n in range(N_p+1, N_p+N_tr+1):
    ecc_2 = ecc_2 + ecc[n, :] * ecc[n, :]
ecc_2_mean = ecc_2 / N_tr
ecc_rms_tr = np.sqrt(ecc_2_mean)
#####


#####
inc_2 = np.zeros(LINE, dtype=float)
for n in range(N_p+1, N_p+N_tr+1):
    inc_2 = inc_2 + inc[n, :] * inc[n, :]
inc_2_mean = inc_2 / N_tr
inc_rms_tr = np.sqrt(inc_2_mean)
#####


for T in range(0, LINE):
    for n in range(N_p+1, N_p+N_tr+1):
        if(axis[n, T] > r_min and axis[n, T] < r_max):
            mass_tot[T] += mass[n, T]
            num[T] += 1
    sigma[T] = mass_tot[T] / area
    print(T, mass_tot[T], sigma[T], num[T])

######################################################################
plt.figure(figsize=(10, 8), dpi=100)

if(N_p == 1):
    plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], ecc_rms_p, color="r", label=r"$e_{\rm p}$")
    plt.plot(time[1, :], ecc_rms_p_timeave, color="g", label=r"$e_{\rm p,timeave}$")
elif(N_p == 3):
    plt.title(r"$N_{\rm tr}=3000,M_{\rm tot}=30 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], ecc[1, :], color="c", linestyle="dashed", linewidth=0.5, label=r"$e_{\rm p,1}$")
    plt.plot(time[1, :], ecc[2, :], color="m", linestyle="dashed", linewidth=0.5, label=r"$e_{\rm p,2}$")
    plt.plot(time[1, :], ecc[3, :], color="y", linestyle="dashed", linewidth=0.5, label=r"$e_{\rm p,3}$")
    plt.plot(time[1, :], ecc_rms_p, color="g", label=r"$e_{\rm p,rms}$")
    plt.plot(time[1, :], ecc_rms_p_timeave, color="r", label=r"$e_{\rm p,rms,timeave}$")
plt.plot(time[1, :], ecc_rms_tr, color="b", label=r"$e_{\rm tr,rms}$")

plt.xscale("log")
plt.yscale("log")
plt.xlim([1, LINE-1])
# plt.ylim([0.03, 0.12])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)

plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('ecc', fontsize=25)
plt.grid(True)
plt.legend(loc="upper left", fontsize=15)

plt.tight_layout()

plt.show()

plt.close()

#####################################################################
plt.figure(figsize=(10, 8), dpi=100)

if(N_p == 1):
    plt.title(r"$N_{\rm tr}=1000,M_{\rm tot}=10 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], inc_rms_p, color="r", label=r"$i_{\rm p}$")
    plt.plot(time[1, :], inc_rms_p_timeave, color="g", label=r"$i_{\rm p,timeave}$")
elif(N_p == 3):
    plt.title(r"$N_{\rm tr}=3000,M_{\rm tot}=30 {\rm M_{\oplus}}$", fontsize=18)
    plt.plot(time[1, :], inc[1, :], color="c", linestyle="dashed", linewidth=0.5, label=r"$i_{\rm p,1}$")
    plt.plot(time[1, :], inc[2, :], color="m", linestyle="dashed", linewidth=0.5, label=r"$i_{\rm p,2}$")
    plt.plot(time[1, :], inc[3, :], color="y", linestyle="dashed", linewidth=0.5, label=r"$i_{\rm p,3}$")
    plt.plot(time[1, :], inc_rms_p, color="g", label=r"$i_{\rm p,rms}$")
    plt.plot(time[1, :], inc_rms_p_timeave, color="r", label=r"$i_{\rm p,rms,timeave}$")
plt.plot(time[1, :], inc_rms_tr, color="b", label=r"$i_{\rm tr,rms}$")


plt.xscale("log")
plt.yscale("log")
plt.xlim([1, LINE-1])
# plt.ylim([0.03, 0.06])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)

plt.xlabel('time[yr]', fontsize=25)
plt.ylabel('inc [rad]', fontsize=25)
plt.grid(True)
plt.legend(loc="upper left", fontsize=15)


plt.tight_layout()

plt.show()

plt.close()

#####################################################################

if(N_p == 1):
    arr2 = np.empty([LINE, 7], dtype=float)
    arr2[:, 0] = time[1, :]
    arr2[:, 1] = ecc_rms_p
    arr2[:, 2] = inc_rms_p
    arr2[:, 3] = ecc_rms_p_timeave
    arr2[:, 4] = inc_rms_p_timeave
    arr2[:, 5] = ecc_rms_tr
    arr2[:, 6] = inc_rms_tr
    np.savetxt(path + "RMS_Ntr1000.dat", arr2, fmt="%.15e", delimiter="\t", newline="\n", header="time\tecc_p\tinc_p\tecc_p_ave\tinc_p_ave\tecc_rms_tr\tinc_rms_tr")

elif(N_p == 3):
    arr2 = np.empty([LINE, 13], dtype=float)
    arr2[:, 0] = time[1, :]
    arr2[:, 1] = ecc_rms_p
    arr2[:, 2] = inc_rms_p
    arr2[:, 3] = ecc_rms_p_timeave
    arr2[:, 4] = inc_rms_p_timeave
    arr2[:, 5] = ecc_rms_tr
    arr2[:, 6] = inc_rms_tr
    arr2[:, 7] = ecc[1, :]
    arr2[:, 8] = ecc[2, :]
    arr2[:, 9] = ecc[3, :]
    arr2[:, 10] = inc[1, :]
    arr2[:, 11] = inc[2, :]
    arr2[:, 12] = inc[3, :]
    np.savetxt(path + "RMS_Ntr3000.dat", arr2, fmt="%.15e", delimiter="\t", newline="\n", header="time\tecc_rms_p\tinc_rms_p\tecc_rms_p_ave\tinc_rms_p_ave\tecc_rms_tr\tinc_rms_tr\tecc_p=1\tecc_p=2\tecc_p=3\tinc_p=1\tinc_p=2\tinc_p=3")

arr3 = np.empty([LINE, 6], dtype=float)
arr3[:, 0] = time[1, :]
arr3[:, 1] = mass_tot
arr3[:, 2] = sigma
arr3[:, 3] = sigma[0]
arr3[:, 4] = num
arr3[:, 5] = num[0]
np.savetxt(path + "sigma.dat", arr3, fmt="%.15e", delimiter="\t", newline="\n", header="time\tmass_tot\tsigma\tsigma_0\tnum\tnum_0")

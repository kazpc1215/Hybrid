#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
# import matplotlib.animation as animation


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


######################################################################
# path = "/Users/isoya.kazuhide/Dynamical_Friction/data/"

# directory = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/"
# directory = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/"
# directory = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_acc/"
# directory = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_acc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_noacc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_acc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_noacc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_acc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_noacc/"
# directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_acc/"
directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_noacc/"


N_p = 3
N_tr = 3000

if(N_p == 1):
    LINE = 42  # 10000yr
    SUBDIR_NUM = 40
elif(N_p == 3):
    LINE = 34  # 1000yr
    SUBDIR_NUM = 13


time = np.empty([SUBDIR_NUM, LINE], dtype=float)  # (ファイル番号,行数)
mass_all = np.empty([SUBDIR_NUM, LINE], dtype=float)
mass_center = np.empty([SUBDIR_NUM, LINE], dtype=float)
sigma_center = np.empty([SUBDIR_NUM, LINE], dtype=float)
n_center = np.empty([SUBDIR_NUM, LINE], dtype=float)
norm_mass_all = np.empty([SUBDIR_NUM, LINE], dtype=float)
norm_mass_center = np.empty([SUBDIR_NUM, LINE], dtype=float)
norm_sigma_center = np.empty([SUBDIR_NUM, LINE], dtype=float)
norm_n_center = np.empty([SUBDIR_NUM, LINE], dtype=float)
#####


for subnum in range(1, SUBDIR_NUM+1):
    subdirectory = "rand%02d/" % subnum

    arr = np.genfromtxt(directory + subdirectory + "Sigma_dep.dat", dtype=np.float, delimiter="\t")
    print(arr.shape)

    time[subnum-1, :] = arr[:, 0]
    mass_all[subnum-1, :] = arr[:, 1]
    mass_center[subnum-1, :] = arr[:, 2]
    sigma_center[subnum-1, :] = arr[:, 3]
    n_center[subnum-1, :] = arr[:, 4]

    print(subnum, time[subnum-1, 0], mass_center[subnum-1, 0], sigma_center[subnum-1, 0])

for T in range(LINE):
    norm_mass_all[:, T] = mass_all[:, T] / mass_all[:, 0]  # 初期値で規格化
    norm_mass_center[:, T] = mass_center[:, T] / mass_center[:, 0]
    norm_sigma_center[:, T] = sigma_center[:, T] / sigma_center[:, 0]
    norm_n_center[:, T] = n_center[:, T] / n_center[:, 0]

    print(subnum, time[subnum-1, T], mass_center[subnum-1, T], sigma_center[subnum-1, T])

######################################################################

rand_error = np.zeros([9, LINE], dtype=float)
rand_error[0, :] = time[0, :]
rand_error[1, :] = norm_mass_all.mean(axis=0)
rand_error[2, :] = norm_mass_all.std(axis=0, ddof=1)
rand_error[3, :] = norm_mass_center.mean(axis=0)
rand_error[4, :] = norm_mass_center.std(axis=0, ddof=1)
rand_error[5, :] = norm_sigma_center.mean(axis=0)
rand_error[6, :] = norm_sigma_center.std(axis=0, ddof=1)
rand_error[7, :] = norm_n_center.mean(axis=0)
rand_error[8, :] = norm_n_center.std(axis=0, ddof=1)

######################################################################

plt.figure(figsize=(10, 8), dpi=100)
plt.plot(time[0, :], rand_error[5, :], color="r", label=r"$\Sigma/\Sigma_0$")
plt.errorbar(time[0, :], rand_error[5, :], yerr=rand_error[6, :], fmt=".", color="r")
plt.yscale("log")
plt.xscale("log")
plt.legend()
plt.show()
plt.close()

#####################################################################

np.savetxt(directory + "Sigma_randall.dat", rand_error.T, fmt="%.15e", delimiter="\t", newline="\n",
           header="time\tmass_tot_all\tmass_tot_all_error\tmass_tot_center\tmass_tot_center_error\tsigma_center\tsigma_center_error\tn_center\tn_center_error\t(normalized)")

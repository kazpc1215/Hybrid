#!/usr/bin/env python
# -*- coding: utf-8 -*-

# import matplotlib.pyplot as plt
import numpy as np
from scipy import integrate


def integral(x, Beta, Tau, t):
    Lambda = Beta + 1.5
    return x / (1.0 + x**(- Lambda) * t / Tau)

def hosei(da, Beta, Tau, t):
    return 2.0 * (1.0 + t / Tau) / ((1.0 + 0.5 * da)**2 - (1.0 - 0.5 * da)**2) * integrate.quad(integral, 1.0-0.5*da, 1.0+0.5*da, args=(Beta, Tau, t))[0]


"""
###
t_list = np.linspace(0.0, 1000.0, 10001)
data = np.empty([10001, 2], dtype=np.float)
for i in range(10001):
    data[i, 0] = t_list[i]
    data[i, 1] = hosei(0.1, 1.0, 1.233830, t_list[i])

np.savetxt("hosei_da0.1_Beta1.0_Tau1.233830_t.dat", data, fmt="%.15e", delimiter="\t", newline="\n", header="time\thosei")
###

###
da_list = np.linspace(0.0, 1.0, 10001)
data = np.empty([10001, 2], dtype=np.float)
for i in range(10001):
    data[i, 0] = da_list[i]
    data[i, 1] = hosei(da_list[i], 1.0, 1.233830, 100.0)

np.savetxt("hosei_Beta1.0_Tau1.233830_t100.0_da.dat", data, fmt="%.15e", delimiter="\t", newline="\n", header="da\thosei")
###

###
Beta_list = np.linspace(-2.0, 2.0, 10001)
data = np.empty([10001, 2], dtype=np.float)
for i in range(10001):
    data[i, 0] = Beta_list[i5
    data[i, 1] = hosei(0.1, Beta_list[i], 1.233830, 100.0)

np.savetxt("hosei_da0.1_Tau1.233830_t100.0_Beta.dat", data, fmt="%.15e", delimiter="\t", newline="\n", header="Beta\thosei")
###
"""


######################################################################
# ## ecc 1E-2 ###


# directory = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta0.125pi"
# directory = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi"
# directory = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta0.125pi"
directory = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi"

outputfile = directory + "_sigma_error.dat"
# directory_list = ["Nc1E2_", "Nc2E2_", "Nc5E2_", "Nc1E3_", "Nc2E3_"]
directory_list = ["Nc1E1_", "Nc2E1_", "Nc5E1_", "Nc1E2_", "Nc2E2_", "Nc5E2_", "Nc1E3_", "Nc2E3_"]


LINE = 26

RAND = 40

DELTA_AXIS = 0.05
BETA = 1.0

with open(outputfile, mode="w") as f:
    print("#n_neighbor_mean\tn_neighbor_error\tsigma_error_mean\tsigma_error_std", file=f)

for dirname in directory_list:

    print(dirname)

    n_neighbor_mean = np.empty(RAND+1, dtype=np.float)
    n_neighbor_error = np.empty(RAND+1, dtype=np.float)
    sigma_error = np.empty(([LINE, RAND+1]), dtype=np.float)
    sigma_rand = np.empty([LINE, RAND+1], dtype=np.float)
    sigma_mean = np.empty([LINE, 6], dtype=np.float)

    for rand in range(1, RAND+1):

        subdirectory = "/rand%02d/" % rand

        ########################################
        arr1 = np.genfromtxt(dirname + directory + subdirectory + "Posi_Mass_25.dat", dtype=np.float, delimiter="\t")
        # print(rand, arr1.shape)

        n_neighbor = arr1[:, 12]
        n_neighbor_mean[rand] = n_neighbor.mean(axis=0)
        n_neighbor_error[rand] = n_neighbor.std(axis=0, ddof=1)

        ########################################
        arr2 = np.genfromtxt(dirname + directory + subdirectory + "Sigma_dep.dat", dtype=np.float, delimiter="\t")
        # print(rand, arr2.shape)

        ########################################
        arr3 = np.genfromtxt(dirname + directory + subdirectory + "Tau_dep.dat", dtype=np.float, delimiter="\t")
        print(rand, arr3)

        for i in range(LINE):
            sigma_error[i, rand] = abs(arr2[i, 3] / arr2[0, 3] / hosei(DELTA_AXIS, BETA, arr3, arr2[i, 0]) * (1.0 + arr2[i, 0] / arr3) - 1)

        sigma_rand[:, rand] = arr2[:, 3] / arr2[0, 3]

    # print(n_neighbor[:, 1:].mean(axis=0))
    # print(n_neighbor[:, 1:].std(axis=0, ddof=1))
    # print((n_neighbor[:, 1:].mean(axis=0)).mean(axis=0))

    square = n_neighbor_error[1:] * n_neighbor_error[1:]
    mean_square = square.mean(axis=0)
    root_mean_square = np.sqrt(mean_square)

    # print(root_mean_square)

    print(sigma_error[25, 1:RAND+1])
    # print(sigma_error[25, 1:5].mean(axis=0))
    # print(sigma_error[25, 1:5].min())
    # print(sigma_error[25, 1:5].max())

    print(sigma_rand[25, 1:RAND+1])

    sigma_mean[:, 0] = arr2[:, 0]
    sigma_mean[:, 1] = sigma_rand[:, 1:RAND+1].mean(axis=1)
    sigma_mean[:, 2] = sigma_rand[:, 1:RAND+1].min(axis=1)
    sigma_mean[:, 3] = sigma_rand[:, 1:RAND+1].max(axis=1)
    sigma_mean[:, 4] = sigma_rand[:, 1:RAND+1].std(axis=1, ddof=1)
    for T in range(LINE):
        print(
            "hosei at ",
            arr2[T, 0],
            " yr = ",
            hosei(DELTA_AXIS, BETA, arr3, arr2[T, 0])
        )
        sigma_mean[T, 5] = hosei(DELTA_AXIS, BETA, arr3, arr2[T, 0]) / (1.0 + arr2[T, 0] / arr3)

    with open(outputfile, mode="a") as f:
        print(
            n_neighbor_mean[1:RAND+1].mean(axis=0),
            root_mean_square,
            sigma_error[25, 1:RAND+1].mean(axis=0),
            sigma_error[25, 1:RAND+1].std(axis=0, ddof=1),
            file=f, sep="\t"
        )

    np.savetxt(
        dirname + directory + "/Sigma_mean.dat",
        sigma_mean,
        fmt="%.15e",
        delimiter="\t",
        newline="\n",
        header="time\tsigma_mean\tsigma_min\tsigma_max\tsigma_std\tanalytic"
    )

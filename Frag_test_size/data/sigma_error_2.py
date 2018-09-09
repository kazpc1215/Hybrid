#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

def hosei(da, Beta):
    Lambda = -2.0 * Beta - 1.5
    return (2.0+Lambda) / (2.0-Beta) / ((1.0+0.5*da)**(2.0+Lambda) - (1.0-0.5*da)**(2.0+Lambda)) * ((1.0+0.5*da)**(2.0-Beta) - (1.0-0.5*da)**(2.0-Beta))

######################################################################
### ecc 1E-2 ###
# directory = "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag"
directory = "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag"

# outputfile = directory + "_dtheta0.125pi_sigma_error.dat"
# directory_list = ["_dr2E-3_dtheta0.125pi", "_dr4E-3_dtheta0.125pi", "_dr8E-3_dtheta0.125pi", "_dr2E-2_dtheta0.125pi", "_dr4E-2_dtheta0.125pi"]

outputfile = directory + "_dr4E-3_sigma_error.dat"
directory_list = ["_dr4E-3_dtheta0.0625pi", "_dr4E-3_dtheta0.125pi", "_dr4E-3_dtheta0.25pi", "_dr4E-3_dtheta0.5pi", "_dr4E-3_dtheta1.0pi"]


LINE = 26

RAND = 40


with open(outputfile, mode="w") as f:
    print("#n_neighbor_mean\tn_neighbor_error\tsigma_error_mean\tsigma_error_min\tsigma_error_max", file=f)

for dirname in directory_list:

    print(dirname)

    n_neighbor_mean = np.empty(RAND+1, dtype=np.float)
    n_neighbor_error = np.empty(RAND+1, dtype=np.float)
    sigma_error = np.empty(([LINE, RAND+1]), dtype=np.float)

    for rand in range(1, RAND+1):

        subdirectory = "/rand%02d/" % rand

        ########################################
        arr1 = np.genfromtxt(directory + dirname + subdirectory + "Posi_Mass_25.dat", dtype=np.float, delimiter="\t")
        # print(rand, arr1.shape)

        n_neighbor = arr1[:, 12]
        n_neighbor_mean[rand] = n_neighbor.mean(axis=0)
        n_neighbor_error[rand] = n_neighbor.std(axis=0, ddof=1)

        ########################################
        arr2 = np.genfromtxt(directory + dirname + subdirectory + "Sigma_dep.dat", dtype=np.float, delimiter="\t")
        # print(rand, arr2.shape)

        ########################################
        arr3 = np.genfromtxt(directory + dirname + subdirectory + "Tau_dep.dat", dtype=np.float, delimiter="\t")
        # print(rand, arr3.shape, arr3, hosei(0.1, 1.0), arr3 * hosei(0.1, 1.0))

        # sigma_error[:, rand] = abs(arr2[:, 3] / arr2[0, 3] * (1.0 + arr2[:, 0] / arr3) - 1)
        sigma_error[:, rand] = abs(arr2[:, 3] / arr2[0, 3] * (1.0 + arr2[:, 0] / (arr3 * hosei(0.1, 1.0))) - 1)

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

    with open(outputfile, mode="a") as f:
        print(n_neighbor_mean[1:RAND+1].mean(axis=0), root_mean_square, sigma_error[25, 1:RAND+1].mean(axis=0), sigma_error[25, 1:RAND+1].min(), sigma_error[25, 1:RAND+1].max(), file=f, sep="\t")

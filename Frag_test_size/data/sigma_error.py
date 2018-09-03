#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np


######################################################################
### ecc 1E-2 ###
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_OmegaZero_frag_drmin5E-3_dthetamin0.125pi"
# tau_dep = [1.336324e+02, 1.286343e+02, 1.393310e+02, 1.296552e+02]

# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi"
# tau_dep = [1.336324e+02, 1.286343e+02, 1.393310e+02, 1.296552e+02]

# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Uniform_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi"
# tau_dep = [1.308233e+02, 1.340436e+02, 1.301718e+02, 1.313492e+02]

### ecc 3E-2 ###
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_OmegaZero_frag_drmin5E-3_dthetamin0.125pi"
# tau_dep = [2.966639e+01, 2.910776e+01, 3.137791e+01, 2.960658e+01]

# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi"
# tau_dep = [2.966639e+01, 2.910776e+01, 3.137791e+01, 2.960658e+01]

# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Uniform_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi"
# tau_dep = [2.960658e+01, 2.978674e+01, 2.951731e+01, 2.931110e+01]

### ecc 5E-3 ###
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_OmegaZero_frag_drmin5E-3_dthetamin0.125pi"   # <-----
# tau_dep = [1.534533e+01, 1.458263e+01, 1.547482e+01, 1.478844e+01]

# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_frag_drmin1E-3_dthetamin0.125pi"
# directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi"   # <-----
# tau_dep = [1.534533e+01, 1.458263e+01, 1.547482e+01, 1.478844e+01]

#directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Uniform_frag_drmin1E-3_dthetamin0.125pi"
directory = "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi"
tau_dep = [1.465548e+01, 1.446758e+01, 1.493903e+01, 1.469953e+01]


outputfile = directory + "_sigma_error.dat"


LINE = 26

N = 3000

DR_MAX = 5
DTHETA_MAX = 8


with open(outputfile, mode="w") as f:
            print("#dr\tdtheta\tn_neighbor_mean\tn_neighbor_error\tsigma_error_mean\tsigma_error_min\tsigma_error_max", file=f)

for dr in range(1, DR_MAX+1):
    for dtheta in range(1, DTHETA_MAX+1):

        print(dr, dtheta)

        n_neighbor = np.empty(([N, 5]), dtype=np.float)

        sigma_error = np.empty(([LINE, 5]), dtype=np.float)

        for rand in range(1, 5):

            subdirectory = "dr%02d" % dr + "_dtheta%02d/" % dtheta

            ########################################
            arr1 = np.genfromtxt(directory + "_rand%02d/" % rand + subdirectory + "Posi_Mass_25.dat", dtype=np.float, delimiter="\t")
            # print(rand, arr1.shape)

            n_neighbor[:, rand] = arr1[:, 12]

            ########################################
            arr2 = np.genfromtxt(directory + "_rand%02d/" % rand + subdirectory + "Sigma_dep.dat", dtype=np.float, delimiter="\t")
            # print(rand, arr2.shape)

            sigma_error[:, rand] = abs(arr2[:, 3] / arr2[0, 3] * (1.0 + arr2[:, 0] / tau_dep[rand-1]) - 1)

        # print(n_neighbor[:, 1:].mean(axis=0))
        # print(n_neighbor[:, 1:].std(axis=0, ddof=1))
        # print((n_neighbor[:, 1:].mean(axis=0)).mean(axis=0))

        square = n_neighbor[:, 1:].std(axis=0, ddof=1) * n_neighbor[:, 1:].std(axis=0, ddof=1)
        mean_square = square.mean(axis=0)
        root_mean_square = np.sqrt(mean_square)

        # print(root_mean_square)

        # print(sigma_error[25, 1:5])
        # print(sigma_error[25, 1:5].mean(axis=0))
        # print(sigma_error[25, 1:5].min())
        # print(sigma_error[25, 1:5].max())

        with open(outputfile, mode="a") as f:
            print(dr, dtheta, (n_neighbor[:, 1:].mean(axis=0)).mean(axis=0), root_mean_square, sigma_error[25, 1:5].mean(axis=0), sigma_error[25, 1:5].min(), sigma_error[25, 1:5].max(), file=f, sep="\t")

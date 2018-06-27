#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm
import numpy as np
from scipy.interpolate import griddata

def delta_axis(ratio):
    return (1.0/ratio + 0.5*np.cbrt(2.0E-6))/(1.0/ratio - 0.5*np.cbrt(2.0E-6))


######################################################################
# path = "/Users/isoya.kazuhide/Dynamical_Friction/data/"
directory = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/"


N_p = 3
N_tr = 3000


if(N_p == 1):
    LINE = 42  # 10000yr
    SUBDIR_NUM = 40
elif(N_p == 3):
    LINE = 34  # 1000yr
    SUBDIR_NUM = 13


for subnum in range(1, SUBDIR_NUM+1):
    subdirectory = "rand%02d/" % subnum

    time = np.empty([N_p+N_tr, LINE], dtype=float)  # (ファイル番号,行数)
    num = np.empty([N_p+N_tr, LINE], dtype=float)
    x = np.empty([N_p+N_tr, LINE], dtype=float)
    y = np.empty([N_p+N_tr, LINE], dtype=float)
    z = np.empty([N_p+N_tr, LINE], dtype=float)
    r_3d = np.empty([N_p+N_tr, LINE], dtype=float)
    r_2d = np.empty([N_p+N_tr, LINE], dtype=float)
    mass = np.empty([N_p+N_tr, LINE], dtype=float)
    sigma = np.empty([N_p+N_tr, LINE], dtype=float)

    # radius = np.empty([N_p+N_tr], dtype=float)
    # theta = np.empty([N_p+N_tr], dtype=float)

    for T in range(LINE):
        arr = np.genfromtxt(directory + subdirectory + "Posi_Mass_%02d.dat" % T, dtype=np.float, delimiter="\t")
        if(N_p+N_tr - arr.shape[0] > 0):
            print(T, "padding")
            arr = np.pad(arr, [(0, N_p+N_tr - arr.shape[0]), (0, 0)], 'constant', constant_values=0.0)

        time[:, T] = arr[:, 0]
        num[:, T] = arr[:, 1]
        x[:, T] = arr[:, 2]
        y[:, T] = arr[:, 3]
        z[:, T] = arr[:, 4]
        r_3d[:, T] = arr[:, 5]
        r_2d[:, T] = arr[:, 6]
        mass[:, T] = arr[:, 7]
        sigma[:, T] = arr[:, 10]
        print(T, int(num[0, T]), time[0, T], x[0, T])

        fig = plt.figure(figsize=(8, 6), dpi=100)

        """
        ax = fig.add_subplot(1, 1, 1, aspect='equal')
        ax.set_xlim([-2, 2])
        ax.set_ylim([-2, 2])
        ax.set_xlabel('x [AU]', fontsize=20)
        ax.set_ylabel('y [AU]', fontsize=20)
        """

        ax = fig.add_subplot(111, projection="polar")
        # ax = fig.add_subplot(111)
        ax.title.set_text('%.3e [yr]' % time[1, T])
        ax.title.set_fontsize(15)

        fig.subplots_adjust(right=0.8)

        # cm = plt.cm.get_cmap('rainbow')

        RADIUS = np.linspace(0.0, 1.5, 500)
        THETA = np.linspace(-np.pi, np.pi, 500)

        radius = np.sqrt(x[:, T]**2 + y[:, T]**2)

        if(N_p == 1):
            radius = np.append(radius, np.random.uniform(0.0, 1.0/delta_axis(5.0), 10000))
            radius = np.append(radius, np.random.uniform(delta_axis(5.0), 1.5, 5000))
        elif(N_p == 3):
            radius = np.append(radius, np.random.uniform(0.0, 1.0/delta_axis(10.0)/delta_axis(5.0), 10000))
            radius = np.append(radius, np.random.uniform(delta_axis(10.0)*delta_axis(5.0), 1.5, 5000))

        theta = np.arctan2(y[:, T], x[:, T])
        theta = np.append(theta, np.random.uniform(-np.pi-0.1, np.pi+0.1, 15000))

        sigma_grid = sigma[:, T]*8888888.88888889
        sigma_grid = np.append(sigma_grid, [0.0 for i in range(15000)])

        RADIUS, THETA = np.meshgrid(RADIUS, THETA)

        Z = griddata((radius[N_p:], theta[N_p:]), sigma_grid[N_p:], (RADIUS, THETA), method="linear")
        Z[np.isnan(Z)] = 0.0
        Z_convert = np.where(Z < 0.0, 0.0, Z)

        # im = ax.scatter(theta[3:], radius[3:], s=1, c=mass[3:, T] * 2E8, vmin=1.0, vmax=6.0, cmap=cm, label='Tracer')

        # im = ax.contourf(THETA, RADIUS, Z, levels=np.linspace(0.0, 3.0, 100), cmap=cm)
        # im = ax.contourf(THETA, RADIUS, Z_convert, cmap="jet")
        im = ax.contourf(THETA, RADIUS, Z_convert, levels=np.linspace(0.0, np.amax(Z), 100), cmap="jet")
        # im = ax.contourf(THETA, RADIUS, Z_convert, norm=LogNorm(), levels=[1E-1, 1E0, 1E1, 1E2, 1E3], cmap="jet")

        # ax.scatter(0, 0, c='k', marker='*', s=50, label='Star')
        if(N_p == 1):
            ax.scatter(theta[0], radius[0], c='k', marker='1', s=50, label='Planet')
        elif(N_p == 3):
            ax.scatter(theta[0], radius[0], c='k', marker='1', s=50, label='Planet1')
            ax.scatter(theta[1], radius[1], c='k', marker='2', s=50, label='Planet2')
            ax.scatter(theta[2], radius[2], c='k', marker='3', s=50, label='Planet3')
        # ax.scatter(theta[3:], radius[3:], c='k', marker='.', s=1, label='tracer')

        ax.set_rlim(0, 1.5)
        ax.set_rticks([0.5, 1.0, 1.5])
        ax.set_thetalim(0, 2*np.pi)
        ax.set_xticks(np.pi/180. * np.linspace(0, 360, 4, endpoint=False))
        cbar_ax = fig.add_axes([0.85, 0.15, 0.03, 0.7])
        fig.colorbar(im, cax=cbar_ax, ticks=np.linspace(0.0, np.amax(Z), 10))
        # fig.colorbar(im, cax=cbar_ax)
        # cbar_ax.set_ylabel(r'mass $[10^{25} \rm g]$', fontsize=20)
        cbar_ax.set_ylabel(r'$\Sigma \ \rm [g/cm^2]$', fontsize=20)

        # plt.tight_layout()
        ax.legend()
        filename = "../image/" + directory + subdirectory + "Sigma_T%02d.png" % T
        plt.savefig(filename, format="png", dpi=100)
        # plt.show()
        plt.close()

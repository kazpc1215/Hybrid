#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt

import numpy as np
# from mpl_toolkits.mplot3d import Axes3D
# import matplotlib.animation as animation


# from matplotlib.font_manager import FontProperties
# fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


filename = "/Users/isoya.kazuhide/Master1/Hybrid/Ejection/data/Ejection_backcone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_1000yr/Posi_Mass.dat"

f = open(filename, mode='r')  # file read
lines = f.readlines()[1:]  # 2行目から読み込み
# lines = lines[0:1788400]
f.close()

nline = 1001
nspace = 2
ntotalline = nline + nspace
nblock = len(lines) / ntotalline  # number of output
# nblock = 6

time = np.zeros((nblock, nline))  # time, space
number = np.zeros((nblock, nline))  # time, space
x = np.zeros((nblock, nline))  # time, space
y = np.zeros((nblock, nline))  # time, space
z = np.zeros((nblock, nline))  # time, space
abs_r = np.zeros((nblock, nline))  # time, space
abs_r_xy = np.zeros((nblock, nline))  # time, space
mass = np.zeros((nblock, nline))  # time, space
delta_r = np.zeros((nblock, nline))  # time, space
sigma = np.zeros((nblock, nline))  # time, space
n_s = np.zeros((nblock, nline))  # time, space
neighbornumber = np.zeros((nblock, nline))  # time, space


for nb in range(nblock):
    print nb
    n1 = ntotalline * nb
    n2 = ntotalline * (nb + 1) - 1
    print n1, n2
    step = 0
    for line in lines[n1:n2 + 1 - nspace]:
        column = line[:-1].split('\t')

        time[nb, step] = float(column[0])  # mojiretsu =>float
        number[nb, step] = int(column[1])
        x[nb, step] = float(column[2])
        y[nb, step] = float(column[3])
        z[nb, step] = float(column[4])
        abs_r[nb, step] = float(column[5])
        abs_r_xy[nb, step] = float(column[6])
        mass[nb, step] = float(column[7])
        delta_r[nb, step] = float(column[8])
        sigma[nb, step] = float(column[9])
        n_s[nb, step] = float(column[10])
        neighbornumber[nb, step] = float(column[11])
        #  print column
        step = step + 1

fig = plt.figure(figsize=(8, 6), dpi=100)

#  サブプロットを追加
ax_common = fig.add_subplot(1, 1, 1)
ax_common.spines['top'].set_color('none')
ax_common.spines['bottom'].set_color('none')
ax_common.spines['left'].set_color('none')
ax_common.spines['right'].set_color('none')
ax_common.tick_params(labelcolor='w', top='off', bottom='off', left='off', right='off')

ax_common.set_xlabel('x [AU]', fontsize=20)
ax_common.set_ylabel('y [AU]', fontsize=20)
#  ax_common.title.set_text('The evolution of the debris ejected at (1,0).')
#  ax_common.title.set_fontsize(15)

ax4 = fig.add_subplot(2, 2, 4, aspect='equal')
ax1 = fig.add_subplot(2, 2, 1, aspect='equal', sharex=ax4, sharey=ax4)
ax2 = fig.add_subplot(2, 2, 2, aspect='equal', sharex=ax4, sharey=ax4)
ax3 = fig.add_subplot(2, 2, 3, aspect='equal', sharex=ax4, sharey=ax4)

ax_list = [ax1, ax2, ax3, ax4]

ax1.title.set_text('1yr')
ax2.title.set_text('10yr')
ax3.title.set_text('100yr')
ax4.title.set_text('1000yr')

for item in ([ax1.title, ax2.title, ax3.title, ax4.title]):
    item.set_fontsize(15)

#  ax4.set_xlim([-5, 2])
ax4.set_xticks(np.arange(-5.0, 2.0, 1.0))

nb_list = [9, 17, 25, 33]

cm = plt.cm.get_cmap('rainbow')

for i in range(4):
    im = ax_list[i].scatter(x[nb_list[i], 1:], y[nb_list[i], 1:], s=1, c=mass[nb_list[i], 1:] * 2E10, vmin=2.0, vmax=6.0, cmap=cm)
    #  im = ax_list[i].scatter(x[nb_list[i],1:], y[nb_list[i],1:], s=1, c=sigma[nb_list[i], 1:]*1.496E13*1.496E13/1.989E33, cmap=cm)

plt.tight_layout()

fig.subplots_adjust(right=0.8)
cbar_ax = fig.add_axes([0.85, 0.15, 0.03, 0.7])
fig.colorbar(im, cax=cbar_ax)
cbar_ax.set_ylabel(r'mass $[10^{23} \rm g]$', fontsize=20)
#  cbar_ax.set_ylabel(r'$\Sigma [{\rm g/cm^2}]$', fontsize=20)


#  plt.legend()

plt.show()

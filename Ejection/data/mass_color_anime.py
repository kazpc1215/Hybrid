#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import os
#from mpl_toolkits.mplot3d import Axes3D
#import matplotlib.animation as animation


#from matplotlib.font_manager import FontProperties
#fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');


dirname = os.path.dirname(os.path.abspath(__file__))

filename = os.path.normpath(os.path.join(dirname, './Ejection_L2cone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_1000yr/Posi_Mass.dat'))





f = open(filename,mode='r')#file read
lines = f.readlines()[1:]  #2行目から読み込み
#lines = lines[0:1788400]
f.close()

nline = 1001
nspace = 2
ntotalline = nline + nspace
nblock = len(lines)/ntotalline #number of output
#nblock = 6

time = np.zeros((nblock,nline))# time, space
number = np.zeros((nblock,nline))# time, space
x = np.zeros((nblock,nline))# time, space
y = np.zeros((nblock,nline))# time, space
z = np.zeros((nblock,nline))# time, space
abs_r = np.zeros((nblock,nline))# time, space
abs_r_xy = np.zeros((nblock,nline))# time, space
mass = np.zeros((nblock,nline))# time, space
delta_r = np.zeros((nblock,nline))# time, space
sigma = np.zeros((nblock,nline))# time, space
n_s = np.zeros((nblock,nline))# time, space
neighbornumber = np.zeros((nblock,nline))# time, space


for nb in range(nblock):
    print nb    
    n1 = ntotalline*nb
    n2 = ntotalline*(nb+1) - 1
    print n1,n2
    step = 0
    for line in lines[n1:n2+1-nspace]:
        column = line[:-1].split('\t')

        time[nb,step] = float(column[0]) # mojiretsu =>float
        number[nb,step] = int(column[1])
        x[nb,step] = float(column[2])
        y[nb,step] = float(column[3])
        z[nb,step] = float(column[4])
        abs_r[nb,step] = float(column[5])
        abs_r_xy[nb,step] = float(column[6])
        mass[nb,step] = float(column[7])
        delta_r[nb,step] = float(column[8])
        sigma[nb,step] = float(column[9])
        n_s[nb,step] = float(column[10])
        neighbornumber[nb,step] = float(column[11])
        #print column
   
        step = step + 1

    
    fig = plt.figure(figsize=(8,6),dpi=100)

    ax = fig.add_subplot(1,1,1, aspect='equal')
    ax.set_xlim([-4,4])
    ax.set_ylim([-4,4])
    ax.set_xlabel('x [AU]', fontsize=20)
    ax.set_ylabel('y [AU]', fontsize=20)
    ax.title.set_text('%.3f [yr]'%time[nb,0])
    ax.title.set_fontsize(15)
    
    fig.subplots_adjust(right=0.8)
    
    
    
    cm = plt.cm.get_cmap('rainbow')
    
    
    #cbar_ax.set_ylabel(r'$\Sigma [{\rm g/cm^2}]$', fontsize=20)
    


    im = ax.scatter(x[nb,1:], y[nb,1:], s=1, c=mass[nb,1:]*2E10, vmin=2.0, vmax=6.0, cmap=cm, label='Ejecta')
    ax.scatter(0, 0, c='k', marker='*', s=50, label='Star')
    ax.scatter(x[nb,0], y[nb,0], c='k', marker='+', s=50, label='Planet')
    cbar_ax = fig.add_axes([0.85, 0.15, 0.03, 0.7])
    fig.colorbar(im, cax=cbar_ax)
    cbar_ax.set_ylabel(r'mass $[10^{24} \rm g]$', fontsize=20)
    
    #plt.tight_layout()
    ax.legend()

    imagename = os.path.normpath(os.path.join(dirname, '../image/L2anime/%02d.png'%nb))
    plt.savefig(imagename)
    plt.close()
    #plt.show()







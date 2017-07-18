#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
from matplotlib.ticker import ScalarFormatter
from mpl_toolkits.mplot3d import Axes3D
#import matplotlib.animation as animation


#from matplotlib.font_manager import FontProperties
#fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');




#filename = "/Users/isoya.kazuhide/Master1/Hybrid/Ejection/data/NoFrag_Ejection_test_OnlyPlanet_1000_100yr/Posi_Velo.dat"

filename = "/Users/isoya.kazuhide/Master1/Hybrid/Ejection/data/Ejection_L2cone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_1000yr/Posi_Velo.dat"


class FixedOrderFormatter(ScalarFormatter):
    def __init__(self, order_of_mag=0, useOffset=True, useMathText=True):
        self._order_of_mag = order_of_mag
        ScalarFormatter.__init__(self, useOffset=useOffset, 
                                 useMathText=useMathText)
    def _set_orderOfMagnitude(self, range):
        self.orderOfMagnitude = self._order_of_mag



f = open(filename,mode='r')#file read
lines = f.readlines()[1:]  #2行目から読み込み
#lines = lines[0:1788400]
f.close()

nline = 1001
nspace = 2
ntotalline = nline + nspace
#nblock = len(lines)/ntotalline #number of output
nblock = 1

time = np.zeros((nblock,nline))# time, space
number = np.zeros((nblock,nline))# time, space
x = np.zeros((nblock,nline))# time, space
y = np.zeros((nblock,nline))# time, space
z = np.zeros((nblock,nline))# time, space
abs_r = np.zeros((nblock,nline))# time, space
abs_r_xy = np.zeros((nblock,nline))# time, space
v_x = np.zeros((nblock,nline))# time, space
v_y = np.zeros((nblock,nline))# time, space
v_z = np.zeros((nblock,nline))# time, space
abs_v = np.zeros((nblock,nline))# time, space

relative_v_x = np.zeros((nblock,nline))# time, space
relative_v_y = np.zeros((nblock,nline))# time, space
relative_v_z = np.zeros((nblock,nline))# time, space

for nb in range(nblock):
    fig = plt.figure(figsize=(8,6),dpi=100)
    ax = fig.add_subplot(111, projection='3d')
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
        v_x[nb,step] = float(column[7])
        v_y[nb,step] = float(column[8])
        v_z[nb,step] = float(column[9])
        abs_v[nb,step] = float(column[10])

        #print column

        relative_v_x[nb,step] = v_x[nb,step] - v_x[nb,0]
        relative_v_y[nb,step] = v_y[nb,step] - v_y[nb,0]
        relative_v_z[nb,step] = v_z[nb,step] - v_z[nb,0]
        
        
        step = step + 1
        
    theta , phi = np.mgrid[0:np.pi:200j, 0:2.0*np.pi:400j]
    #theta = np.linspace(0,2*np.pi,100)
    #phi = np.linspace(0,2*np.pi,100)
    sphere_x = 0.00004 * np.sin(theta) * np.cos(phi) + x[nb,0]
    sphere_y = 0.00004 * np.sin(theta) * np.sin(phi) + y[nb,0]
    sphere_z = 0.00004 * np.cos(theta) + z[nb,0]

    surf = ax.plot_surface(sphere_x,sphere_y,sphere_z,color='cyan')
    #ax.scatter(x[nb,1:],y[nb,1:],z[nb,1:],color='b',s=5,label='Ejecta')
    velo = ax.quiver3D(x[nb,:],y[nb,:],z[nb,:],relative_v_x[nb,:],relative_v_y[nb,:],relative_v_z[nb,:],length=0.00001,color='b',alpha=0.5)

    fake2Dline = mpl.lines.Line2D([0],[0], linestyle="none", c='cyan', marker = 'o')
    ax.legend([fake2Dline,velo], ['Planet','Ejection velocity'], numpoints = 1)

    ax.xaxis.set_major_formatter(FixedOrderFormatter(-5 ,useMathText=True))
    ax.yaxis.set_major_formatter(FixedOrderFormatter(-5 ,useMathText=True))
    ax.zaxis.set_major_formatter(FixedOrderFormatter(-5 ,useMathText=True))

    ax.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
    ax.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
    ax.ticklabel_format(style='sci', axis='z', scilimits=(0,0))

    
    
    ax.set_xlim([0.99-4E-5,0.99+8E-5])
    ax.set_ylim([-6E-5,6E-5])
    ax.set_zlim([-6E-5,6E-5])
    plt.gca().set_aspect('equal', adjustable='box')
    
    plt.show()

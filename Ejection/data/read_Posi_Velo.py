#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
#import matplotlib.animation as animation


#from matplotlib.font_manager import FontProperties
#fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');

fig = plt.figure(figsize=(8,6),dpi=100)
ax = fig.add_subplot(111, projection='3d')


filename = "/Users/isoya.kazuhide/Master1/Hybrid/Ejection/data/NoFrag_Ejection_test_OnlyPlanet_1000_100yr/Posi_Velo.dat"



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

    ax.plot_surface(sphere_x,sphere_y,sphere_z,color='orange')
    ax.scatter(x[nb,1:],y[nb,1:],z[nb,1:],color='b',s=5)
    ax.quiver(x[nb,:],y[nb,:],z[nb,:],relative_v_x[nb,:],relative_v_y[nb,:],relative_v_z[nb,:],length=0.00002,color='b',alpha=0.5)
    
    plt.gca().set_aspect('equal', adjustable='box')
    
    
    plt.show()

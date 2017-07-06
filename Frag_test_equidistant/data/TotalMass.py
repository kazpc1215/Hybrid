#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
#import matplotlib.animation as animation

plt.figure(figsize=(10,8),dpi=100)

##############################################################################
filename = "./deltar_0010au_0990_xi0005_cutting_edge_2/TotalMass.dat"

GYOU = 65

time=np.empty([GYOU],dtype=float)
M_tot=np.empty([GYOU],dtype=float)
M_tot_0=np.empty([GYOU],dtype=float)

arr = np.genfromtxt(filename, dtype = np.float, delimiter = "\t")

time[:] = arr[:,0]
M_tot[:] = arr[:,1]
M_tot_0[:] = arr[:,2]

M_rel = M_tot/M_tot_0

y=1.0/(1.0+time/10.0)
plt.plot(time, y, color="black", label='analytic',lw=1)  #解析解

plt.scatter(time, M_rel, color="r", marker="x", label=r"$\xi=0.005$")  #data

relative_error=np.absolute(M_rel-y)/y
#plt.plot(time, relative_error , color="r", marker="x", label=r"$\xi=0.005$",lw=1)  #relative error
##############################################################################


##############################################################################
filename = "./deltar_0010au_0990_xi001_cutting_edge_2/TotalMass.dat"

GYOU = 65

time=np.empty([GYOU],dtype=float)
M_tot=np.empty([GYOU],dtype=float)
M_tot_0=np.empty([GYOU],dtype=float)

arr = np.genfromtxt(filename, dtype = np.float, delimiter = "\t")

time[:] = arr[:,0]
M_tot[:] = arr[:,1]
M_tot_0[:] = arr[:,2]

M_rel = M_tot/M_tot_0

y=1.0/(1.0+time/10.0)

plt.scatter(time, M_rel, color="b", marker="+", label=r"$\xi=0.01$")  #data

relative_error=np.absolute(M_rel-y)/y
#plt.plot(time, relative_error, color="b", marker="+", label=r"$\xi=0.01$",lw=1)  #relative error
##############################################################################





plt.xscale("log")
plt.yscale("log")
plt.xlim([0.1,1e4])
plt.autoscale(enable=True, axis='y')
#plt.ylim([0.001,1])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
plt.xlabel('time[yr]',fontsize=25)
plt.ylabel(r'$M_{\rm tot}/M_{\rm tot,0}$', fontsize=25)
#plt.ylabel('relative error', fontsize=25)
plt.grid(True)
plt.tight_layout()
plt.legend(loc=1,fontsize=15)
#plt.legend(bbox_to_anchor=(1.0, 0.8),fontsize=15)



plt.show()

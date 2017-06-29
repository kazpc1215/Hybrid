#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
#import matplotlib.animation as animation

plt.figure(figsize=(10,8),dpi=100)


#from matplotlib.font_manager import FontProperties
#fp = FontProperties(fname='/Users/isoya.kazuhide/Library/Fonts/ipag.ttf');



######################################################################
path = "/Users/isoya.kazuhide/Master1/Nbody_test_2/data/S800L200_1000_rand1//"

N_S = 800
N_L = 200

time=np.empty([N_S+N_L+1,100],dtype=float)  #(ファイル番号,行数)
ecc=np.empty([N_S+N_L+1,100],dtype=float)
axis=np.empty([N_S+N_L+1,100],dtype=float)
u=np.empty([N_S+N_L+1,100],dtype=float)
inc=np.empty([N_S+N_L+1,100],dtype=float)
Omega=np.empty([N_S+N_L+1,100],dtype=float)
omega=np.empty([N_S+N_L+1,100],dtype=float)
r_h=np.empty([N_S+N_L+1,100],dtype=float)

#####
for n in range(1,N_S+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(1,N_S+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_S
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="b", label="run1")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(1,N_S+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_S
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="b")

#####
for n in range(N_S+1,N_S+N_L+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(N_S+1,N_S+N_L+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_L
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="b")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(N_S+1,N_S+N_L+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_L
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="b")
######################################################################


######################################################################
path = "/Users/isoya.kazuhide/Master1/Nbody_test_2/data/S800L200_1000_rand2//"

N_S = 800
N_L = 200

time=np.empty([N_S+N_L+1,100],dtype=float)  #(ファイル番号,行数)
ecc=np.empty([N_S+N_L+1,100],dtype=float)
axis=np.empty([N_S+N_L+1,100],dtype=float)
u=np.empty([N_S+N_L+1,100],dtype=float)
inc=np.empty([N_S+N_L+1,100],dtype=float)
Omega=np.empty([N_S+N_L+1,100],dtype=float)
omega=np.empty([N_S+N_L+1,100],dtype=float)
r_h=np.empty([N_S+N_L+1,100],dtype=float)

#####
for n in range(1,N_S+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(1,N_S+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_S
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="g", label="run2")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(1,N_S+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_S
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="g")

#####
for n in range(N_S+1,N_S+N_L+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(N_S+1,N_S+N_L+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_L
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="g")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(N_S+1,N_S+N_L+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_L
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="g")
######################################################################


######################################################################
path = "/Users/isoya.kazuhide/Master1/Nbody_test_2/data/S800L200_1000_rand3//"

N_S = 800
N_L = 200

time=np.empty([N_S+N_L+1,100],dtype=float)  #(ファイル番号,行数)
ecc=np.empty([N_S+N_L+1,100],dtype=float)
axis=np.empty([N_S+N_L+1,100],dtype=float)
u=np.empty([N_S+N_L+1,100],dtype=float)
inc=np.empty([N_S+N_L+1,100],dtype=float)
Omega=np.empty([N_S+N_L+1,100],dtype=float)
omega=np.empty([N_S+N_L+1,100],dtype=float)
r_h=np.empty([N_S+N_L+1,100],dtype=float)

#####
for n in range(1,N_S+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(1,N_S+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_S
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="r", label="run3")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(1,N_S+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_S
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="r")

#####
for n in range(N_S+1,N_S+N_L+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(N_S+1,N_S+N_L+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_L
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="r")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(N_S+1,N_S+N_L+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_L
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="r")
######################################################################


######################################################################
path = "/Users/isoya.kazuhide/Master1/Nbody_test_2/data/S800L200_1000_rand4//"

N_S = 800
N_L = 200

time=np.empty([N_S+N_L+1,100],dtype=float)  #(ファイル番号,行数)
ecc=np.empty([N_S+N_L+1,100],dtype=float)
axis=np.empty([N_S+N_L+1,100],dtype=float)
u=np.empty([N_S+N_L+1,100],dtype=float)
inc=np.empty([N_S+N_L+1,100],dtype=float)
Omega=np.empty([N_S+N_L+1,100],dtype=float)
omega=np.empty([N_S+N_L+1,100],dtype=float)
r_h=np.empty([N_S+N_L+1,100],dtype=float)

#####
for n in range(1,N_S+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(1,N_S+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_S
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="c", label="run4")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(1,N_S+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_S
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="c")

#####
for n in range(N_S+1,N_S+N_L+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(N_S+1,N_S+N_L+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_L
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="c")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(N_S+1,N_S+N_L+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_L
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="c")
######################################################################


######################################################################
path = "/Users/isoya.kazuhide/Master1/Nbody_test_2/data/S800L200_1000_rand5//"

N_S = 800
N_L = 200

time=np.empty([N_S+N_L+1,100],dtype=float)  #(ファイル番号,行数)
ecc=np.empty([N_S+N_L+1,100],dtype=float)
axis=np.empty([N_S+N_L+1,100],dtype=float)
u=np.empty([N_S+N_L+1,100],dtype=float)
inc=np.empty([N_S+N_L+1,100],dtype=float)
Omega=np.empty([N_S+N_L+1,100],dtype=float)
omega=np.empty([N_S+N_L+1,100],dtype=float)
r_h=np.empty([N_S+N_L+1,100],dtype=float)

#####
for n in range(1,N_S+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(1,N_S+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_S
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="m", label="run5")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(1,N_S+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_S
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="m")

#####
for n in range(N_S+1,N_S+N_L+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(N_S+1,N_S+N_L+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_L
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="m")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(N_S+1,N_S+N_L+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_L
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="m")
######################################################################


######################################################################
path = "/Users/isoya.kazuhide/Master1/Nbody_test_2/data/S800L200_1000_rand6//"

N_S = 800
N_L = 200

time=np.empty([N_S+N_L+1,100],dtype=float)  #(ファイル番号,行数)
ecc=np.empty([N_S+N_L+1,100],dtype=float)
axis=np.empty([N_S+N_L+1,100],dtype=float)
u=np.empty([N_S+N_L+1,100],dtype=float)
inc=np.empty([N_S+N_L+1,100],dtype=float)
Omega=np.empty([N_S+N_L+1,100],dtype=float)
omega=np.empty([N_S+N_L+1,100],dtype=float)
r_h=np.empty([N_S+N_L+1,100],dtype=float)

#####
for n in range(1,N_S+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(1,N_S+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_S
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="y", label="run6")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(1,N_S+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_S
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="y")

#####
for n in range(N_S+1,N_S+N_L+1):  #1 から 101 - 1 まで
    arr = np.genfromtxt(path + "tracer%04d.dat"%n, dtype = np.float, delimiter = "\t")

    time[n,:] = arr[:,0]
    ecc[n,:] = arr[:,1]
    axis[n,:] = arr[:,2]
    u[n,:] = arr[:,3]
    inc[n,:] = arr[:,4]
    Omega[n,:] = arr[:,5]
    omega[n,:] = arr[:,6]
    r_h[n,:] = arr[:,7]
    #print n, axis[n,99], ecc[n,99]


ecc_2 = np.zeros(100,dtype=float)
#print ecc_2
for n in range(N_S+1,N_S+N_L+1):
    ecc_2 = ecc_2 + ecc[n,:]*ecc[n,:]
ecc_2_mean = ecc_2/N_L
ecc_rms = np.sqrt(ecc_2_mean)
plt.plot(time[1,:], ecc_rms, color="y")

inc_2 = np.zeros(100,dtype=float)
#print inc_2
for n in range(N_S+1,N_S+N_L+1):
    inc_2 = inc_2 + inc[n,:]*inc[n,:]
inc_2_mean = inc_2/N_L
inc_rms = np.sqrt(inc_2_mean)
#print inc_rms
plt.plot(time[1,:], inc_rms, color="y")
######################################################################





    
plt.xlim([0,1000])
plt.ylim([0,0.006])
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
#plt.yscale("log")
plt.xlabel('time[yr]',fontsize=25)
plt.ylabel('ecc,inc', fontsize=25)
plt.grid(True)
plt.tight_layout()
plt.legend(bbox_to_anchor=(0.49, 0.48), borderaxespad=0, fontsize=15, ncol=3)
#plt.legend(bbox_to_anchor=(1.0, 0.6),fontsize=15)
#plt.title("time=%d"%time[1,j],fontsize=18)



plt.show()

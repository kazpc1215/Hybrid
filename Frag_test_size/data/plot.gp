unset multiplot
reset

set term aqua dashed font "Times-Roman,30" enhanced

PAUSE = 0

set key left bottom box width -4 spacing 1.0 font "Times-Roman,20"
set bmargin 2
set lmargin 6
set xtics offset 0,0.3
set ytics offset 0.5,0
set xl "time [yr]" offset 0,1
set format "10^{%L}"

set bar 0.3

# set ytics add (0.02,0.05,0.2,0.5)
# set xr [0.1:10000]
# set yr [0.001:0.1]
set log
# set title "M_{planetesimal} = 3 x 0.01 M_E, M_{tot} = 3 x 10 M_E, <e>_{0} = 0.1"
# set title "M_{planetesimal} = 0.01 M_E, M_{tot} = 10 M_E, <e>_{0} = 0.01"
# set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"


# unset key


###############################


set log
set format "10^{%L}"
set auto
set xr [0.1:1000]
#set yr [:1]
set yr [:1.01]
set yl "{/Symbol S}/{/Symbol S}_0" offset 2,0

#####


### sigma ###

set key left Left bottom box width -10 spacing 1.0 reverse font "Times-Roman,20"

plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_drmin2E-3_dthetamin0.125pi/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.695252087458064e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.594236) lw 2

# plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_drmin2E-3_dthetamin0.125pi/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($2)/9.0E-5) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.594236) lw 2
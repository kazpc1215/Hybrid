unset multiplot
reset
set auto

set term aqua dashed font "Times-Roman,30" enhanced

PAUSE = -1

set key left bottom box width -4 spacing 1.0 font "Times-Roman,20"
set bmargin 2
set lmargin 6
set xtics offset 0,0.3
set ytics offset 0.5,0
set xl "time [yr]" offset 0,1
set format "10^{%L}"

set bar 0.3

# set ytics add (0.02,0.05,0.2,0.5)

set log

#########################################


# OHTSUKI_NOFRAG_PLANET = "Meach3E-9_Mtot3E-7_Mmax5E-15_t1E9_dtlog_ecc1E-2_nofrag_dt/Planet.dat"
# OHTSUKI_NOFRAG_PLANETESIMAL = "Meach3E-9_Mtot3E-7_Mmax5E-15_t1E9_dtlog_ecc1E-2_nofrag_dt/Planetesimal.dat"
# RUN1 = "Ntr1E2_t1E8_dtlog_Mtot3E-7_Mmax5E-15_ecc1E-2_nofrag_acc/RMS_randall.dat"


# OHTSUKI_NOFRAG_PLANET = "Meach3E-9_Mtot3E-7_Mmax5E-15_t1E9_dtlog_ecc3E-2_nofrag_dt/Planet.dat"
# OHTSUKI_NOFRAG_PLANETESIMAL = "Meach3E-9_Mtot3E-7_Mmax5E-15_t1E9_dtlog_ecc3E-2_nofrag_dt/Planetesimal.dat"
# RUN1 = "Ntr1E2_t1E8_dtlog_Mtot3E-7_Mmax5E-15_ecc3E-2_nofrag_acc/RMS_randall.dat"


 OHTSUKI_NOFRAG_PLANET = "Meach3E-9_Mtot3E-7_Mmax5E-15_t1E9_dtlog_ecc5E-2_nofrag_dt/Planet.dat"
 OHTSUKI_NOFRAG_PLANETESIMAL = "Meach3E-9_Mtot3E-7_Mmax5E-15_t1E9_dtlog_ecc5E-2_nofrag_dt/Planetesimal.dat"
 RUN1 = "Ntr1E2_t1E8_dtlog_Mtot3E-7_Mmax5E-15_ecc5E-2_nofrag_acc/RMS_randall.dat"

set yl "ecc" offset 2,0
set xr [1:1.E8+1]
 set yr [1E-3:1]
# set yr [0.003:1]
# set yr [0.005:0.5]


### nofrag_ecc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:2 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
RUN1 u 1:4:5 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag."
set key left Left top box width -12 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:2 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
RUN1 u 1:6:7 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag."
unset multiplot

pause -1


set yl "inc [rad]" offset 2,0
set xr [1:1.E8+1]
 set yr [1E-3:1]
# set yr [0.003:1]
# set yr [0.005:0.5]

### nofrag_inc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:3 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
RUN1 u 1:10:11 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag."
set key left Left top box width -12 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:3 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
RUN1 u 1:12:13 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag."
unset multiplot

pause -1

### axis ###
set key left top box width 0 spacing 1.0 font "Times-Roman,20"
set auto
unset log
set log x
set format y "%g"


 RUN1 = "Ntr1E2_t1E8_dtlog_Mtot3E-7_Mmax5E-15_ecc1E-2_nofrag_acc/axis_evo.dat"
# RUN1 = "Ntr1E2_t1E8_dtlog_Mtot3E-7_Mmax5E-15_ecc3E-2_nofrag_acc/axis_evo.dat"
# RUN1 = "Ntr1E2_t1E8_dtlog_Mtot3E-7_Mmax5E-15_ecc5E-2_nofrag_acc/axis_evo.dat"

set yl "normalized migration distance" offset 3,0
plot RUN1 u 1:($4/$6):($5/$6) w yerrorlines lw 2 lt 1 ps 0.5 t "Planet1"
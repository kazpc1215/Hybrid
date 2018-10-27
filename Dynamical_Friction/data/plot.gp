unset multiplot
reset

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
# set xr [0.1:10000]
# set yr [0.001:0.1]
set log
# set title "M_{planetesimal} = 3 x 0.01 M_E, M_{tot} = 3 x 10 M_E, <e>_{0} = 0.1"
# set title "M_{planetesimal} = 0.01 M_E, M_{tot} = 10 M_E, <e>_{0} = 0.01"
# set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"


# unset key


#########################################


set key left bottom box width -5 spacing 1.0 font "Times-Roman,20"


# OHTSUKI_NOFRAG_PLANET = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc1E-2_nofrag_dt/Planet.dat"
# OHTSUKI_NOFRAG_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc1E-2_nofrag_dt/Planetesimal.dat"
# OHTSUKI_FRAG_1E19_PLANET = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc1E-2_frag_dt/Planet.dat"
# OHTSUKI_FRAG_1E19_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc1E-2_frag_dt/Planetesimal.dat"
# OHTSUKI_FRAG_1E16_PLANET = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc1E-2_frag_dt/Planet.dat"
# OHTSUKI_FRAG_1E16_PLANETESIMAL = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc1E-2_frag_dt/Planetesimal.dat"
# RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat"
# RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat"
# RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat"
# RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_noacc/RMS_randall.dat"
# RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat"
# RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_acc/RMS_randall.dat"



 OHTSUKI_NOFRAG_PLANET = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc3E-2_nofrag_dt/Planet.dat"
 OHTSUKI_NOFRAG_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc3E-2_nofrag_dt/Planetesimal.dat"
 OHTSUKI_FRAG_1E19_PLANET = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc3E-2_frag_dt/Planet.dat"
 OHTSUKI_FRAG_1E19_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc3E-2_frag_dt/Planetesimal.dat"
 OHTSUKI_FRAG_1E16_PLANET = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc3E-2_frag_dt/Planet.dat"
 OHTSUKI_FRAG_1E16_PLANETESIMAL = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc3E-2_frag_dt/Planetesimal.dat"
 RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat"
 RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat"
 RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat"
 RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_noacc/RMS_randall.dat"
 RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat"
 RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_acc/RMS_randall.dat"



# OHTSUKI_NOFRAG_PLANET = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc5E-2_nofrag_dt/Planet.dat"
# OHTSUKI_NOFRAG_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc5E-2_nofrag_dt/Planetesimal.dat"
# OHTSUKI_FRAG_1E19_PLANET = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc5E-2_frag_dt/Planet.dat"
# OHTSUKI_FRAG_1E19_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc5E-2_frag_dt/Planetesimal.dat"
# OHTSUKI_FRAG_1E16_PLANET = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc5E-2_frag_dt/Planet.dat"
# OHTSUKI_FRAG_1E16_PLANETESIMAL = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc5E-2_frag_dt/Planetesimal.dat"
# RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_nofrag_noacc/RMS_randall.dat"
# RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_nofrag_acc/RMS_randall.dat"
# RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_noacc/RMS_randall.dat"
# RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_noacc/RMS_randall.dat"
# RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_acc/RMS_randall.dat"
# RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_acc/RMS_randall.dat"


set yl "ecc" offset 2,0
set xr [1:1E8]
#  set yr [0.001:0.1]
 set yr [0.003:0.3]
# set yr [0.005:0.5]



### nofrag_ecc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:2 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
RUN2 u 1:4:5 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag."
set key left Left top box width -12 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:2 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
RUN2 u 1:10:11 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag."
unset multiplot

pause PAUSE



### frag_1E19_ecc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANET u 1:2 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{19}g",\
RUN5 u 1:4:5 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "Planet, r.m.s., frag., 10^{19}g"
set key left Left top box width -12 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANETESIMAL u 1:2 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{19}g",\
RUN5 u 1:10:11 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{19}g"
unset multiplot

pause PAUSE



### frag_1E16_ecc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANET u 1:2 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{16}g",\
RUN6 u 1:4:5 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "Planet, r.m.s., frag., 10^{16}g"
set key left Left top box width -12 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANETESIMAL u 1:2 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{16}g",\
RUN6 u 1:10:11 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{16}g"
unset multiplot

pause PAUSE



### nofrag_acc-noacc_ecc  ###
set multiplot
set key left Left bottom box width -14 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:2 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
RUN1 u 1:4:5 w yerrorlines lw 2 dt 1 lt 4 ps 0.5 t "Planet, r.m.s., no frag., no acc.",\
RUN2 u 1:4:5 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag.,      acc."
set key left Left top box width -16 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:2 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
RUN1 u 1:10:11 w yerrorlines lw 2 dt 2 lt 4 ps 0.5 t "Planetesimal, r.m.s., no frag., no acc.",\
RUN2 u 1:10:11 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag.,      acc."
unset multiplot

pause PAUSE



### frag_1E19_acc-noacc_ecc  ###
set multiplot
set key left Left bottom box width -14 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANET u 1:2 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{19}g",\
RUN3 u 1:4:5 w yerrorlines lw 2 dt 1 lt 5 ps 0.5 t "Planet, r.m.s., frag., 10^{19}g, no acc.",\
RUN5 u 1:4:5 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "Planet, r.m.s., frag., 10^{19}g,      acc."
set key left Left top box width -16 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANETESIMAL u 1:2 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{19}g",\
RUN3 u 1:10:11 w yerrorlines lw 2 dt 2 lt 5 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{19}g, no acc.",\
RUN5 u 1:10:11 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{19}g,      acc."
unset multiplot

pause PAUSE



### frag_1E16_acc-noacc_ecc  ###
set multiplot
set key left Left bottom box width -14 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANET u 1:2 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{16}g",\
RUN4 u 1:4:5 w yerrorlines lw 2 dt 1 lt 6 ps 0.5 t "Planet, r.m.s., frag., 10^{16}g, no acc.",\
RUN6 u 1:4:5 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "Planet, r.m.s., frag., 10^{16}g,      acc."
set key left Left top box width -16 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANETESIMAL u 1:2 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{16}g",\
RUN4 u 1:10:11 w yerrorlines lw 2 dt 2 lt 6 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{16}g, no acc.",\
RUN6 u 1:10:11 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{16}g,      acc."
unset multiplot

pause PAUSE



### numerical_ecc  ###
set multiplot
set key left Left bottom box width -12 spacing 1.0 reverse font "Times-Roman,20"
plot RUN2 u 1:4:5 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag.",\
RUN5 u 1:4:5 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "Planet, r.m.s.,      frag., 10^{19}g",\
RUN6 u 1:4:5 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "Planet, r.m.s.,      frag., 10^{16}g"
set key left Left top box width -13.5 spacing 1.0 reverse font "Times-Roman,20"
plot RUN2 u 1:10:11 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag.",\
RUN5 u 1:10:11 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "Planetesimal, r.m.s.,      frag., 10^{19}g",\
RUN6 u 1:10:11 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "Planetesimal, r.m.s.,      frag., 10^{16}g"
unset multiplot

pause PAUSE



### analytic_ecc  ###
set multiplot
set key left Left bottom box width -13.5 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:2 w l lt 1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
OHTSUKI_FRAG_1E19_PLANET u 1:2 w l lt 2 lw 2 dt 1 t "Planet, semi-analytic,      frag., 10^{19}g",\
OHTSUKI_FRAG_1E16_PLANET u 1:2 w l lt 3 lw 2 dt 1 t "Planet, semi-analytic,      frag., 10^{16}g"
set key left Left top box width -15.5 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:2 w l lt 1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
OHTSUKI_FRAG_1E19_PLANETESIMAL u 1:2 w l lt 2 lw 2 dt 2 t "Planetesimal, semi-analytic,      frag., 10^{19}g",\
OHTSUKI_FRAG_1E16_PLANETESIMAL u 1:2 w l lt 3 lw 2 dt 2 t "Planetesimal, semi-analytic,      frag., 10^{16}g"
unset multiplot

pause PAUSE

#####################################

set yl "inc [rad]" offset 2,0
set xr [1:1000]
# set yr [0.0001:0.05]
 set yr [0.001:0.15]
# set yr [0.0025:0.25]


### nofrag_inc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:3 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
RUN2 u 1:14:15 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag."
set key left Left top box width -12 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:3 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
RUN2 u 1:20:21 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag."
unset multiplot

pause PAUSE



### frag_1E19_inc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANET u 1:3 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{19}g",\
RUN5 u 1:14:15 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "Planet, r.m.s., frag., 10^{19}g"
set key left Left top box width -12 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANETESIMAL u 1:3 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{19}g",\
RUN5 u 1:20:21 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{19}g"
unset multiplot

pause PAUSE



### frag_1E16_inc  ###
set multiplot
set key left Left bottom box width -10 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANET u 1:3 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{16}g",\
RUN6 u 1:14:15 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "Planet, r.m.s., frag., 10^{16}g"
set key left Left top box width -12 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANETESIMAL u 1:3 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{16}g",\
RUN6 u 1:20:21 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{16}g"
unset multiplot

pause PAUSE



### nofrag_acc-noacc_inc  ###
set multiplot
set key left Left bottom box width -14 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:3 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
RUN1 u 1:14:15 w yerrorlines lw 2 dt 1 lt 4 ps 0.5 t "Planet, r.m.s., no frag., no acc.",\
RUN2 u 1:14:15 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag.,      acc."
set key left Left top box width -16 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:3 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
RUN1 u 1:20:21 w yerrorlines lw 2 dt 2 lt 4 ps 0.5 t "Planetesimal, r.m.s., no frag., no acc.",\
RUN2 u 1:20:21 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag.,      acc."
unset multiplot

pause PAUSE



### frag_1E19_acc-noacc_inc  ###
set multiplot
set key left Left bottom box width -14 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANET u 1:3 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{19}g",\
RUN3 u 1:14:15 w yerrorlines lw 2 dt 1 lt 5 ps 0.5 t "Planet, r.m.s., frag., 10^{19}g, no acc.",\
RUN5 u 1:14:15 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "Planet, r.m.s., frag., 10^{19}g,      acc."
set key left Left top box width -16 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E19_PLANETESIMAL u 1:3 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{19}g",\
RUN3 u 1:20:21 w yerrorlines lw 2 dt 2 lt 5 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{19}g, no acc.",\
RUN5 u 1:20:21 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{19}g,      acc."
unset multiplot

pause PAUSE



### frag_1E16_acc-noacc_inc  ###
set multiplot
set key left Left bottom box width -14 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANET u 1:3 w l lt -1 lw 2 dt 1 t "Planet, semi-analytic, frag., 10^{16}g",\
RUN4 u 1:14:15 w yerrorlines lw 2 dt 1 lt 6 ps 0.5 t "Planet, r.m.s., frag., 10^{16}g, no acc.",\
RUN6 u 1:14:15 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "Planet, r.m.s., frag., 10^{16}g,      acc."
set key left Left top box width -16 spacing 1.1 reverse font "Times-Roman,20"
plot OHTSUKI_FRAG_1E16_PLANETESIMAL u 1:3 w l lt -1 lw 2 dt 2 t "Planetesimal, semi-analytic, frag., 10^{16}g",\
RUN4 u 1:20:21 w yerrorlines lw 2 dt 2 lt 6 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{16}g, no acc.",\
RUN6 u 1:20:21 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "Planetesimal, r.m.s., frag., 10^{16}g,      acc."
unset multiplot

pause PAUSE



### numerical_inc  ###
set multiplot
set key left Left bottom box width -12 spacing 1.0 reverse font "Times-Roman,20"
plot RUN2 u 1:14:15 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "Planet, r.m.s., no frag.",\
RUN5 u 1:14:15 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "Planet, r.m.s.,      frag., 10^{19}g",\
RUN6 u 1:14:15 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "Planet, r.m.s.,      frag., 10^{16}g"
set key left Left top box width -13.5 spacing 1.0 reverse font "Times-Roman,20"
plot RUN2 u 1:20:21 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "Planetesimal, r.m.s., no frag.",\
RUN5 u 1:20:21 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "Planetesimal, r.m.s.,      frag., 10^{19}g",\
RUN6 u 1:20:21 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "Planetesimal, r.m.s.,      frag., 10^{16}g"
unset multiplot

pause PAUSE



### analytic_inc  ###
set multiplot
set key left Left bottom box width -13.5 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANET u 1:3 w l lt 1 lw 2 dt 1 t "Planet, semi-analytic, no frag.",\
OHTSUKI_FRAG_1E19_PLANET u 1:3 w l lt 2 lw 2 dt 1 t "Planet, semi-analytic,      frag., 10^{19}g",\
OHTSUKI_FRAG_1E16_PLANET u 1:3 w l lt 3 lw 2 dt 1 t "Planet, semi-analytic,      frag., 10^{16}g"
set key left Left top box width -15.5 spacing 1.0 reverse font "Times-Roman,20"
plot OHTSUKI_NOFRAG_PLANETESIMAL u 1:3 w l lt 1 lw 2 dt 2 t "Planetesimal, semi-analytic, no frag.",\
OHTSUKI_FRAG_1E19_PLANETESIMAL u 1:3 w l lt 2 lw 2 dt 2 t "Planetesimal, semi-analytic,      frag., 10^{19}g",\
OHTSUKI_FRAG_1E16_PLANETESIMAL u 1:3 w l lt 3 lw 2 dt 2 t "Planetesimal, semi-analytic,      frag., 10^{16}g"
unset multiplot

pause PAUSE



###############################

set key left top box width 0 spacing 1.0 font "Times-Roman,20"
set auto
unset log
set log x
set format y "%g"


#RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/axis_evo.dat"
#RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/axis_evo.dat"
#RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/axis_evo.dat"
#RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_noacc/axis_evo.dat"
#RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/axis_evo.dat"
#RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_acc/axis_evo.dat"

#RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/axis_evo.dat"
#RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/axis_evo.dat"
#RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/axis_evo.dat"
#RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_noacc/axis_evo.dat"
#RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/axis_evo.dat"
#RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_acc/axis_evo.dat"

#RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_nofrag_noacc/axis_evo.dat"
#RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_nofrag_acc/axis_evo.dat"
#RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_noacc/axis_evo.dat"
#RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_noacc/axis_evo.dat"
#RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_acc/axis_evo.dat"
#RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_acc/axis_evo.dat"


#RUN1 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/axis_evo.dat"
#RUN2 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/axis_evo.dat"
#RUN3 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/axis_evo.dat"
#RUN4 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/axis_evo.dat"

RUN1 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/axis_evo.dat"
RUN2 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/axis_evo.dat"
RUN3 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/axis_evo.dat"
RUN4 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_acc/axis_evo.dat"


#set yl "normalized migration distance" offset 2,0
#plot RUN1 u 1:($8/$14):($9/$14) w yerrorlines lw 2 lt 1 ps 0.5 t "Planet1",\
#RUN1 u 1:($10/$16):($11/$16) w yerrorlines lw 2 lt 2 ps 0.5 t "Planet2",\
#RUN1 u 1:($12/$18):($13/$18) w yerrorlines lw 2 lt 3 ps 0.5 t "Planet3"


#set yl "semi-major axis [AU]" offset 3,0
#set yr [0.8:1.2]
#plot RUN1 u 1:2:3 w yerrorlines lw 2 lt 1 ps 0.5 t "Planet1",\
#RUN1 u 1:4:5 w yerrorlines lw 2 lt 2 ps 0.5 t "Planet2",\
#RUN1 u 1:6:7 w yerrorlines lw 2 lt 3 ps 0.5 t "Planet3"


set key left bottom box width 0 spacing 1.0 font "Times-Roman,20"
set key box width -7
set yl "normalized migration distance" offset 3,0
plot RUN1 u 1:($4/$6):($5/$6) w yerrorlines lw 2 lt 1 ps 0.5 t "no frag., no acc.",\
RUN2 u 1:($4/$6):($5/$6) w yerrorlines lw 2 lt 2 ps 0.5 t "no frag.,      acc."

#pause PAUSE

plot RUN3 u 1:($4/$6):($5/$6) w yerrorlines lw 2 lt 3 ps 0.5 t "frag., no acc.",\
RUN4 u 1:($4/$6):($5/$6) w yerrorlines lw 2 lt 4 ps 0.5 t "frag.,      acc.",\

#pause PAUSE

###############################


set log
set format "10^{%L}"
set auto
set xr [0.1:1000]
#set yr [:1]
set yr [:1.01]
set yl "{/Symbol S}/{/Symbol S}_0" offset 2,0

#####


# OHTSUKI_FRAG_1E19_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc1E-2_frag_dt/Planetesimal.dat"
# OHTSUKI_FRAG_1E16_PLANETESIMAL = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc1E-2_frag_dt/Planetesimal.dat"

# OHTSUKI_FRAG_1E19_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc3E-2_frag_dt/Planetesimal.dat"
# OHTSUKI_FRAG_1E16_PLANETESIMAL = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc3E-2_frag_dt/Planetesimal.dat"

 OHTSUKI_FRAG_1E19_PLANETESIMAL = "Meach3E-8_Mtot3E-5_t1E3_dtlog_ecc5E-2_frag_dt/Planetesimal.dat"
 OHTSUKI_FRAG_1E16_PLANETESIMAL = "Meach3E-8_Mtot3E-5_Mmax5E-18_t1E3_dtlog_ecc5E-2_frag_dt/Planetesimal.dat"


#RUN1 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/Sigma_randall.dat"
#RUN2 = "Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_acc/Sigma_randall.dat"

# RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/Sigma_randall.dat"
# RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/Sigma_randall.dat"
# RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_noacc/Sigma_randall.dat"
# RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_acc/Sigma_randall.dat"

# RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/Sigma_randall.dat"
# RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/Sigma_randall.dat"
# RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_noacc/Sigma_randall.dat"
# RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_acc/Sigma_randall.dat"

 RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_noacc/Sigma_randall.dat"
 RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_acc/Sigma_randall.dat"
 RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_noacc/Sigma_randall.dat"
 RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_acc/Sigma_randall.dat"


set key left Left bottom box width -1 spacing 1.0 reverse font "Times-Roman,20"
plot RUN1 u 1:6:7 w yerrorlines lw 2 ps 0.5 t "no acc.",\
RUN2 u 1:6:7 w yerrorlines lw 2 ps 0.5 t "acc."

# pause PAUSE

set key left Left bottom box width -1 spacing 1.0 reverse font "Times-Roman,20"
plot RUN3 u 1:6:7 w yerrorlines lw 2 ps 0.5 t "no acc.",\
RUN4 u 1:6:7 w yerrorlines lw 2 ps 0.5 t "acc."

# pause PAUSE


### sigma ###
set key left Left bottom box width -5 spacing 1.2 reverse font "Times-Roman,20"
plot RUN2 u 1:6:7 w yerrorlines lw 2 lt 2 ps 0.5 t "numerical, m_{max}=10^{19}g",\
RUN4 u 1:6:7 w yerrorlines lw 2 lt 3 ps 0.5 t "numerical, m_{max}=10^{16}g",\
OHTSUKI_FRAG_1E19_PLANETESIMAL u 1:($5/3.0E-5) w l lt 2 lw 2 dt 2 t "semi-analytic, m_{max}=10^{19}g",\
OHTSUKI_FRAG_1E16_PLANETESIMAL u 1:($5/3.0E-5) w l lt 3 lw 2 dt 2 t "semi-analytic, m_{max}=10^{16}g"
reset

set term aqua dashed font "Times-Roman,30"

PAUSE = 1

set key left bottom box width -4 spacing 1.0 font "Times-Roman,20"
set bmargin 2
set lmargin 6
set xtics offset 0,0.3
set ytics offset 0.5,0
set xl "time [yr]" offset 0,1
set format "10^{%L}"

set bar 0.3

#set ytics add (0.02,0.05,0.2,0.5)
#set xr [0.1:10000]
#set yr [0.001:0.1]
set log
#set title "M_{planetesimal} = 3 x 0.01 M_E, M_{tot} = 3 x 10 M_E, <e>_{0} = 0.1"
#set title "M_{planetesimal} = 0.01 M_E, M_{tot} = 10 M_E, <e>_{0} = 0.01"
#set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"


# unset key

#########################################

#### Kobayashi data $6 : e_tr, $7 : i_tr, $8 : e_p, $9 : i_p ####

#########################################


set key left bottom box width -5 spacing 1.0 font "Times-Roman,20"

#KOBAYASHI_NOFRAG = "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat"
#KOBAYASHI_FRAG = "M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat"
#RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat"
#RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat"
#RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat"
#RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_noacc/RMS_randall.dat"
#RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat"
#RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_acc/RMS_randall.dat"


#KOBAYASHI_NOFRAG = "M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat"
#KOBAYASHI_FRAG = "M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat"
#RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat"
#RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat"
#RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat"
#RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_noacc/RMS_randall.dat"
#RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat"
#RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc3E-2_frag_acc/RMS_randall.dat"


KOBAYASHI_NOFRAG = "M6E25_Mtot6E28_ecc5E-2_inc2.5E-2.dat"
KOBAYASHI_FRAG = "M6E25_Mtot6E28_ecc5E-2_inc2.5E-2_frag.dat"
RUN1 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_nofrag_noacc/RMS_randall.dat"
RUN2 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_nofrag_acc/RMS_randall.dat"
RUN3 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_noacc/RMS_randall.dat"
RUN4 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_noacc/RMS_randall.dat"
RUN5 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc5E-2_frag_acc/RMS_randall.dat"
RUN6 = "Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-18_ecc5E-2_frag_acc/RMS_randall.dat"


set yl "ecc" offset 2,0
set xr [0.1:1000]
#set yr [0.0001:0.1]

set key box width -5
plot KOBAYASHI_NOFRAG u 1:8 w l lt -1 lw 2 dt 1 t "planet semi-analytic",\
RUN1 u 1:4:5 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "planet r.m.s.",\
KOBAYASHI_NOFRAG u 1:6 w l lt -1 lw 2 dt 2 t "protoplanet semi-analytic",\
RUN1 u 1:10:11 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "protoplanet r.m.s."



set key box width -10
plot KOBAYASHI_NOFRAG u 1:8 w l lt -1 lw 2 dt 1 t "planet semi-analytic",\
RUN1 u 1:4:5 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "planet r.m.s., no acc.",\
RUN2 u 1:4:5 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "planet r.m.s.,      acc.",\
KOBAYASHI_NOFRAG u 1:6 w l lt -1 lw 2 dt 2 t "protoplanet semi-analytic",\
RUN1 u 1:10:11 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "protoplanet r.m.s., no acc.",\
RUN2 u 1:10:11 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "protoplanet r.m.s.,      acc."



set key box width -10
plot KOBAYASHI_NOFRAG u 1:8 w l lt -1 lw 2 dt 1 t "planet semi-analytic",\
RUN1 u 1:4:5 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "planet r.m.s., no frag.",\
RUN3 u 1:4:5 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "planet r.m.s., frag., 10^{19}g",\
RUN4 u 1:4:5 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "planet r.m.s., frag., 10^{16}g",\
KOBAYASHI_NOFRAG u 1:6 w l lt -1 lw 2 dt 2 t "protoplanet semi-analytic",\
RUN1 u 1:10:11 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "protoplanet r.m.s., no frag.",\
RUN3 u 1:10:11 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "protoplanet r.m.s., frag., 10^{19}g",\
RUN4 u 1:10:11 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "protoplanet r.m.s., frag., 10^{16}g"




set yl "inc [rad]" offset 2,0
set xr [0.1:1000]
#set yr [0.00001:0.1]

set key box width -5
plot KOBAYASHI_NOFRAG u 1:9 w l lt -1 lw 2 dt 1 t "planet semi-analytic",\
RUN1 u 1:14:15 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "planet r.m.s.",\
KOBAYASHI_NOFRAG u 1:7 w l lt -1 lw 2 dt 2 t "protoplanet semi-analytic",\
RUN1 u 1:20:21 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "protoplanet r.m.s."




set key box width -10
plot KOBAYASHI_NOFRAG u 1:9 w l lt -1 lw 2 dt 1 t "planet semi-analytic",\
RUN1 u 1:14:15 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "planet r.m.s., no acc.",\
RUN2 u 1:14:15 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "planet r.m.s.,      acc.",\
KOBAYASHI_NOFRAG u 1:7 w l lt -1 lw 2 dt 2 t "protoplanet semi-analytic",\
RUN1 u 1:20:21 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "protoplanet r.m.s., no acc.",\
RUN2 u 1:20:21 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "protoplanet r.m.s.,      acc."



set key box width -10
plot KOBAYASHI_NOFRAG u 1:9 w l lt -1 lw 2 dt 1 t "planet semi-analytic",\
RUN1 u 1:14:15 w yerrorlines lw 2 dt 1 lt 1 ps 0.5 t "planet r.m.s., no frag.",\
RUN3 u 1:14:15 w yerrorlines lw 2 dt 1 lt 2 ps 0.5 t "planet r.m.s., frag., 10^{19}g",\
RUN4 u 1:14:15 w yerrorlines lw 2 dt 1 lt 3 ps 0.5 t "planet r.m.s., frag., 10^{16}g",\
KOBAYASHI_NOFRAG u 1:7 w l lt -1 lw 2 dt 2 t "protoplanet semi-analytic",\
RUN1 u 1:20:21 w yerrorlines lw 2 dt 2 lt 1 ps 0.5 t "protoplanet r.m.s., no frag.",\
RUN3 u 1:20:21 w yerrorlines lw 2 dt 2 lt 2 ps 0.5 t "protoplanet r.m.s., frag., 10^{19}g",\
RUN4 u 1:20:21 w yerrorlines lw 2 dt 2 lt 3 ps 0.5 t "protoplanet r.m.s., frag., 10^{16}g"



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

#pause

plot RUN3 u 1:($4/$6):($5/$6) w yerrorlines lw 2 lt 3 ps 0.5 t "frag., no acc.",\
RUN4 u 1:($4/$6):($5/$6) w yerrorlines lw 2 lt 4 ps 0.5 t "frag.,      acc.",\

pause

###############################


unset key
set auto
set xr [1:10000]
#set yr [0.01:0.2]
set yl "sigma/sigma_0"

#####

plot 1.0/(1.0 + x/1.306925e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/3.778376367544035e-05) w l t sprintf("rand%02d",i)


plot 1.0/(1.0 + x/1.306925e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/3.778376367544035e-05*1000.0/($5)) w l t sprintf("rand%02d",i)

#####

plot 1.0/(1.0 + x/1.306925e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/3.778376367544035e-05) w l t sprintf("rand%02d",i)

plot 1.0/(1.0 + x/1.306925e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/3.778376367544035e-05*1000.0/($5)) w l t sprintf("rand%02d",i)

#####

plot 1.0/(1.0 + x/1.190277e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/4.148657251563326e-05) w l t sprintf("rand%02d",i)
pause
plot 1.0/(1.0 + x/1.190277e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/4.148657251563326e-05*1098.0/($5)) w l t sprintf("rand%02d",i)

#####

plot 1.0/(1.0 + x/1.190277e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/4.148657251563326e-05) w l t sprintf("rand%02d",i)

plot 1.0/(1.0 + x/1.190277e+02) lt -1 lw 2,\
for [i=1:40] sprintf("Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/rand%02d/Sigma_dep.dat", i) u 1:(($4)/4.148657251563326e-05*1098.0/($5)) w l t sprintf("rand%02d",i)
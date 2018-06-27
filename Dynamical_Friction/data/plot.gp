reset

set term aqua dashed font "Times-Roman,30"

set key left bottom box width -4 spacing 0.9 font "Times-Roman,20"
set bmargin 2
set lmargin 6
set xtics offset 0,0.3
set ytics offset 0.5,0
set xl "time [yr]" offset 0,1
set format "10^{%L}"

#set ytics add (0.02,0.05,0.2,0.5)
#set xr [0.1:10000]
#set yr [0.001:0.1]
set log
#set title "M_{planetesimal} = 3 x 0.01 M_E, M_{tot} = 3 x 10 M_E, <e>_{0} = 0.1"
#set title "M_{planetesimal} = 0.01 M_E, M_{tot} = 10 M_E, <e>_{0} = 0.01"
#set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"


# unset key

#########################################

#### Kobayashi data 6: e_tr, 7: i_tr, 8: e_p, 9:i_p ####

set yl "ecc" offset 2,0
set xr [0.1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:8 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:2 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:2 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:2 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:2 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:6 w l lt -1 lw 2 dt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:4 w l lw 2 lt 1 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:4 w l lw 2 lt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:4 w l lw 2 lt 3 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:4 w l lw 2 lt 4 notitle


set yl "inc [rad]" offset 2,0
set xr [0.1:10000]
set yr [0.0001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:9 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:9 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:5 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:5 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:5 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:5 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:7 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:7 w l lt -1 lw 2 dt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:7 w l lw 2 lt 1 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:7 w l lw 2 lt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:7 w l lw 2 lt 3 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:7 w l lw 2 lt 4 notitle




set yl "ecc" offset 2,0
set xr [0.1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:8 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:8 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:2 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:2 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:2 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:2 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:6 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:6 w l lt -1 lw 2 dt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:4 w l lw 2 lt 1 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:4 w l lw 2 lt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:4 w l lw 2 lt 3 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:4 w l lw 2 lt 4 notitle



set yl "inc [rad]" offset 2,0
set xr [0.1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:9 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:9 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:5 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:5 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:5 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:5 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:7 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:7 w l lt -1 lw 2 dt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:7 w l lw 2 lt 1 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:7 w l lw 2 lt 2 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:7 w l lw 2 lt 3 notitle,\
"Ntr1E3_t1E4_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:7 w l lw 2 lt 4 notitle



#########################################


set yl "ecc" offset 2,0
set xr [0.1:1000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:8 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:3 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:3 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:3 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:3 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:6 w l lt -1 lw 2 dt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:6 w l lw 2 lt 1 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:6 w l lw 2 lt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:6 w l lw 2 lt 3 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:6 w l lw 2 lt 4 notitle



set yl "inc [rad]" offset 2,0
set xr [0.1:1000]
set yr [0.0001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:9 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:9 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:8 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:8 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:8 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:8 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:7 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:7 w l lt -1 lw 2 dt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_acc/RMS_randall.dat" u 1:11 w l lw 2 lt 1 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_acc/RMS_randall.dat" u 1:11 w l lw 2 lt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_nofrag_noacc/RMS_randall.dat" u 1:11 w l lw 2 lt 3 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc1E-2_frag_noacc/RMS_randall.dat" u 1:11 w l lw 2 lt 4 notitle



set yl "ecc" offset 2,0
set xr [0.1:1000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:8 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:8 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:3 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:3 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:3 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:3 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:6 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:6 w l lt -1 lw 2 dt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:6 w l lw 2 lt 1 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:6 w l lw 2 lt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:6 w l lw 2 lt 3 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:6 w l lw 2 lt 4 notitle



set yl "inc [rad]" offset 2,0
set xr [0.1:1000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:9 w l lt -1 lw 2 dt 1 t "Kobayashi w/o frag",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:9 w l lt -1 lw 2 dt 2 t "Kobayashi w frag",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:8 w l lw 2 lt 1 t "w/o frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:8 w l lw 2 lt 2 t "w frag, w acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:8 w l lw 2 lt 3 t "w/o frag, w/o acc",\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:8 w l lw 2 lt 4 t "w frag, w/o acc",\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2.dat" u 1:7 w l lt -1 lw 2 dt 1 notitle,\
"M6E25_Mtot6E28_ecc3E-2_inc1.5E-2_frag.dat" u 1:7 w l lt -1 lw 2 dt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_acc/RMS_randall.dat" u 1:11 w l lw 2 lt 1 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_acc/RMS_randall.dat" u 1:11 w l lw 2 lt 2 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_nofrag_noacc/RMS_randall.dat" u 1:11 w l lw 2 lt 3 notitle,\
"Ntr3E3_t1E3_dtlog_Mtot3E-5_ecc3E-2_frag_noacc/RMS_randall.dat" u 1:11 w l lw 2 lt 4 notitle


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
reset
set term aqua dashed font "Helvetica,20"
set xl "time [yr]"
set yl "ecc"
#set yl "inc [rad]"
#set format "10^{%L}"

set ytics add (0.02,0.05)
set xr [100:10000]
#set yr [0.09:0.2]
set log
#set title "M_{planetesimal} = 3 x 0.01 M_E, M_{tot} = 3 x 10 M_E, <e>_{0} = 0.1"
set title "M_{planetesimal} = 0.01 M_E, M_{tot} = 10 M_E, <e>_{0} = 0.1"
#set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"
set key left top

#plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand1_ver2/RMS.dat" u 1:4 w l t "rand1",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand2_ver2/RMS.dat" u 1:4 w l t "rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand3_ver2/RMS.dat" u 1:4 w l t "rand3",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand4_ver2/RMS.dat" u 1:4 w l t "rand4",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand2/RMS.dat" u 1:4 w l t "all rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand3/RMS.dat" u 1:4 w l t "all rand3"

#plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:7 w l lw 2 dt 2 t "Kobayashi",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand1_ver2/RMS.dat" u 1:5 w l t "rand1",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand2_ver2/RMS.dat" u 1:5 w l t "rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand3_ver2/RMS.dat" u 1:5 w l t "rand3",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand4_ver2/RMS.dat" u 1:5 w l t "rand4",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand2/RMS.dat" u 1:5 w l t "all rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand3/RMS.dat" u 1:5 w l t "all rand3"

#plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand1_ver2/RMS.dat" u 1:2 w l t "rand1",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand2_ver2/RMS.dat" u 1:2 w l t "rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand3_ver2/RMS.dat" u 1:2 w l t "rand3",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand4_ver2/RMS.dat" u 1:2 w l t "rand4",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand2/RMS.dat" u 1:2 w l t "all rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand3/RMS.dat" u 1:2 w l t "all rand3"

#plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:9 w l lw 2 dt 2 t "Kobayashi",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand1_ver2/RMS.dat" u 1:3 w l t "rand1",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand2_ver2/RMS.dat" u 1:3 w l t "rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand3_ver2/RMS.dat" u 1:3 w l t "rand3",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand4_ver2/RMS.dat" u 1:3 w l t "rand4",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand2/RMS.dat" u 1:3 w l t "all rand2",\
#"Ntr1E3_t2E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand3/RMS.dat" u 1:3 w l t "all rand3"

#plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:4 w l t "rand1",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand2/RMS.dat" u 1:4 w l t "rand2",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand3/RMS.dat" u 1:4 w l t "rand3",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand4/RMS.dat" u 1:4 w l t "rand4",\
#"Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:4 w l t "N3E3 rand1"


set yr [0.01:0.1]
set ytics add (0.02,0.05)
set key left bottom
plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 lt 1 t "Kobayashi M_{tot} = 10M_E",\
"M6E25_Mtot9E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 lt 2 t "Kobayashi M_{tot} = 15M_E",\
"M6E25_Mtot12E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 lt 3 t "Kobayashi M_{tot} = 20M_E",\
"M6E25_Mtot18E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 lt 4 t "Kobayashi M_{tot} = 30M_E",\
"Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS_ver2.dat" u 1:2 w l lt 5 t "N3E3 rms",\
"Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS_ver2.dat" u 1:6 w l lt 6 t "N3E3 No.1",\
"Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS_ver2.dat" u 1:7 w l lt 7 t "N3E3 No.2",\
"Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS_ver2.dat" u 1:8 w l lt 8 t "N3E3 No.3"


set yr [0.09:0.15]
set ytics add (0.09,0.11,0.12,0.13,0.14,0.15)
set key left top
#plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 lt 1 t "Kobayashi M_{tot} = 10M_E",\
#"M6E25_Mtot9E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 lt 2 t "Kobayashi M_{tot} = 15M_E",\
#"M6E25_Mtot12E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 lt 3 t "Kobayashi M_{tot} = 20M_E",\
#"M6E25_Mtot18E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 lt 4 t "Kobayashi M_{tot} = 30M_E",\
#"Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:4 w l lt 5 t "N3E3 rand1"

set yr [0.01:0.1]
set ytics add (0.02,0.05)
set key left bottom
#plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 lt 1 t "Kobayashi M_{tot} = 10M_E",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:2 w l t "rand1",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand2/RMS.dat" u 1:2 w l t "rand2",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand3/RMS.dat" u 1:2 w l t "rand3",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand4/RMS.dat" u 1:2 w l t "rand4"

set yr [0.09:0.15]
set ytics add (0.09,0.11,0.12,0.13,0.14,0.15)
set key left top
#plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 lt 1 t "Kobayashi M_{tot} = 10M_E",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:4 w l t "rand1",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand2/RMS.dat" u 1:4 w l t "rand2",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand3/RMS.dat" u 1:4 w l t "rand3",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand4/RMS.dat" u 1:4 w l t "rand4"

#plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:2 w l t "rand1",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand2/RMS.dat" u 1:2 w l t "rand2",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand3/RMS.dat" u 1:2 w l t "rand3",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand4/RMS.dat" u 1:2 w l t "rand4"

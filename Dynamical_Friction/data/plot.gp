set term aqua dashed font "Helvetica,20"
set xl "time [yr]"
set yl "ecc"
#set yl "inc [rad]"
set format "10^{%L}"
set xr [1:10000]
#set yr [0.1:0.2]
set log
set title "M_p=6e25g,M_{tot}=6e28g,<e>_{0}=0.1"
#set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"
set key left

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

plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand2/RMS.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand3/RMS.dat" u 1:4 w l t "rand3",\
"M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:2 w l t "rand1",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand2/RMS.dat" u 1:2 w l t "rand2",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand3/RMS.dat" u 1:2 w l t "rand3"

#plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1/RMS.dat" u 1:2 w l t "rand1",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand2/RMS.dat" u 1:2 w l t "rand2",\
#"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand3/RMS.dat" u 1:2 w l t "rand3"
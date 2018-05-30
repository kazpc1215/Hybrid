reset

set term aqua dashed font "Times-Roman,25"
set xl "time [yr]"
set yl "ecc"
#set yl "inc [rad]"
#set format "10^{%L}"

set ytics add (0.02,0.05,0.2,0.5)
set xr [1:1000]
#set yr [0.001:0.1]
set log
#set title "M_{planetesimal} = 3 x 0.01 M_E, M_{tot} = 3 x 10 M_E, <e>_{0} = 0.1"
#set title "M_{planetesimal} = 0.01 M_E, M_{tot} = 10 M_E, <e>_{0} = 0.01"
#set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"
set key left bottom



plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS.dat" u 1:2 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS.dat" u 1:2 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS.dat" u 1:2 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS.dat" u 1:2 w l t "rand4"


plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS.dat" u 1:2 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS.dat" u 1:2 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS.dat" u 1:2 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS.dat" u 1:2 w l t "rand4"


plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS.dat" u 1:4 w l t "rand4"


plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS.dat" u 1:4 w l t "rand4"


#########################################







set xr [100:1000]
set yr [0.01:0.2]
plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS.dat" u 1:2 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS.dat" u 1:2 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS.dat" u 1:2 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS.dat" u 1:2 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS.dat" u 1:4 w l t "rand4"


set xr [1:1000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS.dat" u 1:2 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS.dat" u 1:2 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS.dat" u 1:2 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS.dat" u 1:2 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS.dat" u 1:4 w l t "rand4"

#########################################

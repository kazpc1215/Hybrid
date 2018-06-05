reset

set term aqua dashed font "Times-Roman,30"
set xl "time [yr]"
set yl "ecc"
#set yl "inc [rad]"
set format "10^{%L}"

#set ytics add (0.02,0.05,0.2,0.5)
set xr [1:10000]
#set yr [0.001:0.1]
set log
#set title "M_{planetesimal} = 3 x 0.01 M_E, M_{tot} = 3 x 10 M_E, <e>_{0} = 0.1"
#set title "M_{planetesimal} = 0.01 M_E, M_{tot} = 10 M_E, <e>_{0} = 0.01"
#set title "M_p=6e25g,M_{tot}=6e28g,<i>_{0}=0.005"
set key left bottom

unset key

plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS_Ntr1000.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS_Ntr1000.dat" u 1:4 w l t "rand4"


plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS_Ntr1000.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS_Ntr1000.dat" u 1:4 w l t "rand4"


plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS_Ntr1000.dat" u 1:6 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS_Ntr1000.dat" u 1:6 w l t "rand4"


plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS_Ntr1000.dat" u 1:6 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS_Ntr1000.dat" u 1:6 w l t "rand4"


#########################################


set xr [1:10000]
set yr [0.01:0.2]
plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS_Ntr1000.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS_Ntr1000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS_Ntr1000.dat" u 1:6 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS_Ntr1000.dat" u 1:6 w l t "rand4"


set xr [1:10000]
set yr [0.01:0.2]
plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2_frag.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand3/RMS_Ntr1000.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand4/RMS_Ntr1000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-1_inc5E-2_frag.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand3/RMS_Ntr1000.dat" u 1:6 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand4/RMS_Ntr1000.dat" u 1:6 w l t "rand4"


set xr [1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS_Ntr1000.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS_Ntr1000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand3/RMS_Ntr1000.dat" u 1:6 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS_Ntr1000.dat" u 1:6 w l t "rand4"


set xr [1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand3/RMS_Ntr1000.dat" u 1:4 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand4/RMS_Ntr1000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand3/RMS_Ntr1000.dat" u 1:6 w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand4/RMS_Ntr1000.dat" u 1:6 w l t "rand4"


#########################################


set key
set xr [1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_nofrag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2 all",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr1000.dat" u 1:4 w l t "rand2",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_nofrag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2 all",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr1000.dat" u 1:6 w l t "rand2"


set xr [1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_frag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1 all",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/RMS_Ntr1000.dat" u 1:4 w l t "rand1",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_frag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1 all",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/RMS_Ntr1000.dat" u 1:6 w l t "rand1"


#########################################

set xr [1:10000]
set yr [0.01:0.2]
plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS_Ntr3000.dat" u 1:4 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS_Ntr3000.dat" u 1:4 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS_Ntr3000.dat" u 1:4 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS_Ntr3000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-1_inc5E-2.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand1/RMS_Ntr3000.dat" u 1:6 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand2/RMS_Ntr3000.dat" u 1:6 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand3/RMS_Ntr3000.dat" u 1:6 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_nofrag_rand4/RMS_Ntr3000.dat" u 1:6 w l t "rand4"


set xr [1:10000]
set yr [0.01:0.2]
plot "M6E25_Mtot6E28_ecc1E-1_inc5E-2_frag.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand1/RMS_Ntr3000.dat" u 1:4 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand2/RMS_Ntr3000.dat" u 1:4 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand3/RMS_Ntr3000.dat" u 1:4 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand4/RMS_Ntr3000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-1_inc5E-2_frag.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand1/RMS_Ntr3000.dat" u 1:6 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand2/RMS_Ntr3000.dat" u 1:6 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand3/RMS_Ntr3000.dat" u 1:6 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_frag_rand4/RMS_Ntr3000.dat" u 1:6 w l t "rand4"


set xr [1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS_Ntr3000.dat" u 1:4 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr3000.dat" u 1:4 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS_Ntr3000.dat" u 1:4 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand5/RMS_Ntr3000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand1/RMS_Ntr3000.dat" u 1:6 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand2/RMS_Ntr3000.dat" u 1:6 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand4/RMS_Ntr3000.dat" u 1:6 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_nofrag_rand5/RMS_Ntr3000.dat" u 1:6 w l t "rand4"


set xr [1:10000]
set yr [0.001:0.1]
plot "M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:8 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/RMS_Ntr3000.dat" u 1:4 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand2/RMS_Ntr3000.dat" u 1:4 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand3/RMS_Ntr3000.dat" u 1:4 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand4/RMS_Ntr3000.dat" u 1:4 w l t "rand4",\
"M6E25_Mtot6E28_ecc1E-2_inc5E-3_frag.dat" u 1:6 w l lw 2 dt 2 t "Kobayashi",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/RMS_Ntr3000.dat" u 1:6 w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand2/RMS_Ntr3000.dat" u 1:6 w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand3/RMS_Ntr3000.dat" u 1:6 w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand4/RMS_Ntr3000.dat" u 1:6 w l t "rand4"


##################################################################

set auto
set xr [1:10000]
#set yr [0.01:0.2]
set yl "sigma/sigma_0"
plot 1.0/(1.0 + x/1.306925e+02),\
"Ntr1E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/sigma.dat" u 1:(($3)/($4)) w l t "rand1",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand2/sigma.dat" u 1:(($3)/($4)) w l t "rand2",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand3/sigma.dat" u 1:(($3)/($4)) w l t "rand3",\
"Ntr1E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand4/sigma.dat" u 1:(($3)/($4)) w l t "rand4"


set auto
#set xr [1:10000]
#set yr [0.01:0.2]
set yl "sigma/sigma_0"
plot 1.0/(1.0 + x/1.335678e+02),\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand1/sigma.dat" u 1:(($3)/($4)) w l t "rand1",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand2/sigma.dat" u 1:(($3)/($4)) w l t "rand2",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand3/sigma.dat" u 1:(($3)/($4)) w l t "rand3",\
"Ntr3E3_t1E3yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_frag_rand4/sigma.dat" u 1:(($3)/($4)) w l t "rand4"
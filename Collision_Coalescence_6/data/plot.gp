reset
#set term postscript eps size 800,600 enhanced color font "Helvetica,30"
set term pngcairo size 800,600 enhanced color font "Helvetica,30"


set key left reverse box spacing 1.5 width -2
set bmargin 4
set auto

set xr [0.3:2.0]
#set yr [0:0.35]

#set log xy
set xl "semi-major axis [AU]"
#set yl "eccentricity" offset 1,0
set yl "mass [M_E]" offset 1,0


#set xtics add (0.5,1.5,2.0)

n=0
while(n<=0){

###################################################################################################
#set out sprintf("N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_log.png",n)
#set out sprintf("N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_linear.png",n)

#ecc
#plot for [i=1:1] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:25] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass log
#plot for [i=1:1] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:25] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass linear
#plot for [i=1:1] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:25] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
###################################################################################################


###################################################################################################
#set out sprintf("N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_log.png",n)
#set out sprintf("N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_linear.png",n)
#ecc
#plot for [i=1:1] sprintf("./N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:18] sprintf("./N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass log
#plot for [i=1:1] sprintf("./N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:18] sprintf("./N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass linear
#plot for [i=1:1] sprintf("./N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:18] sprintf("./N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
###################################################################################################


###################################################################################################
#set out sprintf("N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_log.png",n)
set out sprintf("N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_linear.png",n)
#ecc
#plot for [i=1:1] sprintf("./N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:21] sprintf("./N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass log
#plot for [i=1:1] sprintf("./N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:21] sprintf("./N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass linear
plot for [i=1:1] sprintf("./N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
for [i=2:21] sprintf("./N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
###################################################################################################


###################################################################################################
#set out sprintf("N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_log.png",n)
#set out sprintf("N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_linear.png",n)
#ecc
#plot for [i=1:1] sprintf("./N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:16] sprintf("./N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass log
#plot for [i=1:1] sprintf("./N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:16] sprintf("./N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass linear
#plot for [i=1:1] sprintf("./N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:16] sprintf("./N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
###################################################################################################


###################################################################################################
#set out sprintf("N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_log.png",n)
#set out sprintf("N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1_t%03dMyr_linear.png",n)
#ecc
#plot for [i=1:1] sprintf("./N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:16] sprintf("./N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass log
#plot for [i=1:1] sprintf("./N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:16] sprintf("./N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle

#mass linear
#plot for [i=1:1] sprintf("./N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" t "0 yr  ",\
#for [i=2:16] sprintf("./N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3.0E-6):(($9)*5.0E2) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
###################################################################################################

set output

n=n+1
}



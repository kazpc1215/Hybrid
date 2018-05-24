reset
#set term postscript eps enhanced color font "Helvetica,30"
set term pngcairo enhanced color font "Helvetica,30"

set key left reverse box spacing 1.5 width -2
set auto
set xr [0.4:2.0]
set yr [0:0.35]

set xl "semi-major axis [AU]"
set yl "eccentricity" offset 1,0

n=0
while(n<=100){

set out sprintf("GiantImpactStage_rand2_t%03dMyr.png",n)

plot for [i=1:1] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_ecc1E-1_inc5E-2_rand2/Planet%02d.dat",i) every ::0::0 u 3:2:(($10)*5.0E4) w circles lc rgb "black" t "0 yr  ",\
for [i=2:20] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_ecc1E-1_inc5E-2_rand2/Planet%02d.dat",i) every ::0::0 u 3:2:(($10)*5.0E4) w circles lc rgb "black" notitle,\
for [i=1:1] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_ecc1E-1_inc5E-2_rand2/Planet%02d.dat",i) every ::(n*1000)::(n*1000) u 3:2:(($10)*5.0E4) w circles lc rgb "black" fill solid t sprintf("%d Myr  ",n),\
for [i=1:20] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_ecc1E-1_inc5E-2_rand2/Planet%02d.dat",i) every ::(n*1000)::(n*1000) u 3:2:(($10)*5.0E4) w circles lc rgb "black" fill solid notitle

set output

n=n+1
}



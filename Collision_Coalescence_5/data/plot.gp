reset
set term postscript eps enhanced color font "Helvetica,30"

set key left reverse box spacing 1.5 width -2
set auto
set xr [0.4:1.8]
set yr [0:0.2]

set xl "semi-major axis [AU]"
set yl "eccentricity" offset 1,0

n=1
while(n<=2){

set out sprintf("GiantImpactStage_rand%d.eps",n)

plot for [i=1:1] sprintf("./N20_t1E8yr_dtlog_10RHM_ecc1E-2_inc5E-3_rand%d_v2/Planet%02d.dat",n,i) every ::0::0 u 3:2:(($9)*5.0E2) w circles lc rgb "black" t "0 yr  ",\
for [i=2:20] sprintf("./N20_t1E8yr_dtlog_10RHM_ecc1E-2_inc5E-3_rand%d_v2/Planet%02d.dat",n,i) every ::0::0 u 3:2:(($9)*5.0E2) w circles lc rgb "black" notitle,\
for [i=1:1] sprintf("./N20_t1E8yr_dtlog_10RHM_ecc1E-2_inc5E-3_rand%d_v2/Planet%02d.dat",n,i) every ::57::57 u 3:2:(($9)*5.0E2) w circles lc rgb "black" fill solid t "10^7 yr  ",\
for [i=1:20] sprintf("./N20_t1E8yr_dtlog_10RHM_ecc1E-2_inc5E-3_rand%d_v2/Planet%02d.dat",n,i) every ::57::57 u 3:2:(($9)*5.0E2) w circles lc rgb "black" fill solid notitle

set output

n=n+1
}
!open GiantImpactStage_rand1.eps
!open GiantImpactStage_rand2.eps


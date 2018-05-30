reset

set term aqua font "Helvetica,30"
#set term pngcairo enhanced color font "Helvetica,30"

set auto
#set xr [1E7:1E8]
#set xr [0:100]
#set yr [0:2.0]
#set log x
#set format x "10^{%L}"
set format x "%g"

set xl "time [Myr]"
set yl "semi-major axis [AU]" offset 2,0

plot for [i=1:20] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_Sigma10_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every 10 u (($1)*1E-6):(($3)*(1.0-($2))) w l lt i t sprintf("%d",i),for [i=1:20] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_Sigma10_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i)every 10 u (($1)*1E-6):(($3)*(1.0+($2))) w l lt i notitle
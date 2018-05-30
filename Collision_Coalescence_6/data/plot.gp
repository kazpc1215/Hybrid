reset
#set term postscript eps enhanced color font "Helvetica,30"
set term pngcairo size 800,600 enhanced color font "Helvetica,30"


set key left reverse box spacing 1.5 width -2
set auto

set xr [0.3:2.0]
#set yr [0:0.35]
set cbr [0:1]

set palette model HSV
set palette defined ( 0 0 1 1, 1 1 1 1 )
set palette defined ( 0 0 1 0, 1 0 1 1, 6 0.8333 1 1, 7 0.8333 0 1)

set log xy
set xl "semi-major axis [AU]"
set yl "eccentricity" offset 1,0
#set yl "mass [M_E]" offset 1,0
set cbl "mass [M_E]"

set xtics add (0.5,2.0)

n=0
while(n<=0){

set out sprintf("GiantImpactStage_rand1_t%03dMyr.png",n)

plot for [i=1:1] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_Sigma71_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($10)/3E-6) w p lc palette pt 6 ps 2 t "0 yr  ",\
for [i=2:25] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_Sigma71_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:2:(($10)/3E-6) w p lc palette pt 6 ps 2 notitle,\
for [i=1:1] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_Sigma71_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::(n*1000)::(n*1000) u 3:2:(($10)/3E-6) w p lc palette pt 7 ps 2 t sprintf("%d Myr  ",n),\
for [i=1:25] sprintf("./N25_t1E8yr_dt1E3yr_10RHM_Sigma71_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::(n*1000)::(n*1000) u 3:2:(($10)/3E-6) w p lc palette pt 7 ps 2 notitle


#plot for [i=1:1] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_Sigma10_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3E-6):(($10)*5.0E4) w circles lc rgb "black" t "0 yr  ",\
#for [i=2:20] sprintf("./N20_t1E8yr_dt1E3yr_10RHM_Sigma10_Miso_ecc1E-2_inc5E-3_rand1/Planet%02d.dat",i) every ::0::0 u 3:(($10)/3E-6):(($10)*5.0E4) w circles lc rgb "black" notitle

set output

n=n+1
}



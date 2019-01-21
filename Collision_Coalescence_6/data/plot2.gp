reset

set term aqua font "Times-Roman,30" enhanced
#set term pngcairo size 800,600 enhanced color font "Helvetica,30"

set auto

set xr [1E4:1E8]
YEAR=1.0
set xl "time [yr]" offset 0,1

#set xr [1E-2:1E2]
#YEAR=1.0E6
#set xl "time [Myr]" offset 0,1


set log x
set format x "10^{%L}"
#set format x "%g"

set bmargin 2
set lmargin 7
unset key

set xtics offset 0,0.3
set ytics offset 0,0

#set xl "time [kyr]" offset 0,1
#set yl "semi-major axis [AU]" offset 2.5,0
set yl "pericenter/apocenter distance [AU]" offset 2.5,0

#dirname = "N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1"
dirname = "N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1"

i1 = 1
i2 = 2
i3 = 14
i4 = 17

N=18

#YEAR=1.0E3
EVERY=1
LW=1


# plot for [i=1:N] sprintf("%s/Planet%02d.dat",dirname,i) every EVERY u (($1)/YEAR):(($3)*(1.0-($2))) w l lw 0.5

# pause
set yr [0:2]

plot for [i=1:N] sprintf("%s/Planet%02d.dat",dirname,i) every EVERY u (($1)/YEAR):(($3)*(1.0-($2))) w l lw 0.5 lc rgb "gray50" notitle,\
for [i=1:N] sprintf("%s/Planet%02d.dat",dirname,i) every EVERY u (($1)/YEAR):(($3)*(1.0+($2))) w l lw 0.5 lc rgb "gray50" notitle,\
sprintf("%s/Planet%02d.dat",dirname,i1) every EVERY u (($1)/YEAR):(($3)*(1.0-($2))) w l lw LW lt 1 notitle,\
sprintf("%s/Planet%02d.dat",dirname,i1) every EVERY u (($1)/YEAR):(($3)*(1.0+($2))) w l lw LW lt 1 notitle,\
sprintf("%s/Planet%02d.dat",dirname,i2) every EVERY u (($1)/YEAR):(($3)*(1.0-($2))) w l lw LW lt 2 notitle,\
sprintf("%s/Planet%02d.dat",dirname,i2) every EVERY u (($1)/YEAR):(($3)*(1.0+($2))) w l lw LW lt 2 notitle,\
sprintf("%s/Planet%02d.dat",dirname,i3) every EVERY u (($1)/YEAR):(($3)*(1.0-($2))) w l lw LW lt 3 notitle,\
sprintf("%s/Planet%02d.dat",dirname,i3) every EVERY u (($1)/YEAR):(($3)*(1.0+($2))) w l lw LW lt 3 notitle,\
sprintf("%s/Planet%02d.dat",dirname,i4) every EVERY u (($1)/YEAR):(($3)*(1.0-($2))) w l lw LW lt 4 notitle,\
sprintf("%s/Planet%02d.dat",dirname,i4) every EVERY u (($1)/YEAR):(($3)*(1.0+($2))) w l lw LW lt 4 notitle


pause

set yr [0:20]
set yl "number of protoplanet" offset 2.5,0
plot sprintf("%s/WeightedAverage.dat",dirname) every EVERY u (($1)/YEAR):5 w l lw LW notitle

pause -1

set lmargin 8
set yr [0:0.16]
set ytics 0,0.05
set mytics 5

set yl "mass weighted mean ecc" offset 2.5,0
plot sprintf("%s/WeightedAverage.dat",dirname) every EVERY u (($1)/YEAR):2 w l lw LW notitle

pause -1

set yl "mass weighted mean inc [rad]" offset 2.5,0
plot sprintf("%s/WeightedAverage.dat",dirname) every EVERY u (($1)/YEAR):3 w l lw LW notitle

pause -1

set yl "mass weighted mean (e^2 + i^2)^{1/2}" offset 2.5,0
plot sprintf("%s/WeightedAverage.dat",dirname) every EVERY u (($1)/YEAR):4 w l lw LW notitle
reset
#set term aqua
set log
set format x "10^{%L}"
set format y "10^{%L}"
#set format y "%g"

set xr [1:1E4]
set yr [1E-16:1E-8]
#set yr [*:*]
set xl "time [yr]" font "Helvetica,20" offset 0,-0.5
set yl "relative E error" font "Helvetica,20" offset -3,0
set xtics font "Helvetica,20"
set ytics font "Helvetica,20"
set lmargin 12
set bmargin 5
set key right font "Helvetica,20"


n=1
while (n<=10){


set term pngcairo size 800,600
set out sprintf("../image/N10_t1E4_dt1yr_eta1E-2_%dHill_Eerror.png",n)

p sprintf("./N10_t1E4_dt1yr_eta1E-2_%dHill/ENERGY.dat",n) u (($1)/2.0/pi):(abs($3)) w l t sprintf("{/Symbol D}r = %dHill",n)

set output


n = n+1
}

set term aqua
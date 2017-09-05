reset
#set term aqua
set log y
set format y "10^{%L}"
#set format y "%g"

set xr [0:15]
set yr [1E-14:1E-12]
#set yr [*:*]
set xl "time [yr]" font "Helvetica,20" offset 0,-0.5
set yl "relative E error" font "Helvetica,20" offset -3,0
set xtics font "Helvetica,20"
set ytics font "Helvetica,20"
set lmargin 12
set bmargin 5
set key right font "Helvetica,20"


n=1000
while (n<=3000){


set term pngcairo size 800,600
set out sprintf("../image/Eerror/b%4d_dt1E-2yr_eta1E-3_Eerror.png",n)

p sprintf("./dt1E-2yr_eta1E-3/b%4d_dt1E-2yr_eta1E-3/ENERGY.dat",n) u (($1)/2.0/pi):(abs($3)) w l t sprintf("b=%1.3f",n/1000.0)

set output


n = n+1
}

set term aqua
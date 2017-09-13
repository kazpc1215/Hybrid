reset
#set term aqua
unset log
#set format x "10^{%L}"
#set format y "10^{%L}"
#set format y "%g"


#set auto
set xl "semi-major axis [AU]" font "Helvetica,20" offset 0,-0.5
set yl "ecc" font "Helvetica,20" offset -3,0
set xtics font "Helvetica,20"
set ytics font "Helvetica,20"
set lmargin 12
set bmargin 5
set key right font "Helvetica,20"

RH = 10
set xr [0.9:1.6]
set yr [0:0.005]

n = 2
step = n - 2
while (n<=10001){

filename = "./N10_t1E4_dt1yr_eta1E-2_1Hill/Planet01.dat"
TIME = system("cat " . filename . " | awk \'NR==" . n . "{printf(\"%e\", $1" . ")}\'")
TIME = TIME/2.0/pi
set title sprintf("Time %.f [yr], \t {/Symbol D}a = %d [R_H]",TIME,RH) font "Helvetica,20"


set term pngcairo size 800,600
set out sprintf("../image/N10_t1E4_dt1yr_eta1E-2_%dHill/axisecc_%05d.png",RH,step)

p for [i=1:10] sprintf("./N10_t1E4_dt1yr_eta1E-2_%dHill/Planet%02d.dat",RH,i) every ::n-2::n-2 u 3:2:8 w circle t sprintf("%d",i),for [i=1:10] sprintf("./N10_t1E4_dt1yr_eta1E-2_%dHill/Planet%02d.dat",RH,i) every ::n-2::n-2 u 3:2:(($2)*($3)) w xerrorbars pt 7 ps 0.5 lc rgb "black" t ""

set output

print step

n = n + 1
step = step + 1
}

set term aqua
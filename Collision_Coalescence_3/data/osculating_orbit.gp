reset
set term aqua font "Helvetica,20"
set size square
set xr [-1.5:1.5]
set yr [-1.5:1.5]

set xtics font "Helvetica,20"
set ytics font "Helvetica,20"

set key font "Helvetica,20"

set xl "x[AU]" font "Helvetica,20"
set yl "y[AU]" font "Helvetica,20"

#set lmargin 12
#set tmargin 5
#set key samplen 3
#set yl offset -1,0
#set grid


RH = 5

n = 0

while(n<=10000){

#set term pngcairo size 800,800
#set out sprintf("../image/N10_t1E4_dt1yr_eta1E-2_%dHill_osculating_orbit_%04d.png",RH,n)

set title sprintf("TIME %d [yr], \t {/Symbol D}a = %d [R_H]",n,RH) font "Helvetica,20"

plot for [i=1:10] sprintf("./N10_t1E4_dt1yr_eta1E-2_%dHill_e0001i00005/Planet%02d_e0001i00005_osculating_orbit.dat",RH,i) index n u 2:3 w l lw 1 t sprintf("%d",i)


#set output

n = n + 1
}

set term aqua font "Helvetica,20"

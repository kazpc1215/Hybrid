reset
set term aqua dashed

set xl "semi-major axis [AU]" font "Times-Roman,30"
set yl "mass [10^{24} g]" font "Times-Roman,30"
set xtics font "Times-Roman,30"
set ytics font "Times-Roman,30"
set title font "Times-Roman,25"
#set key font "Times-Roman,25"
unset key
set lmargin 11
set tmargin 2
set title offset 0,-1.0
set yl offset -1,0

n = 2
j = 0
while (n<=46){

file = "./Ejection_L2cone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_6000yr_dt1yr/Planet1.dat"

TIME = system("cat " . file . " | awk \'NR==" . n . "{printf(\"%e\", $1" . ")}\'")
#TIME = system("cat " . file . " | awk \'END{printf(\"%e\", $1" . ")}\'")
TIME = TIME/2.0/pi 
set title sprintf("Time %.2e [yr]",TIME)

#

set xr [0:3]
set yr [0:6]

plot for [i=1:1000] sprintf("Ejection_L2cone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_6000yr_dt1yr/tracer%04d.dat",i) every ::j::j u 3:(($9)*2.0E10) w p pt 5 lc rgb "black"



n = n + 1
j = j + 1
}




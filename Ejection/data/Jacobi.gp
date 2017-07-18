reset
set term aqua dashed

set xl "semi-major axis[AU]" font "Times-Roman,30"
set yl "ecc" font "Times-Roman,30"
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

file = "./Ejection_L2cone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_1000yr/Planet1.dat"

TIME = system("cat " . file . " | awk \'NR==" . n . "{printf(\"%e\", $1" . ")}\'")
#TIME = system("cat " . file . " | awk \'END{printf(\"%e\", $1" . ")}\'")
TIME = TIME/2.0/pi 
set title sprintf("Time %.2e [yr]",TIME)

unset surface
set contour
set cntrparam bspline
set cntrparam order 10
#set cntrparam levels incremental 2.8, 0.05, 3.2
set samples 1000
set isosamples 100
unset surface
set view 0,0
set xr [0:3]
set yr [0:0.6]
set zr [0:5]
I = 0.0

AXIS = 1.0
RH = AXIS*(5.9723E27/3.0/1.989E33)**(1.0/3.0)

#

cont1RH = AXIS/(AXIS+RH) + 2.0*sqrt((AXIS+RH)/AXIS)
#cont4RH = AXIS/(AXIS+4.0*RH) + 2.0*sqrt((AXIS+4.0*RH)/AXIS)
#cont10RH = AXIS/(AXIS+10.0*RH) + 2.0*sqrt((AXIS+10.0*RH)/AXIS)
#set cntrparam levels discrete cont1RH, cont4RH, cont10RH
set cntrparam levels discrete cont1RH
set table "Jacobi_contour" 
splot AXIS/x+2.0*sqrt(x/AXIS)*sqrt(1.0-y*y)*cos(I)
unset table


set xr [0:3]
set yr [0:0.6]

plot for [i=1:1000] sprintf("Ejection_L2cone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_1000yr/tracer%04d.dat",i) every ::j::j u 3:2 w p pt 5 lc rgb "black",\
"Jacobi_contour" u 1:2 w l dt 2 lt 4 lw 2

#set yl "inc[rad]"
#plot for [i=1:1000] sprintf("Ejection_L2cone30equidistant_v1011curl_Frag_OnlyPlanet_xi001_n1000_1000yr/tracer%04d.dat",i) every ::j::j u 3:5 w p pt 5 lc rgb "black"


n = n + 1
j = j + 1
}




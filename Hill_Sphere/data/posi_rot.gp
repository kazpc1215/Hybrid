reset
set term aqua
set view equal xy
set size square

set xr [-5:5]
set yr [-5:5]
#set xr [-1.1:1.1]
#set yr [-1.1:1.1]

#set xl "x [R_{Hill}]" font "Helvetica,20" offset 0,-0.5
#set yl "y [R_{Hill}]" font "Helvetica,20"
#set xl "x [AU]" font "Helvetica,20" offset 0,-0.5
#set yl "y [AU]" font "Helvetica,20"
set xl "x [R_{Planet}]" font "Helvetica,20" offset 0,-0.5
set yl "y [R_{Planet}]" font "Helvetica,20"

set xtics font "Helvetica,20"
set ytics font "Helvetica,20"
set lmargin 10
set bmargin 5
set key right font "Helvetica,20"


#n=2000
n=2500
while (n<=3000){
#while (n<=3000){

#set title sprintf("b=%1.3f",n/1000.0)
#set label 1 sprintf("b=%1.3f",n/1000.0) at -1,1 font "Helvetica,20"
set label 1 sprintf("b=%1.3f",n/1000.0) at -4.5,4.5 font "Helvetica,20"

set term pngcairo size 600,600
#set out sprintf("../image/b%4d_dt1E-2yr_eta5E-2_RHill.png",n)
#set out sprintf("../image/b%4d_dt1E-2yr_eta5E-2_AU.png",n)
set out sprintf("../image/b%4d_dt1E-2yr_eta5E-2_Radius.png",n)

p sprintf("./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u ((($2)-($8))/($13)):((($3)-($9))/($13)) w l t "orbit",\
sprintf("< tail -1 ./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u ((($2)-($8))/($13)):((($3)-($9))/($13)):(($7)/($13)) w circle t "R_{Planetesimal}",\
sprintf("< head -2 ./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u ((($8)-($8))/($13)):((($9)-($9))/($13)):(($13)/($13)) w circle t "R_{Planet}"


#p sprintf("./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u ((($2)-($8))/($14)):((($3)-($9))/($14)) w l t "orbit",\
#sprintf("< tail -1 ./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u ((($2)-($8))/($14)):((($3)-($9))/($14)) t "collision point",\
#sprintf("< head -2 ./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u ((($8)-($8))/($14)):((($9)-($9))/($14)):(($14)/($14)) w circle t "R_{Hill}",\
#sprintf("< head -2 ./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u ((($8)-($8))/($14)):((($9)-($9))/($14)):(($13)/($14)) w circle t "R_{Planet}"


#p sprintf("./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u 2:3 w l t "orbit",\
#sprintf("< head -2 ./dt1E-2yr_eta5E-2/b%4d_dt1E-2yr_eta5E-2/Planetesimal_posi_rot.dat",n) u 8:9 t "Planet"



print n

set output

n = n+1
}
set term aqua
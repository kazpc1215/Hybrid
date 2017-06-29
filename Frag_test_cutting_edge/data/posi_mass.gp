reset
set log y
set grid
N = 54

#set yr [1e-6:1e-3]
#set yl "{/Symbol S} [M_{Solar} / AU^2]"

set yr [1e-9:1e-6]
set yl "mass [M_{Solar}]"

set xr [0.94:1.06]



set format y "10^{%L}"
set xl "Orbital Radius [AU]"
i = 0
t = 0.0
set title sprintf("time = %.02e[yr]",t)
set term pngcairo size 800,600 font "Helvetica,20"

#set out sprintf("../image/deltar_0010au_1000_page%03d.png",i)
#p "deltar_0010au_1000/Posi_Mass.dat" index i u 7:10 w p pt 6 ps 1 t sprintf("data"),4.994E-4/(4.0*pi*1.0*0.05)/(1.0+t/10.0) t "analytic"

set out sprintf("../image/deltar_0025au_1000_page%03d.png",i)
p "deltar_0025au_1000/Posi_Mass.dat" index i u 7:8 w p pt 6 ps 1 t sprintf("data"),4.994E-7/(1.0+t/10.0) t "analytic"
set output

#set out "../image/pngtest.png"
#test
#set output

i = i+1
t = 0.1

while (i<=N){
      set term pngcairo size 800,600 font "Helvetica,20"
      set title sprintf("time = %.02e[yr]",t)

      #set out sprintf("../image/deltar_0010au_1000_page%03d.png",i)   
      #p "deltar_0010au_1000/Posi_Mass.dat" index i u 7:10 w p pt 6 ps 1t sprintf("data"),4.994E-4/(4.0*pi*1.0*0.05)/(1.0+t/10.0) t "analytic"


      set out sprintf("../image/deltar_0025au_1000_page%03d.png",i)
      p "deltar_0025au_1000/Posi_Mass.dat" index i u 7:8 w p pt 6 ps 1 t sprintf("data"),4.994E-7/(1.0+t/10.0) t "analytic"
      set output
      i = i+1
      t = t*1.2
      #pause 0.1
}

set term aqua font "Helvetica,20" dashed

#,"" index i u 7:(4.994E-4/(4.0*pi*1.0*0.05)/(1.0+($1)/10.0)) w l t sprintf("analytic")
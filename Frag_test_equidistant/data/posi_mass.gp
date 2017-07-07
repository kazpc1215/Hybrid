reset
set term aqua font "Helvetica,20" dashed
set auto
#set log y
set grid
N = 64

#set yr [1e-6:1e-2]
#set yl "{/Symbol S} [M_{Solar} / AU^2]"

#set yr [1e-9:1e-5]
#set yl "mass [M_{Solar}]"

#set yr [-0.0008:0.0008]
#set yl "z [AU]"

#set xr [0.95:1.05]

set size square
set xl "x [AU]"
set yl "y [AU]"


#set format y "10^{%L}"
#set xl "Orbital Radius [AU]"
i = 0
t = 0.0
set title sprintf("time = %.02e[yr]",t)
set term pngcairo size 800,600 font "Helvetica,20"

set out sprintf("../image/deltar_0010au_0990_page%03d.png",i)
#p "deltar_0010au_0990_xi0005_cutting_edge_2/Posi_Mass.dat" index i u 7:11 w p pt 6 ps 1 t sprintf("data"),0.00176642915581268/(4.0*pi*1.0*0.05)/(1.0+t/10.0) t "analytic"

#p "deltar_0010au_0990_xi0005_cutting_edge_2/Posi_Mass.dat" index i u 7:8 w p pt 6 ps 1 t sprintf("data"),0.00176642915581268/990.0/(1.0+t/10.0) t "analytic"

#p "deltar_0010au_0990_xi0005_cutting_edge_2/Posi_Mass.dat" index i u 7:5 w p pt 6 ps 1 t sprintf("data")

p "deltar_0010au_0990_xi0005_cutting_edge_2/Posi_Mass.dat" index i u 3:4 w p pt 6 ps 1 t sprintf("data")

set output


i = 1
t = 0.1

while (i<=N){
      set term pngcairo size 800,600 font "Helvetica,20"
      set title sprintf("time = %.02e[yr]",t)

      set out sprintf("../image/deltar_0010au_0990_page%03d.png",i)   
      #p "deltar_0010au_0990_xi0005_cutting_edge_2/Posi_Mass.dat" index i u 7:11 w p pt 6 ps 1t sprintf("data"),0.00176642915581268/(4.0*pi*1.0*0.05)/(1.0+t/10.0) t "analytic"
      #p "deltar_0010au_0990_xi0005_cutting_edge_2/Posi_Mass.dat" index i u 7:8 w p pt 6 ps 1 t sprintf("data"),0.00176642915581268/990.0/(1.0+t/10.0) t "analytic"

      p "deltar_0010au_0990_xi0005_cutting_edge_2/Posi_Mass.dat" index i u 3:4 w p pt 6 ps 1 t sprintf("data")

      set output
      i = i+1
      t = t*1.2
      #pause 0.1
}

set term aqua font "Helvetica,20" dashed

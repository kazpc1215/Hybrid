reset
set term postscript eps enhanced color font "Helvetica,30"

set xl "{/Helvetica-Oblique n} : Number of Threads"
#set yl "{/Symbol-Oblique a} = {/Helvetica-Oblique T_1} / {/Helvetica-Oblique n}{/Helvetica-Oblique T_n} : Strong Scaling"
set yl "{/Helvetica-Oblique T_1} / {/Helvetica-Oblique T_n} : Speedup"

set log

set xr [1:24]
#set yr [0.1:1]
set yr [1:10]

set grid

set xtics add (1,2,5,10,20)
#set ytics add (0.1,0.2,0.5,1.0)
set ytics add (1,2,5,10)

#set out "StrongScaling_log_v2.eps"
set out "Speedup_log_v2.eps"
#plot "exetime_N1E4_v2.dat" u 1:(2082.607462/($1)/($2)) w lp t "{/Helvetica-Oblique N} = 10^{4}","exetime_N1E5_v2.dat" u 1:(1916.556280/($1)/($2)) w lp t "{/Helvetica-Oblique N} = 10^{5}"
plot "exetime_N1E4_v2.dat" u 1:(2082.607462/($2)) w lp t "{/Helvetica-Oblique N} = 10^{4}","exetime_N1E5_v2.dat" u 1:(1916.556280/($2)) w lp t "{/Helvetica-Oblique N} = 10^{5}"
set output
#!open StrongScaling_log_v2.eps
!open Speedup_log_v2.eps

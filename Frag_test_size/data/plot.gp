unset multiplot
reset

set term aqua dashed font "Times-Roman,30" enhanced

PAUSE = 0


set bmargin 2
set lmargin 6
set xtics offset 0,0.3
set ytics offset 0.5,0


set bar 0.5
LW = 1
PS = 0.5

# unset key


###############################
set log
set format "10^{%L}"
set auto
# set xr [1:1000]
set yr [1E-3:1]
set xl "N_{neighbor}" offset 0,1
set yl "relative error" offset 2,0


### ecc 1E-2 ###



### Ncを変化 ###
RUN1 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta0.125pi_sigma_error.dat"
RUN2 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi_sigma_error.dat"
RUN3 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta0.125pi_sigma_error.dat"
RUN4 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi_sigma_error.dat"

set xr [1:100]
set key right top box width -8 spacing 1.0 font "Times-Roman,20"
plot RUN1 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 1 t "cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"

 pause -1

set xr [1:1000]
set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot RUN2 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 2 t "cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"

 pause -1

set xr [1:1000]
set key right top box width -8 spacing 1.0 font "Times-Roman,20"
plot RUN1 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 1 t "cos term ignored, {/Symbol D} {/Symbol q} =  {/Symbol p}/4",\
RUN2 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 2 t "cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"

 pause -1

set xr [1:100]
set key right top box width -2 spacing 1.0 font "Times-Roman,20"
plot RUN3 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 3 t "{/Symbol D} {/Symbol q} = {/Symbol p}/4"

 pause -1

set xr [1:1000]
set key right top box width -1 spacing 1.0 font "Times-Roman,20"
plot RUN4 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 4 t "{/Symbol D} {/Symbol q} = 2{/Symbol p}"

 pause -1

set xr [1:1000]
set key right top box width -2 spacing 1.0 font "Times-Roman,20"
plot RUN3 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 3 t "{/Symbol D} {/Symbol q} = {/Symbol p}/4",\
RUN4 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 4 t "{/Symbol D} {/Symbol q} = 2{/Symbol p}"

 pause -1

set xr [1:100]
set key right top box width -8 spacing 1.0 font "Times-Roman,20"
plot RUN1 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 1 t "cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4",\
RUN3 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 3 t "{/Symbol D} {/Symbol q} = {/Symbol p}/4"

 pause -1

set xr [1:1000]
set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot RUN2 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 2 t "cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}",\
RUN4 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 4 t "{/Symbol D} {/Symbol q} = 2{/Symbol p}"

 pause -1

set xr [1:100]
set key right top box width -10 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN1 u 1:3 via a,b
p RUN1 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 1 t "cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4", f(x) t sprintf("fitting, index = %.2f ± 0.04",b) lc rgb "black"

pause -1

set xr [1:1000]
set key right top box width -9 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN2 u 1:3 via a,b
p RUN2 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 2 t "cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}", f(x) t sprintf("fitting, index = %.1f ± 0.2",b) lc rgb "black"

pause -1

set xr [1:100]
set key right top box width -10 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN3 u 1:3 via a,b
p RUN3 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 3 t "{/Symbol D} {/Symbol q} = {/Symbol p}/4", f(x) t sprintf("fitting, index = %.1f ± 0.4",b) lc rgb "black"

pause -1

set xr [1:1000]
set key right top box width -10 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN4 u 1:3 via a,b
p RUN4 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 4 t "{/Symbol D} {/Symbol q} = 2{/Symbol p}", f(x) t sprintf("fitting, index = %.2f ± 0.06",b) lc rgb "black"

pause -1



### drを変化 ###
set key right top box width -7 spacing 1.0 font "Times-Roman,20"
# set yr [1E-2:1]
# plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust, cos term ignored"

# pause

set key right top box width 0 spacing 1.0 font "Times-Roman,20"
#set yr [1E-2:1]
# plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust"

# pause


set key right top box width -7 spacing 1.0 font "Times-Roman,20"
# plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 t "adjust, cos term ignored",\
# "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 2 t "adjust"

# pause


### dthetaを変化 ###

set key right top box width -7 spacing 1.0 font "Times-Roman,20"
#set yr [1E-2:1]
# plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust, cos term ignored"

# pause

set key right top box width 0 spacing 1.0 font "Times-Roman,20"
#set yr [1E-2:1]
# plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust"

# pause


set key right top box width -7 spacing 1.0 font "Times-Roman,20"
# plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 t "adjust, cos term ignored",\
# "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 2 t "adjust"

# pause



set log
set format "10^{%L}"
set auto
set xr [0.1:1000]
#set yr [:1]
set yr [:1.01]
set xl "time [yr]" offset 0,1
set yl "{/Symbol S}/{/Symbol S}_0" offset 2,0

#####


set bar 0
LW = 3
PS = 0.5
DT = 2

set xr [0.1:101]
set yr [0.01:1]

set key left bottom box width -12 spacing 1.0 font "Times-Roman,20"
plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot 1.0/(1.0 + x/1.229334) lw 3 dt 2 lc rgb "red" t "analytic (corrected), {/Symbol t} = 1.229334 yr"

pause -1

set key left bottom box width -10 spacing 1.0 font "Times-Roman,20"

RUN1 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN2 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN3 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN4 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN5 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN1 u 1:2:3:4 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN1 u 1:2:5 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN2 u 1:2:3:4 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN2 u 1:2:5 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN3 u 1:2:3:4 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN3 u 1:2:5 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN4 u 1:2:3:4 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN4 u 1:2:5 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN5 u 1:2:3:4 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN5 u 1:2:5 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1


set key left bottom box width -9 spacing 1.0 font "Times-Roman,20"


RUN1 = "./Nc1E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN2 = "./Nc2E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN3 = "./Nc5E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN4 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN5 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN6 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN7 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN8 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_OmegaZero_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN1 u 1:2:3:4 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 10, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN1 u 1:2:5 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 10, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN2 u 1:2:3:4 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 20, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN2 u 1:2:5 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 20, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN3 u 1:2:3:4 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 50, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN3 u 1:2:5 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 50, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN4 u 1:2:3:4 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN4 u 1:2:5 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN5 u 1:2:3:4 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN5 u 1:2:5 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN6 u 1:2:3:4 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN6 u 1:2:5 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN7 u 1:2:3:4 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN7 u 1:2:5 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN8 u 1:2:3:4 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN8 u 1:2:5 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1


############ 数値計算と解析解の比較で一番綺麗に一致するもの
set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot RUN8 u 1:2 w l lw LW ps PS lt 1 dt 2 t "numerical"
############

pause


set key left bottom box width -7 spacing 1.0 font "Times-Roman,20"


RUN1 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN2 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN3 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN4 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN5 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN1 u 1:2:3:4 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN1 u 1:2:5 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN2 u 1:2:3:4 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN2 u 1:2:5 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN3 u 1:2:3:4 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN3 u 1:2:5 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN4 u 1:2:3:4 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN4 u 1:2:5 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN5 u 1:2:3:4 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN5 u 1:2:5 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
pause -1


set key left bottom box width -7 spacing 1.0 font "Times-Roman,20"

RUN1 = "./Nc1E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN2 = "./Nc2E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN3 = "./Nc5E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN4 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN5 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN6 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN7 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN8 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN1 u 1:2:3:4 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 10, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN1 u 1:2:5 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 10, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN2 u 1:2:3:4 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 20, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN2 u 1:2:5 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 20, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN3 u 1:2:3:4 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 50, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN3 u 1:2:5 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 50, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN4 u 1:2:3:4 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN4 u 1:2:5 w yerrorlines lw LW ps PS lt 1 dt DT t "N_c = 100, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN5 u 1:2:3:4 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN5 u 1:2:5 w yerrorlines lw LW ps PS lt 2 dt DT t "N_c = 200, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN6 u 1:2:3:4 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN6 u 1:2:5 w yerrorlines lw LW ps PS lt 3 dt DT t "N_c = 500, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN7 u 1:2:3:4 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN7 u 1:2:5 w yerrorlines lw LW ps PS lt 4 dt DT t "N_c = 1000, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
# replot RUN8 u 1:2:3:4 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN8 u 1:2:5 w yerrorlines lw LW ps PS lt 5 dt DT t "N_c = 2000, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
pause


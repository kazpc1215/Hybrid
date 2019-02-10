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
RUN1 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta0.125pi_sigma_error.dat"
RUN2 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi_sigma_error.dat"
RUN3 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta0.125pi_sigma_error.dat"
RUN4 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi_sigma_error.dat"

set xr [1:1000]
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

set xr [1:1000]
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

set xr [1:1000]
set key right top box width -8 spacing 1.0 font "Times-Roman,20"
plot RUN1 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 1 t "cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4",\
RUN3 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 3 t "{/Symbol D} {/Symbol q} = {/Symbol p}/4"

 pause -1

set xr [1:1000]
set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot RUN2 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 2 t "cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}",\
RUN4 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 4 t "{/Symbol D} {/Symbol q} = 2{/Symbol p}"

 pause -1

set xr [1:1000]
set key right top box width -10 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN1 u 1:3 via a,b
p RUN1 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 1 t "cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4", f(x) t sprintf("fitting, index = %.2f ± 0.08",b) lc rgb "black"

 pause -1

set xr [1:1000]
set key right top box width -10 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN2 u 1:3 via a,b
p RUN2 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 2 t "cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}", f(x) t sprintf("fitting, index = %.2f ± 0.03",b) lc rgb "black"

 pause -1

set xr [1:1000]
set key right top box width -10 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN3 u 1:3 via a,b
p RUN3 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 3 t "{/Symbol D} {/Symbol q} = {/Symbol p}/4", f(x) t sprintf("fitting, index = %.2f ± 0.02",b) lc rgb "black"

pause -1

set xr [1:1000]
set key right top box width -10 spacing 1.0 font "Times-Roman,20"
f(x) = a * x**b
a = 0.5
b = -1.0
fit f(x) RUN4 u 1:3 via a,b
p RUN4 u 1:3:2:4 w xyerrorbars lw LW ps PS lt 4 t "{/Symbol D} {/Symbol q} = 2{/Symbol p}", f(x) t sprintf("fitting, index = %.2f ± 0.04",b) lc rgb "black"

pause -1


########################################

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
LW_DATA = 3
LW_ANALYTIC = 2
PS = 0.5
DT = 2

set xr [0.1:100.0001]
set yr [0.001:1]


############ 数値計算と解析解の比較で一番綺麗に一致するもの
# set key right top box width -1 spacing 1.0 font "Times-Roman,20"
# plot RUN8 u 1:2 w l lw LW_DATA ps PS lt 1 t "numerical"
# replot RUN8 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic"

RUN8 = "./old_2/Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"

set bar 0
LW_DATA = 5
LW_ANALYTIC = 3
PS = 1.5
DT = 2

unset key
plot RUN8 u 1:2 w p ps PS lt 1

pause -1

plot RUN8 u 1:2 w p ps PS lt 1
replot RUN8 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT
############




RUN1 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN2 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN3 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN4 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN5 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"



set key right top box width -8 spacing 1.0 font "Times-Roman,20"
plot RUN1 u 1:6 w l lw LW_DATA lc rgb "red" t "analytic (corrected)"
replot 1.0/(1.0 + x/6.169149e-01) lw LW_ANALYTIC lc rgb "black" dt 2 t "analytic, {/Symbol t} = 6.169149e-01 yr"


pause -1



set key right top box width -5 spacing 1.0 font "Times-Roman,20"


plot RUN1 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 1 t "N_c = 100, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN1 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN2 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 2 t "N_c = 200, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN2 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN3 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 3 t "N_c = 500, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN3 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN4 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 4 t "N_c = 1000, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN4 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN5 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 5 t "N_c = 2000, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN5 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1




set key right top box width -6 spacing 1.0 font "Times-Roman,20"

RUN1 = "./Nc1E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN2 = "./Nc2E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN3 = "./Nc5E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN4 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN5 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN6 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN7 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN8 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"



plot RUN1 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 1 t "N_c = 10, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN1 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN2 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 2 t "N_c = 20, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN2 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN3 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 3 t "N_c = 50, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN3 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN4 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 1 t "N_c = 100, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN4 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN5 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 2 t "N_c = 200, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN5 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN6 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 3 t "N_c = 500, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN6 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN7 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 4 t "N_c = 1000, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN7 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN8 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 5 t "N_c = 2000, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN8 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1




########



set key right top box width -10.5 spacing 1.0 font "Times-Roman,20"

RUN1 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN2 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN3 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN4 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"
RUN5 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta0.125pi/Sigma_mean.dat"



plot RUN1 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 1 t "N_c = 100, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN1 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN2 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 2 t "N_c = 200, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN2 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN3 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 3 t "N_c = 500, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN3 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN4 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 4 t "N_c = 1000, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN4 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN5 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 5 t "N_c = 2000, cos term ignored, {/Symbol D} {/Symbol q} = {/Symbol p}/4"
replot RUN5 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


set key right top box width -9.5 spacing 1.0 font "Times-Roman,20"


RUN1 = "./Nc1E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN2 = "./Nc2E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN3 = "./Nc5E1_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN4 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN5 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN6 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN7 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"
RUN8 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_da0.05index1rms_OMEGAZERO_frag_dr1E-2_dtheta1.0pi/Sigma_mean.dat"


plot RUN1 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 1 t "N_c = 10, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN1 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN2 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 2 t "N_c = 20, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN2 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN3 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 3 t "N_c = 50, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN3 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN4 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 1 t "N_c = 100, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN4 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN5 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 2 t "N_c = 200, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN5 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN6 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 3 t "N_c = 500, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN6 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN7 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 4 t "N_c = 1000, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN7 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1


plot RUN8 u 1:2:5 w yerrorlines lw LW_DATA ps PS lt 5 t "N_c = 2000, cos term ignored, {/Symbol D} {/Symbol q} = 2{/Symbol p}"
replot RUN8 u 1:6 w l lw LW_ANALYTIC lc rgb "black" dt DT t "analytic (corrected)"
pause -1



pause
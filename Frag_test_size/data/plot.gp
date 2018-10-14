unset multiplot
reset

set term aqua dashed font "Times-Roman,30" enhanced

PAUSE = 0


set bmargin 2
set lmargin 6
set xtics offset 0,0.3
set ytics offset 0.5,0


set bar 0.5


# unset key


###############################
set log
set format "10^{%L}"
set auto
set xr [1:1000]
#set yr [1E-3:1E-1]
set xl "N_{neighbor}" offset 0,1
set yl "relative error" offset 2,0


### ecc 1E-2 ###



### Ncを変化 ###
RUN1 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta0.125pi_sigma_error.dat"
RUN2 = "t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi_sigma_error.dat"

set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot RUN1 u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust, cos term ignored"

# pause -1

set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot RUN2 u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust, cos term ignored"

# pause -1


set key right top box width -12 spacing 1.0 font "Times-Roman,20"
plot RUN1 u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 t "adjust, cos term ignored, 0.125 {/Symbol p}",\
RUN2 u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 2 t "adjust, cos term ignored,     1.0 {/Symbol p}"

# pause



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



set key right top box width -10 spacing 1.0 font "Times-Roman,20"
plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot 1.0/(1.0 + x/1.23450477715) lw 3 dt 2 lc rgb "red" t "analytic hosei, {/Symbol t} = 1.23450477715 yr"

pause -1

set key right top box width -7 spacing 1.0 font "Times-Roman,20"

RUN1 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat"
RUN2 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat"
RUN3 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat"
RUN4 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat"
RUN5 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat"

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN1,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 1 t "N_c = 100, 0.125 {/Symbol p}"
replot for [i=2:40] sprintf(RUN1,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 1 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN2,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 2 t "N_c = 200, 0.125 {/Symbol p}"
replot for [i=2:40] sprintf(RUN2,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 2 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN3,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 3 t "N_c = 500, 0.125 {/Symbol p}"
replot for [i=2:40] sprintf(RUN3,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 3 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN4,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 4 t "N_c = 1000, 0.125 {/Symbol p}"
replot for [i=2:40] sprintf(RUN4,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 4 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN5,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 5 t "N_c = 2000, 0.125 {/Symbol p}"
replot for [i=2:40] sprintf(RUN5,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 5 notitle

pause -1




RUN1 = "./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat"
RUN2 = "./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat"
RUN3 = "./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat"
RUN4 = "./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat"
RUN5 = "./Nc2E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat"

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN1,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 1 t "N_c = 100, 1.0 {/Symbol p}"
replot for [i=2:40] sprintf(RUN1,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 1 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN2,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 2 t "N_c = 200, 1.0 {/Symbol p}"
replot for [i=2:40] sprintf(RUN2,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 2 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN3,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 3 t "N_c = 500, 1.0 {/Symbol p}"
replot for [i=2:40] sprintf(RUN3,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 3 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN4,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 4 t "N_c = 1000, 1.0 {/Symbol p}"
replot for [i=2:40] sprintf(RUN4,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 4 notitle
pause -1

plot 1.0/(1.0 + x/1.233830) lw 1 lc rgb "black" t "analytic, {/Symbol t} = 1.233830 yr"
replot for [i=1:1] sprintf(RUN5,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 5 t "N_c = 2000, 1.0 {/Symbol p}"
replot for [i=2:40] sprintf(RUN5,i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lt 5 notitle

pause




set key right bottom box width 0 spacing 1.0 font "Times-Roman,20"
plot 1.0/(1.0 + x/1.233830) lw 2 lc rgb "black" t "analytic"
replot 1.0/(1.0 + x/1.22933414622) lw 2 dt 2 lc rgb "black" t "analytic hosei"
pause 1
replot for [i=1:40] sprintf("./Nc1E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "orange" notitle
pause 1
replot for [i=1:40] sprintf("./Nc2E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "gray" notitle
pause 1
replot for [i=1:40] sprintf("./Nc5E2_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "blue" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_adjust2_OmegaZero_frag_dr1E-2_dtheta1.0pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "green" notitle

pause




set key right bottom box width 0 spacing 1.0 font "Times-Roman,20"
plot 1.0/(1.0 + x/103.4223) lw 1 lc rgb "black" t "analytic"
replot 1.0/(1.0 + x/103.045447809) lw 1 lc rgb "red" t "analytic hosei"

# pause

set key right bottom box width 0 spacing 1.0 font "Times-Roman,20"
plot 1.0/(1.0 + x/103.4223) lw 2 lc rgb "black" t "analytic"
# plot 1.0/(1.0 + x/103.045447809) lw 2 lc rgb "black" t "analytic"
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr2E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "orange" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "gray" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr8E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "blue" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr2E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "green" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "red" notitle

# pause


plot 1.0/(1.0 + x/103.4223) lw 2 lc rgb "black" t "analytic"
# plot 1.0/(1.0 + x/103.045447809) lw 2 lc rgb "black" t "analytic"
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr2E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "orange" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "gray" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr8E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "blue" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr2E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "green" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-2_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "red" notitle

# pause



set key right bottom box width 0 spacing 1.0 font "Times-Roman,20"
plot 1.0/(1.0 + x/103.4223) lw 2 lc rgb "black" t "analytic"
# plot 1.0/(1.0 + x/103.045447809) lw 2 lc rgb "black" t "analytic"
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_dtheta0.0625pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "orange" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "gray" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_dtheta0.25pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "blue" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_dtheta0.5pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "green" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_dtheta1.0pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 1 lc rgb "red" notitle

# pause


plot 1.0/(1.0 + x/103.4223) lw 2 lc rgb "black" t "analytic"
# plot 1.0/(1.0 + x/103.045447809) lw 2 lc rgb "black" t "analytic"
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_dtheta0.0625pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "orange" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_dtheta0.125pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "gray" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_dtheta0.25pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "blue" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_dtheta0.5pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "green" notitle
pause 1
replot for [i=1:40] sprintf("./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_dtheta1.0pi/rand%02d/Sigma_dep.dat",i) u 1:(($4)/4.774648292756859e-05) w l lw 2 lc rgb "red" notitle

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

### drを変化 ###
set key right top box width -7 spacing 1.0 font "Times-Roman,20"
#set yr [1E-2:1]
plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust, cos term ignored"

# pause

set key right top box width 0 spacing 1.0 font "Times-Roman,20"
#set yr [1E-2:1]
plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust"

# pause


set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 t "adjust, cos term ignored",\
"Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust_frag_dtheta0.125pi_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 2 t "adjust"

# pause


### dthetaを変化 ###

set key right top box width -7 spacing 1.0 font "Times-Roman,20"
#set yr [1E-2:1]
plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust, cos term ignored"

# pause

set key right top box width 0 spacing 1.0 font "Times-Roman,20"
#set yr [1E-2:1]
plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 lc rgb "red" t "adjust"

# pause


set key right top box width -7 spacing 1.0 font "Times-Roman,20"
plot "Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust2_OmegaZero_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 1 t "adjust, cos term ignored",\
"Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_adjust_frag_dr4E-3_sigma_error.dat" u 1:3:($1-$2):($1+$2):4:5 w xyerrorbars lw 1 lt 2 t "adjust"

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

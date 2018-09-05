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
set yr [1E-3:1E-1]
set xl "N_{neighbor}" offset 0,1
set yl "relative error" offset 2,0


### ecc 1E-2 ###
set key right bottom box width -4 spacing 1.0 font "Times-Roman,20"
plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 2 lc rgb "red" t "Rayleigh (adjust)"

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_OmegaZero_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 2 lc rgb "red" notitle



set key right bottom box width -1 spacing 1.0 font "Times-Roman,20"
plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 4 lc rgb "forest-green" t "Rayleigh"

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 4 lc rgb "forest-green" notitle



set key right bottom box width 0 spacing 1.0 font "Times-Roman,20"
plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Uniform_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 5 lc rgb "dark-blue" t "Uniform"

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 5 lc rgb "dark-blue" notitle




### ecc 3E-2 ###
set yr [1E-2:1]
set key right bottom box width -4 spacing 1.0 font "Times-Roman,20"
plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 2 lc rgb "red" t "Rayleigh (adjust)"

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_OmegaZero_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars  lw 1 lt 2 lc rgb "red" notitle



set key right bottom box width -1 spacing 1.0 font "Times-Roman,20"
plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 4 lc rgb "forest-green" t "Rayleigh"

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 4 lc rgb "forest-green" notitle




set key right bottom box width 0 spacing 1.0 font "Times-Roman,20"
plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Uniform_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 5 lc rgb "dark-blue" t "Uniform"

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars lw 1 lt 5 lc rgb "dark-blue" notitle



### ecc 5E-2 ###
plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_OmegaZero_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars


plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars


plot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Uniform_frag_drmin1E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars

replot "Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi_sigma_error.dat" u 3:5:($3-$4):($3+$4):6:7 with xyerrorbars





set log
set format "10^{%L}"
set auto
set xr [0.1:1000]
#set yr [:1]
set yr [:1.01]
set xl "time [yr]" offset 0,1
set yl "{/Symbol S}/{/Symbol S}_0" offset 2,0

#####


set key left Left bottom box width -10 spacing 1.0 reverse font "Times-Roman,20"

### Uniform Distriution ###

### ecc = 0.01 ###
plot for [i=5:5] for [j=8:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.774597991176490e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.308233e+02) lw 2

pause

### ecc = 0.03 ###
plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Uniform_frag_drmin5E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.748149356603682e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/2.960658e+01) lw 2

### ecc = 0.05 ###
plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Uniform_frag_drmin1E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.782154743911579e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.465548e+01) lw 2



### Rayleigh Distriution ###

### ecc = 0.01 ###
plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.695252087458064e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.336324e+02) lw 2

### ecc = 0.03 ###
plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_frag_drmin5E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.740592603868593e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/2.966639e+01) lw 2

### ecc = 0.05 ###
plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_frag_drmin1E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.612127807372093e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.534533e+01) lw 2




### Rayleigh & Omega Zero ###

### ecc = 0.01 ###
plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc1E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.695252087458064e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.336324e+02) lw 2

### ecc = 0.03 ###
# plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.740592603868593e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/2.966639e+01) lw 2

### ecc = 0.05 ###
# plot for [i=1:5] for [j=1:8] sprintf("./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc5E-2_Rayleigh_OmegaZero_frag_drmin1E-3_dthetamin0.125pi_rand01/dr%02d_dtheta%02d/Sigma_dep.dat",i,j) u 1:(($4)/3.612127807372093e-05) w l lw 2 t sprintf("%02d,%02d",i,j), 1.0/(1.0 + x/1.534533e+01) lw 2

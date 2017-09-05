reset
set term aqua dashed
#set term x11

set xl "x [R_{Hill}]" font "Helvetica,20"
set yl "y [R_{Hill}]" font "Helvetica,20"


#set lmargin 11
#set tmargin 2
#set title offset 0,-1.0
#set yl offset -1,0


unset surface
set contour
set cntrparam linear
#set cntrparam bspline
#set cntrparam order 10
set samples 1000
set isosamples 1000
unset surface
set view 0,0

mu = 3.0E-6
RH = (mu/3.0)**(1.0/3.0)

f(x,y) = 3.0*x**2 + 2.0*mu/sqrt(x**2+y**2)


set xr [-5.0*RH:5.0*RH]
set yr [-5.0*RH:5.0*RH]
set zr [0:3.1*f(RH,0)]



set cntrparam levels discrete 0.2*f(RH,0), 0.4*f(RH,0), 0.6*f(RH,0), 0.8*f(RH,0),1.0*f(RH,0), 1.2*f(RH,0), 1.4*f(RH,0), 1.6*f(RH,0), 1.8*f(RH,0),2.0*f(RH,0), 2.2*f(RH,0), 2.4*f(RH,0), 2.6*f(RH,0), 2.8*f(RH,0), 3.0*f(RH,0)

set table "ZeroVelocityCurve_contour" 
splot f(x,y)
unset table



set size square
set view equal xy
set xr [-5:5]
set yr [-5:5]


p "ZeroVelocityCurve_contour" u (($1)/RH):(($2)/RH) w l lc rgb "gray50"




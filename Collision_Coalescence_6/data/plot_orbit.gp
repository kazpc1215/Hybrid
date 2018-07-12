reset
#set term postscript eps size 800,600 enhanced color font "Helvetica,30"
set term pngcairo size 800,800 enhanced color font "Helvetica,30"

set bmargin 4
# set auto

set size ratio -1
set xr [-2.0:2.0]
set yr [-2.0:2.0]


set xl "x [AU]" offset 0,0
set yl "y [AU]" offset 0, 0

set xtics offset 0,0
set ytics offset 0,0

unset key

set object circle fill solid fc rgb "red" at 0, 0

n=0
j=0

#dirname = "N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1"
dirname = "N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1"


N=25

while(n<=100000){


###################################################################################################
set title sprintf("t = %.eyr",n*1000.0) offset 0,0
set out sprintf("../image/%s/orbit_t%02d.png",dirname,j)


p sprintf("%s/orbit/Planet_orbit.dat.%06d",dirname,n) u 2:3 w l lc rgb "black",\
for [i=1:N] sprintf("%s/Planet%02d_position.dat",dirname,i) every ::n::n u 2:3:(($6)*7E2) w circles lc rgb "black" fill solid noborder
###################################################################################################

set output

print n

if(n<10){
  n=n+1
}else{
  if(n<100){
    n=n+10
  }else{
    if(n<1000){
      n=n+100
    }else{
      if(n<10000){
        n=n+1000
      }else{
        if(n<100000){
          n=n+10000
        }else{
          n=n+1
        }
      }
    }
  }
}

j=j+1

}


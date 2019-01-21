reset
#set term postscript eps size 800,600 enhanced color font "Helvetica,30"
set term pngcairo size 1200,1200 enhanced color font "Helvetica,35"

set bmargin 4
# set auto

set size ratio -1
set xr [-1.6:1.6]
set yr [-1.6:1.6]


set xl "x [AU]" offset 0,0 tc rgb "white"
set yl "y [AU]" offset 0,0 tc rgb "white"

set xtics offset 0,0 tc rgb "white"
set ytics offset 0,0 tc rgb "white"

set border lw 2 lc rgb "white"

unset key

set object rect behind from screen 0,0 to screen 1,1 fc rgb "black" fill solid 1.0
set object circle fill solid fc rgb "red" at 0, 0

n=0
j=0

#dirname = "N15_t1E8yr_dt1E3yr_10RHM_3MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N16_t1E8yr_dt1E3yr_10RHM_2.5MMSN_Miso_ecc1E-2_inc5E-3_rand1"
dirname = "N18_t1E8yr_dt1E3yr_10RHM_2MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N21_t1E8yr_dt1E3yr_10RHM_1.5MMSN_Miso_ecc1E-2_inc5E-3_rand1"
#dirname = "N25_t1E8yr_dt1E3yr_10RHM_1MMSN_Miso_ecc1E-2_inc5E-3_rand1"


N=18

while(n<=100000){


###################################################################################################
set title sprintf("time : %.e yr",n*1000.0) offset 0,0 tc rgb "white"
set out sprintf("../image/%s/orbit_t%02d.png",dirname,j)


p sprintf("%s/orbit/Planet_orbit.dat.%06d",dirname,n) u 2:3 w l lw 3 lc rgb "white",\
for [i=1:N] sprintf("%s/Planet%02d_position.dat",dirname,i) every ::n::n u 2:3:(($6)*1.5E3) w circles lc rgb "white" fill solid noborder
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


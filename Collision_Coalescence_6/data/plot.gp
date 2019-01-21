reset
#set term postscript eps size 800,600 enhanced color font "Helvetica,30"
set term pngcairo size 800,600 enhanced color font "Helvetica,20"
# set term pngcairo size 800,600 enhanced color font "Times-Roman,20"

#set key left reverse box spacing 1.5 width -2
unset key
set bmargin 4
set auto

set xr [0.3:2.0]
#set xr [0.3:2.5]


set log xy
set xl "semi-major axis [AU]"
set format y "10^{%L}"

set xtics add (0.5,1.5,2.0)
#set xtics add (0.5,1.5,2.0,2.5)

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

#ecc
set title sprintf("time : %.e yr",n*1000.0) offset 0,0
set out sprintf("../image/%s/ecc_axis_t%02d.png",dirname,j)

set yl "ecc" offset 0,0
set yr [1E-3:1]


if((N==15 || N==18) && n==100000){
  plot for [i=1:N] sprintf("%s/Planet%02d.dat",dirname,i) every ::n-1::n-1 u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
}else{
  plot for [i=1:N] sprintf("%s/Planet%02d.dat",dirname,i) every ::n::n u 3:2:(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
}
set output


#mass log
set title sprintf("time : %.e yr",n*1000.0) offset 0,0
set out sprintf("../image/%s/mass_axis_t%02d.png",dirname,j)

set yl "mass [M_E]" offset 0,0
#set yr [1E-2:1]
#set yr [1E-1:1E1]
set yr [1E-2:1E1]

if((N==15 || N==18) && n==100000){
  plot for [i=1:N] sprintf("./%s/Planet%02d.dat",dirname,i) every ::n-1::n-1 u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
}else{
  plot for [i=1:N] sprintf("./%s/Planet%02d.dat",dirname,i) every ::n::n u 3:(($10)/3.0E-6):(($9)*5.0E2*(($3))) w circles lc rgb "gray" fill solid border lc rgb "black" notitle
}
set output
###################################################################################################




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



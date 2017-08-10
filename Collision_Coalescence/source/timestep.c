#include "hybrid.h"

/*初期 タイムステップ計算*/
double Timestep_i_0(int i,double a_0[][4],double adot_0[][4],double abs_a[],double abs_adot[],double dt_[]){
  int k;

  abs_a[i] = 0.0;  
  abs_adot[i] = 0.0;
  for(k=1;k<=3;++k){
    abs_a[i] += a_0[i][k]*a_0[i][k];
    abs_adot[i] += adot_0[i][k]*adot_0[i][k];
  }  //k loop
  
  abs_a[i] = sqrt(abs_a[i]);
  abs_adot[i] = sqrt(abs_adot[i]);
  
  //printf("abs_a[%d]=%f\tabs_adot[%d]=%f\n",i,abs_a[i],i,abs_adot[i]);
  dt_[i] = ETA*abs_a[i]/abs_adot[i];
  return dt_[i];
}


/*i_sys のみのタイムステップ計算*/
double Timestep_i_sys(int i_sys,double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_a[],double abs_adot[],double abs_adot2[],double abs_adot3[],double dt_[]){

  int k;
  double dt_inv = 1.0/dt_[i_sys];
  
  abs_a[i_sys] = 0.0;
  abs_adot[i_sys] = 0.0;
  abs_adot2[i_sys] = 0.0;
  abs_adot3[i_sys] = 0.0;
  for(k=1;k<=3;++k){
    abs_a[i_sys] += a[i_sys][k]*a[i_sys][k];
    abs_adot[i_sys] += adot[i_sys][k]*adot[i_sys][k];
    abs_adot2[i_sys] += (adot2_dt2[i_sys][k] + adot3_dt3[i_sys][k])*(adot2_dt2[i_sys][k] + adot3_dt3[i_sys][k])*dt_inv*dt_inv*dt_inv*dt_inv;
    abs_adot3[i_sys] += adot3_dt3[i_sys][k]*adot3_dt3[i_sys][k]*dt_inv*dt_inv*dt_inv*dt_inv*dt_inv*dt_inv;
  }  //k loop	  
  abs_a[i_sys] = sqrt(abs_a[i_sys]);
  abs_adot[i_sys] = sqrt(abs_adot[i_sys]);
  abs_adot2[i_sys] = sqrt(abs_adot2[i_sys]);
  abs_adot3[i_sys] = sqrt(abs_adot3[i_sys]);
  
  dt_[i_sys] = ETA*sqrt((abs_a[i_sys]*abs_adot2[i_sys] + abs_adot[i_sys]*abs_adot[i_sys])/(abs_adot[i_sys]*abs_adot3[i_sys] + abs_adot2[i_sys]*abs_adot2[i_sys]));

  return dt_[i_sys];
}

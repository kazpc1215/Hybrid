#include "hybrid.h"


/*i_sys のみの修正子*/
inline void Corrector_sys(int i_sys,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double r_p[],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double r_dot_v[],double dt_[]){

  int j,k;
  double abs_r[global_n+1],r_dot_v_ij[global_n+1];
  double a_tmp[4]={},adot_tmp[4]={},adot2_dt2_tmp[4]={},adot3_dt3_tmp[4]={};
  double x_c_tmp[4]={},v_c_tmp[4]={};

  
  for(j=1;j<=global_n;++j){
    if(i_sys!=j){
      abs_r[j] = RelativeDistance(i_sys,j,x_p);  //絶対値.
      r_dot_v_ij[j] = RelativeInnerProduct(i_sys,j,x_p,v_p);  //r_ij,v_ijの内積.
    }else{
      abs_r[i_sys] = 0.0;
      r_dot_v_ij[i_sys] = 0.0;
    }
  }
  
  
  for(k=1;k<=3;++k){
    a_tmp[k] = All_Acceleration(i_sys,k,ele,x_p,r_p,abs_r);
    adot_tmp[k] = All_dAcceleration(i_sys,k,ele,x_p,v_p,r_dot_v,r_dot_v_ij,r_p,abs_r);
  }
   

  /*for(k=1;k<=3;++k){
    printf("a[%d][%d]=%f\tadot[%d][%d]=%f\n",i_sys,k,a[i_sys][k],i_sys,k,adot[i_sys][k]);
    }*/	  
 
  for(k=1;k<=3;++k){  //修正子.
	  
    adot2_dt2_tmp[k] = -6*(a_0[i_sys][k] - a_tmp[k]) - (4*adot_0[i_sys][k] + 2*adot_tmp[k])*dt_[i_sys]; //第2次導関数.
    adot3_dt3_tmp[k] = 12*(a_0[i_sys][k] - a_tmp[k]) + 6*(adot_0[i_sys][k] + adot_tmp[k])*dt_[i_sys]; //第3次導関数.
	  
    x_c_tmp[k] = x_p[i_sys][k] + adot2_dt2_tmp[k]*dt_[i_sys]*dt_[i_sys]/24.0 + adot3_dt3_tmp[k]*dt_[i_sys]*dt_[i_sys]/120.0;
    v_c_tmp[k] = v_p[i_sys][k] + adot2_dt2_tmp[k]*dt_[i_sys]/6.0 +adot3_dt3_tmp[k]*dt_[i_sys]/24.0;
  }  //k loop
  

  r_c[i_sys] = sqrt(x_c_tmp[1]*x_c_tmp[1] + x_c_tmp[2]*x_c_tmp[2] + x_c_tmp[3]*x_c_tmp[3]);
  v2_c[i_sys] = v_c_tmp[1]*v_c_tmp[1] + v_c_tmp[2]*v_c_tmp[2] + v_c_tmp[3]*v_c_tmp[3];
  r_dot_v[i_sys] = x_c_tmp[1]*v_c_tmp[1] + x_c_tmp[2]*v_c_tmp[2] + x_c_tmp[3]*v_c_tmp[3];

  
  for(k=1;k<=3;++k){
    a[i_sys][k] = a_tmp[k];
    adot[i_sys][k] = adot_tmp[k];
    adot2_dt2[i_sys][k] = adot2_dt2_tmp[k];
    adot3_dt3[i_sys][k] = adot3_dt3_tmp[k];
    x_c[i_sys][k] = x_c_tmp[k];
    v_c[i_sys][k] = v_c_tmp[k];
  }

  
  return;
}

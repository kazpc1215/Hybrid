#include "hybrid.h"

/*i_sys のみのiteration*/
void Iteration_sys(int i_sys,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_r[],double abs_r2[],double abs_v[],double abs_v2[],double r_dot_v_ij[],double r_dot_v[],double dt_[]){

  int j,k;

  for(j=1;j<=global_n;++j){
    if(i_sys!=j){	 
      abs_r2[j] = SquareOfRelativeDistance(i_sys,j,x_c); //絶対値2乗.
      abs_v2[j] = SquareOfRelativeVelocity(i_sys,j,v_c);
      r_dot_v_ij[j] = RelativeInnerProduct(i_sys,j,x_c,v_c);  //r_ij,v_ijの内積.
      abs_r[j] = sqrt(abs_r2[j]); //絶対値.
      abs_v[j] = sqrt(abs_v2[j]);	
    }
  }  //j loop
   	  
  r_dot_v[i_sys] = InnerProduct(i_sys,x_c,v_c);  //r_i,v_iの内積.
	 	 
  
  for(k=1;k<=3;++k){
    a[i_sys][k] = All_Acceleration(i_sys,k,ele,x_c,r_c,abs_r2);
    adot[i_sys][k] = All_dAcceleration(i_sys,k,ele,x_c,v_c,r_dot_v,r_dot_v_ij,r_c,abs_r2);
  }
  

  

  //修正子 (iteration).
  for(k=1;k<=3;++k){	  
    adot2_dt2[i_sys][k] = -6*(a_0[i_sys][k] - a[i_sys][k]) - (4*adot_0[i_sys][k] + 2*adot[i_sys][k])*dt_[i_sys]; //第2次導関数.
    adot3_dt3[i_sys][k] = 12*(a_0[i_sys][k] - a[i_sys][k]) + 6*(adot_0[i_sys][k] + adot[i_sys][k])*dt_[i_sys]; //第3次導関数.	  
    x_c[i_sys][k] = x_p[i_sys][k] + adot2_dt2[i_sys][k]*dt_[i_sys]*dt_[i_sys]/24.0 + adot3_dt3[i_sys][k]*dt_[i_sys]*dt_[i_sys]/120.0;
    v_c[i_sys][k] = v_p[i_sys][k] + adot2_dt2[i_sys][k]*dt_[i_sys]/6.0 +adot3_dt3[i_sys][k]*dt_[i_sys]/24.0;
  }  //k loop
   

    
  r_c[i_sys] = RadiusFromCenter(i_sys,x_c);  //中心からの距離.
  v2_c[i_sys] = SquareOfVelocity(i_sys,v_c);  //速度の2乗.
       
}


#include "hybrid.h"

/*全加速度*/
double All_Acceleration(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double r_0[],double abs_r2[],double a_0[][4]){
  a_0[i][k] = External_Acceleration(i,k,x_0,r_0);

#if INTERACTION
  for(j=1;j<=N_tr;++j){
    if(i!=j){
      a_0[i][k] += Acceleration_ij(i,j,k,ele,x_0,abs_r2);	  
    }
  }
#endif
  
  return a_0[i][k];
}


/*全加加速度*/
double All_dAcceleration(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v[],double r_dot_v_ij[],double r_0[],double abs_r2[],double adot_0[][4]){ 
  adot_0[i][k] = External_dAcceleration(i,k,x_0,v_0,r_0,r_dot_v);

#if INTERACTION
  for(j=1;j<=N_tr;++j){ 
    if(i!=j){
      adot_0[i][k] += dAcceleration_ij(i,j,k,ele,x_0,v_0,r_dot_v_ij,abs_r2);
    } 
  }
#endif
  
  return adot_0[i][k];
}




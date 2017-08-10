#include "hybrid.h"

/*角運動量*/
double AngularMomentum(int i,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double abs_L_0){
  int k;
  double L[global_n+1][4];
  double L_tot_0[4];
  
  for(i=1;i<=global_n;++i){ 
    L[i][1] = ele[i].mass*(x_0[i][2]*v_0[i][3] - x_0[i][3]*v_0[i][2]);
    L[i][2] = ele[i].mass*(x_0[i][3]*v_0[i][1] - x_0[i][1]*v_0[i][3]);
    L[i][3] = ele[i].mass*(x_0[i][1]*v_0[i][2] - x_0[i][2]*v_0[i][1]);
  }
  for(k=1;k<=3;++k){
    L_tot_0[k] = 0.0;
    for(i=1;i<=global_n;++i){
      L_tot_0[k] += L[i][k];
    }
  }
  abs_L_0 = 0.0;
  for(k=1;k<=3;++k){
    abs_L_0 += L_tot_0[k]*L_tot_0[k];
  }
  abs_L_0 = sqrt(abs_L_0);
  return abs_L_0;
}

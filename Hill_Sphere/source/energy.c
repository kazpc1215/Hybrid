#include "hybrid.h"


/*エネルギー計算*/
double Calculate_Energy(struct orbital_elements ele[],double x_c[][4],double v2_c[],double r_c[],double abs_r[],double abs_r2[]){

  int i,j;
  double E[N_p+N_tr+1]={};
  double E_tot=0.0;
  
  for(i=1;i<=global_n;++i){
    E[i] = 0.5*ele[i].mass*v2_c[i];
    for(j=i+1;j<=global_n;++j){    
      abs_r2[j] = SquareOfRelativeDistance(i,j,x_c); //絶対値2乗.
      abs_r[j] = sqrt(abs_r2[j]); //絶対値.
        
#ifndef G
      E[i] += - ele[i].mass*ele[j].mass/abs_r[j];  //エネルギー計算.
#else
      E[i] += - G*ele[i].mass*ele[j].mass/abs_r[j];  //エネルギー計算.
#endif
      
    }  //j loop
    
#if !defined(G) && !defined(M_0)    
    E_tot += - ele[i].mass/r_c[i] + E[i];
#else
    E_tot += - G*M_0*ele[i].mass/r_c[i] + E[i];
#endif
    
  }  //i loop
  return E_tot;
}

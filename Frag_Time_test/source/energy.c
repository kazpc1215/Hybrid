#include "hybrid.h"


/*エネルギー計算*/
double Calculate_Energy(struct orbital_elements ele[],double x_c[][4],
#if INDIRECT_TERM
			double v_c[][4],double v_G[],
#else
			double v2_c[],
#endif
			double r_c[],double abs_r[],double abs_r2[]){
  uint64_t start = mach_absolute_time();

  int i,j;
  double E[N_p+N_tr+1]={};
  double E_tot;

#if INDIRECT_TERM
#ifndef M_0
  E_tot = 0.5*(v_G[1]*v_G[1] + v_G[2]*v_G[2] + v_G[3]*v_G[3]);
#else
  E_tot = 0.5*M_0*(v_G[1]*v_G[1] + v_G[2]*v_G[2] + v_G[3]*v_G[3]);
#endif
  
#else
  E_tot = 0.0
#endif
  
  for(i=1;i<=global_n;++i){
    
#if INDIRECT_TERM    
    E[i] = 0.5*ele[i].mass*((v_c[i][1]-v_G[1])*(v_c[i][1]-v_G[1]) + (v_c[i][2]-v_G[2])*(v_c[i][2]-v_G[2]) + (v_c[i][3]-v_G[3])*(v_c[i][3]-v_G[3]));
#else    
    E[i] = 0.5*ele[i].mass*v2_c[i];
#endif
    
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

  uint64_t end = mach_absolute_time();
  exetime.Calculate_Energy += (double)(end-start) * sTimebaseInfo.numer / sTimebaseInfo.denom;
  
  return E_tot;
}

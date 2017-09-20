#include "hybrid.h"

/*全加速度*/
double All_Acceleration(int i,int k,struct orbital_elements ele[],double x_0[][4],double r_0[],double abs_r2[]){
  clock_t start = clock();
  
  int j;
  double a_0;
  
  a_0 = External_Acceleration(i,k,x_0,r_0);

  for(j=1;j<=
#if INTERACTION_ALL
	global_n
#elif INTERACTION_ONLY_PLANET_TRACER
	global_n_p
#else
	0
#endif
	;++j){

#if INDIRECT_TERM
    a_0 += Acceleration_indirect(j,k,ele,x_0,r_0);
#endif
    
    if(i!=j){
      a_0 += Acceleration_ij(i,j,k,ele,x_0,abs_r2);	  
    }
  }

    
  return a_0;

  clock_t end = clock();
  exetime.All_Acceleration += (double)(end-start)/CLOCKS_PER_SEC;
}

/*全加加速度*/
double All_dAcceleration(int i,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v[],double r_dot_v_ij[],double r_0[],double abs_r2[]){
  clock_t start = clock();
  
  int j;
  double adot_0;
  
  adot_0 = External_dAcceleration(i,k,x_0,v_0,r_0,r_dot_v);

  for(j=1;j<=
#if INTERACTION_ALL
	global_n
#elif INTERACTION_ONLY_PLANET_TRACER
	global_n_p
#else
	0
#endif
	;++j){

#if INDIRECT_TERM
    adot_0 += dAcceleration_indirect(j,k,ele,x_0,v_0,r_0,r_dot_v);
#endif
    
    if(i!=j){
      adot_0 += dAcceleration_ij(i,j,k,ele,x_0,v_0,r_dot_v_ij,abs_r2);
    } 
  }
  
  return adot_0;

  clock_t end = clock();
  exetime.All_dAcceleration += (double)(end-start)/CLOCKS_PER_SEC;
}


#include "hybrid.h"


/*エネルギー計算*/
double Calculate_Energy(struct orbital_elements ele[],double x_c[][4],double v_c[][4],double v2_c[],double r_c[],double abs_r[],double abs_r2[],double abs_v[],double abs_v2[],double r_dot_v_ij[]){

  int i,j;
  double rij1;
  double r1;
  double E[global_n+1];
  double E_tot=0.0;
  
  for(i=1;i<=global_n;++i){
    E[i] = 0.5*ele[i].mass*v2_c[i];
    for(j=1;j<=global_n;++j){
      if(i!=j){
	abs_r2[j] = SquareOfRelativeDistance(i,j,x_c); //絶対値2乗
	abs_v2[j] = SquareOfRelativeVelocity(i,j,v_c);
	r_dot_v_ij[j] = RelativeInnerProduct(i,j,x_c,v_c);  //r_ij,v_ijの内積 
	    
	abs_r[j] = sqrt(abs_r2[j]); //絶対値
	abs_v[j] = sqrt(abs_v2[j]);
	
	rij1 = 1.0/abs_r[j];
	
	E[i] += -0.5*G*ele[i].mass*ele[j].mass*rij1;  //エネルギー計算	
      }
    }  //j loop
    r1 = 1.0/r_c[i];
    E_tot += - G*M_0*ele[i].mass*r1 + E[i];
  }  //i loop
  return E_tot;
}

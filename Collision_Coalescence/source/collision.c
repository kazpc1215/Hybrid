#include "hybrid.h"

void Coalescence(int i,struct orbital_elements ele[],double x_p[][4],double abs_r[],double abs_r2[]){

  int j;
  for(j=1;j<=global_n;++j){
    if(i!=j){
      abs_r2[j] = SquareOfRelativeDistance(i,j,x_p); //i,j 絶対値2乗
      abs_r[j] = sqrt(abs_r2[j]); //i,j 絶対値
    }
  }
  
  
}

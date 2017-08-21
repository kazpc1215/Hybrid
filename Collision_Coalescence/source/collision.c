#include "hybrid.h"

void Coalescence(struct orbital_elements ele[],double x_p[][4],double abs_r[],double abs_r2[]){

  int i,j;

  for(i=1;i<=global_n-1;++i){
    for(j=i+1;j<=global_n;++j){
      abs_r2[j] = SquareOfRelativeDistance(i,j,x_p); //i,j 絶対値2乗
      abs_r[j] = sqrt(abs_r2[j]); //i,j 絶対値
      
      if(abs_r[j] < ele[i].radius + ele[j].radius){
	printf("collision i=%d, j=%d\n",i,j);
      }
      
    }
  }
  
}

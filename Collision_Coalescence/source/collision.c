#include "hybrid.h"

int Collision_Judgement(struct orbital_elements ele[],double x_p[][4],double abs_r[],double abs_r2[],int *i_col,int *j_col){

  int i,j;
  
  (*i_col) = 0;
  (*j_col) = 0;

  for(i=1;i<=global_n_p-1;++i){
    for(j=i+1;j<=global_n_p;++j){
      abs_r2[j] = SquareOfRelativeDistance(i,j,x_p); //i,j 絶対値2乗.
      abs_r[j] = sqrt(abs_r2[j]); //i,j 絶対値.
      
      if(abs_r[j] < ele[i].radius + ele[j].radius){
	(*i_col) = i;
	(*j_col) = j;
	return 1;  //衝突した場合.
      }
    }
  }

  return 0;  //衝突しない場合.
}

/*
void Energy_Correction(){

}
*/

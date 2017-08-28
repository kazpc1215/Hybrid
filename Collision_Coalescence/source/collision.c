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


void Energy_Correction(int i_col,int j_col,double x_0[][4],double v_0[][4],struct orbital_elements ele[],double *dE_heat,double *dE_grav,double *dE_c){
  
  double m_1 = ele[i_col].mass;
  double m_2 = ele[j_col].mass;
  double abs_v2 = SquareOfRelativeVelocity(i_col,j_col,v_0);  //相対速度.
  double r_p12 = ele[i_col].radius + ele[j_col].radius;  //2粒子間の距離（物理半径の和）.
  double r_g12 = RadiusFromCenter(0,x_0);  //重心と中心星との距離.
  double r_1 = RadiusFromCenter(i_col,x_0);
  double r_2 = RadiusFromCenter(j_col,x_0);
  

  (*dE_heat) = - 0.5*m_1*m_2/(m_1+m_2)*abs_v2;  //完全合体することで、相対速度分の運動エネルギーが熱エネルギーとなって散逸する.

  (*dE_grav) = G*m_1*m_2/r_p12;  //2粒子間の距離に対応する相互重力エネルギーがなくなっている.

  (*dE_c) = G*M_0*(- (m_1+m_2)/r_g12 + m_1/r_1 + m_2/r_2);  //中心星ポテンシャルエネルギーが変わる.

  printf("dE_heat=%e\tdE_grav=%e\tdE_c=%e\n",(*dE_heat),(*dE_grav),(*dE_c));

}



void Coalescence(int i_col,int j_col,double x_0[][4],double v_0[][4],struct orbital_elements ele[]){

  int k;
  
  //i_colを新しい合体粒子の番号にする.
	ele[i_col].mass = ele[0].mass;
	ele[i_col].radius = cbrt(3.0/4.0/M_PI*ele[i_col].mass*1.989E33/PLANET_DENSITY)/1.496E13;
	for(k=1;k<=3;++k){
	  x_0[i_col][k] = x_0[0][k];
	  v_0[i_col][k] = v_0[0][k];
	}
	
	//j_colとglobal_n_pを入れ替える.
	ele[0] = ele[j_col];  //構造体のためswap関数は使えない. 0番目の要素はコピーに使うだけ.
	ele[j_col] = ele[global_n_p];
	ele[global_n_p] = ele[0];
	for(k=1;k<=3;++k){
	  swap(&x_0[j_col][k],&x_0[global_n_p][k]);
	  swap(&v_0[j_col][k],&v_0[global_n_p][k]);
	}
	
	//global_n_pとglobal_nを入れ替える.
	ele[0] = ele[global_n_p];  //構造体のためswap関数は使えない. 0番目の要素はコピーに使うだけ.
	ele[global_n_p] = ele[global_n];
	ele[global_n] = ele[0];
	for(k=1;k<=3;++k){
	  swap(&x_0[global_n_p][k],&x_0[global_n][k]);
	  swap(&v_0[global_n_p][k],&v_0[global_n][k]);
	}
	
	//global_nとglobal_n_pを1つ減らす.
	global_n--;
	global_n_p--;
  
}

#include "hybrid.h"
#include "func.h"


#if COLLISION
bool Collision_Judgement(const struct orbital_elements *ele_p,const double x_p[][4],double abs_r[],int *i_col,int *j_col){

#if EXECUTION_TIME
  uint64_t start = mach_absolute_time();
#endif

  int i,j;

  for(i=1;i<=global_n_p-1;++i){
    for(j=i+1;j<=global_n_p;++j){
      abs_r[j] = RelativeDistance(i,j,x_p);  //絶対値.
      if(abs_r[j] < ((ele_p+i)->radius) + ((ele_p+j)->radius)){
	(*i_col) = i;
	(*j_col) = j;

#if EXECUTION_TIME
	uint64_t end = mach_absolute_time();
	exetime.Collision_Judgement += (double)(end-start) * sTimebaseInfo.numer / sTimebaseInfo.denom;
#endif
	return (TRUE);  //衝突した場合.
      }
    }
  }

#if EXECUTION_TIME
  uint64_t end = mach_absolute_time();
  exetime.Collision_Judgement += (double)(end-start) * sTimebaseInfo.numer / sTimebaseInfo.denom;
#endif
  return (FALSE);  //衝突しない場合.
}
#endif


#if COLLISION
void Energy_Correction(int i_col,int j_col,const double x_0[][4],const double v_0[][4],const struct orbital_elements *ele_p,double *dE_heat,double *dE_grav,double *dE_c,double *v_imp){

  double m_1 = ((ele_p+i_col)->mass);
  double m_2 = ((ele_p+j_col)->mass);
  double abs_v2 = SquareOfRelativeVelocity(i_col,j_col,v_0);  //相対速度2乗.
  double r_p12 = RelativeDistance(i_col,j_col,x_0);  //2粒子間の距離.
  double r_g12 = RadiusFromCenter(0,x_0);  //2粒子の重心と中心星との距離.
  double r_1 = RadiusFromCenter(i_col,x_0);
  double r_2 = RadiusFromCenter(j_col,x_0);


  (*dE_heat) = - 0.5*m_1*m_2/(m_1+m_2)*abs_v2;  //完全合体することで、相対速度分の運動エネルギーが熱エネルギーとなって散逸する.

#ifndef G
  (*dE_grav) = m_1*m_2/r_p12;  //2粒子間の距離に対応する相互重力エネルギーがなくなっている.
#else
  (*dE_grav) = G*m_1*m_2/r_p12;  //2粒子間の距離に対応する相互重力エネルギーがなくなっている.
#endif

#if !defined(G) && !defined(M_0)
  (*dE_c) = (- (m_1+m_2)/r_g12 + m_1/r_1 + m_2/r_2);  //中心星ポテンシャルエネルギーが変わる.
#else
  (*dE_c) = G*M_0*(- (m_1+m_2)/r_g12 + m_1/r_1 + m_2/r_2);  //中心星ポテンシャルエネルギーが変わる.
#endif

  (*v_imp) = sqrt(abs_v2);

  printf("dE_heat=%e\tdE_grav=%e\tdE_c=%e\tv_imp=%e\n",(*dE_heat),(*dE_grav),(*dE_c),(*v_imp));

  return;
}
#endif


#if COLLISION
void Coalescence(int i_col,int j_col,double x_0[][4],double v_0[][4],struct orbital_elements *ele_p){

  int k;

  //i_colを新しい合体粒子の番号にする.
  ((ele_p+i_col)->mass) = ((ele_p+i_col)->mass) + ((ele_p+j_col)->mass);
  ((ele_p+i_col)->radius) = cbrt(3.0/4.0/M_PI*((ele_p+i_col)->mass)*1.989E33/PLANET_DENSITY)/1.496E13;
  for(k=1;k<=3;++k){
    x_0[i_col][k] = x_0[0][k];
    v_0[i_col][k] = v_0[0][k];
  }

  //j_colとglobal_n_pを入れ替える.
  *(ele_p+0) = *(ele_p+j_col);  //構造体のためSwap関数は使えない. 0番目の要素はコピーに使うだけ.
  *(ele_p+j_col) = *(ele_p+global_n_p);
  *(ele_p+global_n_p) = *(ele_p+0);
  for(k=1;k<=3;++k){
    Swap_double(&x_0[j_col][k],&x_0[global_n_p][k]);
    Swap_double(&v_0[j_col][k],&v_0[global_n_p][k]);
  }

#if N_tr != 0
  //global_n_pとglobal_nを入れ替える.
  *(ele_p+0) = *(ele_p+global_n_p);  //構造体のためSWAPマクロは使えない. 0番目の要素はコピーに使うだけ.
  *(ele_p+global_n_p) = *(ele_p+global_n);
  *(ele_p+global_n) = *(ele_p+0);
  for(k=1;k<=3;++k){
    Swap_double(&x_0[global_n_p][k],&x_0[global_n][k]);
    Swap_double(&v_0[global_n_p][k],&v_0[global_n][k]);
  }
#endif

  //global_n_pを1つ減らす.
  global_n_p--;
  global_n = global_n_p + N_tr;

  return;
}
#endif

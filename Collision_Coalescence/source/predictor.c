#include "hybrid.h"

/*予測子*/
void Predictor(int i,double x_0[][4],double v_0[][4],double a_0[][4],double adot_0[][4],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double Dt[]){
  int k;
  
  //printf("Dt[%d]=%f",i,Dt[i]);
  for(k=1;k<=3;++k){
    x_p[i][k] = x_0[i][k] + v_0[i][k]*Dt[i] + a_0[i][k]*Dt[i]*Dt[i]/2.0 + adot_0[i][k]*Dt[i]*Dt[i]*Dt[i]/6.0;
    v_p[i][k] = v_0[i][k] + a_0[i][k]*Dt[i] + adot_0[i][k]*Dt[i]*Dt[i]/2.0;
  }
  
  //printf("predictor\tx_p[%d][1]=%f\tx_p[%d][2]=%f\tx_p[%d][3]=%f\n",i,x_p[i][1],i,x_p[i][2],i,x_p[i][3]);
  //printf("predictor\tv_p[%d][1]=%f\tv_p[%d][2]=%f\tv_p[%d][3]=%f\n",i,v_p[i][1],i,v_p[i][2],i,v_p[i][3]);

  r_p[i] = RadiusFromCenter(i,x_p);  //中心星からの距離.
  v2_p[i] = SquareOfVelocity(i,v_p); //速度の2乗.

}

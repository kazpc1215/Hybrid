#include "hybrid.h"
#include "func.h"


/*予測子*/
void Predictor(int i,const double x_0[][4],const double v_0[][4],const double a_0[][4],const double adot_0[][4],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double r_dot_v[],const double Dt[]){

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
  r_dot_v[i] = InnerProduct(i,x_p,v_p);  //r_i,v_iの内積.

  return;
}


/*i_sys のみの修正子*/
void Corrector_sys(int i_sys,const struct orbital_elements *ele_p,const double x_p[][4],const double v_p[][4],const double r_p[],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double r_dot_v[],const double a_0[][4],const double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],const double dt_[]){

  int j,k;
  double abs_r[global_n+1],r_dot_v_ij[global_n+1];
  double a_tmp[4]={},adot_tmp[4]={},adot2_dt2_tmp[4]={},adot3_dt3_tmp[4]={};
  double x_c_tmp[4]={},v_c_tmp[4]={};


  for(j=1;j<=global_n;++j){
    if(i_sys!=j){
      abs_r[j] = RelativeDistance(i_sys,j,x_p);  //絶対値.
      r_dot_v_ij[j] = RelativeInnerProduct(i_sys,j,x_p,v_p);  //r_ij,v_ijの内積.
    }else{
      abs_r[i_sys] = 0.0;
      r_dot_v_ij[i_sys] = 0.0;
    }
  }


  for(k=1;k<=3;++k){
    a_tmp[k] = All_Acceleration(i_sys,k,ele_p,x_p,r_p,abs_r);
    adot_tmp[k] = All_dAcceleration(i_sys,k,ele_p,x_p,v_p,r_dot_v,r_dot_v_ij,r_p,abs_r);
  }


  /*for(k=1;k<=3;++k){
    printf("a[%d][%d]=%f\tadot[%d][%d]=%f\n",i_sys,k,a[i_sys][k],i_sys,k,adot[i_sys][k]);
    }*/

  for(k=1;k<=3;++k){  //修正子.

    adot2_dt2_tmp[k] = -6*(a_0[i_sys][k] - a_tmp[k]) - (4*adot_0[i_sys][k] + 2*adot_tmp[k])*dt_[i_sys]; //第2次導関数.
    adot3_dt3_tmp[k] = 12*(a_0[i_sys][k] - a_tmp[k]) + 6*(adot_0[i_sys][k] + adot_tmp[k])*dt_[i_sys]; //第3次導関数.

    x_c_tmp[k] = x_p[i_sys][k] + adot2_dt2_tmp[k]*dt_[i_sys]*dt_[i_sys]/24.0 + adot3_dt3_tmp[k]*dt_[i_sys]*dt_[i_sys]/120.0;
    v_c_tmp[k] = v_p[i_sys][k] + adot2_dt2_tmp[k]*dt_[i_sys]/6.0 +adot3_dt3_tmp[k]*dt_[i_sys]/24.0;
  }  //k loop


  r_c[i_sys] = sqrt(x_c_tmp[1]*x_c_tmp[1] + x_c_tmp[2]*x_c_tmp[2] + x_c_tmp[3]*x_c_tmp[3]);
  v2_c[i_sys] = v_c_tmp[1]*v_c_tmp[1] + v_c_tmp[2]*v_c_tmp[2] + v_c_tmp[3]*v_c_tmp[3];
  r_dot_v[i_sys] = x_c_tmp[1]*v_c_tmp[1] + x_c_tmp[2]*v_c_tmp[2] + x_c_tmp[3]*v_c_tmp[3];


  for(k=1;k<=3;++k){
    a[i_sys][k] = a_tmp[k];
    adot[i_sys][k] = adot_tmp[k];
    adot2_dt2[i_sys][k] = adot2_dt2_tmp[k];
    adot3_dt3[i_sys][k] = adot3_dt3_tmp[k];
    x_c[i_sys][k] = x_c_tmp[k];
    v_c[i_sys][k] = v_c_tmp[k];
  }

  return;
}


/*i_sys のみのiteration*/
void Iteration_sys(int i_sys,const struct orbital_elements *ele_p,const double x_p[][4],const double v_p[][4],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double r_dot_v[],const double a_0[][4],const double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],const double dt_[]){

  int j,k;
  double abs_r[global_n+1],r_dot_v_ij[global_n+1];
  double a_tmp[4]={},adot_tmp[4]={},adot2_dt2_tmp[4]={},adot3_dt3_tmp[4]={};
  double x_c_tmp[4]={},v_c_tmp[4]={};


  for(j=1;j<=global_n;++j){
    if(i_sys!=j){
      abs_r[j] = RelativeDistance(i_sys,j,x_c);  //絶対値.
      r_dot_v_ij[j] = RelativeInnerProduct(i_sys,j,x_c,v_c);  //r_ij,v_ijの内積.
    }else{
      abs_r[i_sys] = 0.0;
      r_dot_v_ij[i_sys] = 0.0;
    }
  }  //j loop


  for(k=1;k<=3;++k){
    a_tmp[k] = All_Acceleration(i_sys,k,ele_p,x_c,r_c,abs_r);
    adot_tmp[k] = All_dAcceleration(i_sys,k,ele_p,x_c,v_c,r_dot_v,r_dot_v_ij,r_c,abs_r);
  }


  //修正子 (iteration).
  for(k=1;k<=3;++k){
    adot2_dt2_tmp[k] = -6*(a_0[i_sys][k] - a_tmp[k]) - (4*adot_0[i_sys][k] + 2*adot_tmp[k])*dt_[i_sys]; //第2次導関数.
    adot3_dt3_tmp[k] = 12*(a_0[i_sys][k] - a_tmp[k]) + 6*(adot_0[i_sys][k] + adot_tmp[k])*dt_[i_sys]; //第3次導関数.
    x_c_tmp[k] = x_p[i_sys][k] + adot2_dt2_tmp[k]*dt_[i_sys]*dt_[i_sys]/24.0 + adot3_dt3_tmp[k]*dt_[i_sys]*dt_[i_sys]/120.0;
    v_c_tmp[k] = v_p[i_sys][k] + adot2_dt2_tmp[k]*dt_[i_sys]/6.0 +adot3_dt3_tmp[k]*dt_[i_sys]/24.0;
  }  //k loop


  r_c[i_sys] = sqrt(x_c_tmp[1]*x_c_tmp[1] + x_c_tmp[2]*x_c_tmp[2] + x_c_tmp[3]*x_c_tmp[3]);
  v2_c[i_sys] = v_c_tmp[1]*v_c_tmp[1] + v_c_tmp[2]*v_c_tmp[2] + v_c_tmp[3]*v_c_tmp[3];
  r_dot_v[i_sys] = x_c_tmp[1]*v_c_tmp[1] + x_c_tmp[2]*v_c_tmp[2] + x_c_tmp[3]*v_c_tmp[3];


  for(k=1;k<=3;++k){
    a[i_sys][k] = a_tmp[k];
    adot[i_sys][k] = adot_tmp[k];
    adot2_dt2[i_sys][k] = adot2_dt2_tmp[k];
    adot3_dt3[i_sys][k] = adot3_dt3_tmp[k];
    x_c[i_sys][k] = x_c_tmp[k];
    v_c[i_sys][k] = v_c_tmp[k];
  }

  return;
}


/*全加速度*/
double All_Acceleration(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double r_0[],const double abs_r[]){
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
    a_0 += Acceleration_indirect(j,k,ele_p,x_0,r_0);
#endif

    if(i!=j){
      a_0 += Acceleration_ij(i,j,k,ele_p,x_0,abs_r);
    }
  }

  return a_0;
}


/*全加加速度*/
double All_dAcceleration(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double v_0[][4],const double r_dot_v[],const double r_dot_v_ij[],const double r_0[],const double abs_r[]){ 
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
    adot_0 += dAcceleration_indirect(j,k,ele_p,x_0,v_0,r_0,r_dot_v);
#endif

    if(i!=j){
      adot_0 += dAcceleration_ij(i,j,k,ele_p,x_0,v_0,r_dot_v_ij,abs_r);
    }
  }

  return adot_0;
}


/*相互重力加速度*/
double Acceleration_ij(int i,int j,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double abs_r[]){
  double rij3;

#ifndef EPSILON
  rij3 = abs_r[j]*abs_r[j]*abs_r[j];
#else
  rij3 = (abs_r[j]*abs_r[j] + EPSILON*EPSILON)*sqrt(abs_r[j]*abs_r[j] + EPSILON*EPSILON);
#endif
  rij3 = 1.0/rij3;

#ifndef G
  return ((ele_p+j)->mass)*(x_0[j][k] - x_0[i][k])*rij3;
#else
  return G*((ele_p+j)->mass)*(x_0[j][k] - x_0[i][k])*rij3;
#endif
}


/*相互重力加加速度*/
double dAcceleration_ij(int i,int j,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double v_0[][4],const double r_dot_v_ij[],const double abs_r[]){
  double rij3;
  double rij5;

#ifndef EPSILON
  rij3 = abs_r[j]*abs_r[j]*abs_r[j];
  rij5 = abs_r[j]*abs_r[j]*abs_r[j]*abs_r[j]*abs_r[j];
#else
  rij3 = (abs_r[j]*abs_r[j] + EPSILON*EPSILON)*sqrt(abs_r[j]*abs_r[j] + EPSILON*EPSILON);
  rij5 = (abs_r[j]*abs_r[j] + EPSILON*EPSILON)*(abs_r[j]*abs_r[j] + EPSILON*EPSILON)*sqrt(abs_r[j]*abs_r[j] + EPSILON*EPSILON);
#endif
  rij3 = 1.0/rij3;
  rij5 = 1.0/rij5;

#ifndef G
  return ((ele_p+j)->mass)*((v_0[j][k] - v_0[i][k])*rij3 - 3*r_dot_v_ij[j]*(x_0[j][k] - x_0[i][k])*rij5);
#else
  return G*((ele_p+j)->mass)*((v_0[j][k] - v_0[i][k])*rij3 - 3*r_dot_v_ij[j]*(x_0[j][k] - x_0[i][k])*rij5);
#endif
}


/*加速度indirect項*/
double Acceleration_indirect(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double r_0[]){
  double r3;
  r3 = r_0[i]*r_0[i]*r_0[i];
  r3 = 1.0/r3;

#ifndef G
  return -1*((ele_p+i)->mass)*x_0[i][k]*r3;
#else
  return -1*G*((ele_p+i)->mass)*x_0[i][k]*r3;
#endif
}


/*加加速度indirect項*/
double dAcceleration_indirect(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double v_0[][4],const double r_0[],const double r_dot_v[]){
  double r3;
  double r5;
  r3 = r_0[i]*r_0[i]*r_0[i];
  r3 = 1.0/r3;
  r5 = r_0[i]*r_0[i]*r_0[i]*r_0[i]*r_0[i];
  r5 = 1.0/r5;

#ifndef G
  return -1*((ele_p+i)->mass)*(v_0[i][k]*r3 - 3*r_dot_v[i]*x_0[i][k]*r5);
#else
  return -1*G*((ele_p+i)->mass)*(v_0[i][k]*r3 - 3*r_dot_v[i]*x_0[i][k]*r5);
#endif
}


/*外力加速度*/
double External_Acceleration(int i,int k,const double x_0[][4],const double r_0[]){
  double r3;
  r3 = r_0[i]*r_0[i]*r_0[i];
  r3 = 1.0/r3;

#if !defined(G) && !defined(M_0)
  return -1*x_0[i][k]*r3;
#else
  return -1*G*M_0*x_0[i][k]*r3;
#endif
}


/*外力加加速度*/
double External_dAcceleration(int i,int k,const double x_0[][4],const double v_0[][4],const double r_0[],const double r_dot_v[]){
  double r3;
  double r5;
  r3 = r_0[i]*r_0[i]*r_0[i];
  r3 = 1.0/r3;
  r5 = r_0[i]*r_0[i]*r_0[i]*r_0[i]*r_0[i];
  r5 = 1.0/r5;

#if !defined(G) && !defined(M_0)
  return -1*(v_0[i][k]*r3 - 3*r_dot_v[i]*x_0[i][k]*r5);
#else
  return -1*G*M_0*(v_0[i][k]*r3 - 3*r_dot_v[i]*x_0[i][k]*r5);
#endif
}

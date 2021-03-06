#include "hybrid.h"
#include "func.h"


/*軌道要素計算*/
void Calculate_OrbitalElements(int i,CONST double x_c[][4],CONST double v_c[][4],struct orbital_elements *ele_p,double P[][4],double Q[][4],CONST double r_c[],CONST double v2_c[],CONST double r_dot_v[]){

#if INDIRECT_TERM

#if !defined(G) && !defined(M_0)
  double mu = 1.0*(1.0 + ((ele_p+i)->mass));
#else
  double mu = G*(M_0 + ((ele_p+i)->mass));
#endif

#else

#if !defined(G) && !defined(M_0)
  double mu = 1.0;
#else
  double mu = G*M_0;
#endif

#endif

  int k;
  double esin_u;
  double ecos_u;
  double sin_inc;
  double cos_inc;
  double sin_omega;
  double cos_omega;
  double sin_Omega;
  double cos_Omega;
  double radian;


  /*
  if(isnan(x_c[i][1])||isnan(x_c[i][2])||isnan(x_c[i][3])){
    printf("i=%d\tx is nan.\t[1]=%f\t[2]=%f\t[3]=%f\n",i,x_c[i][1],x_c[i][2],x_c[i][3]);
  }
  if(isnan(v_c[i][1])||isnan(v_c[i][2])||isnan(v_c[i][3])){
    printf("i=%d\tx is nan.\t[1]=%f\t[2]=%f\t[3]=%f\n",i,v_c[i][1],v_c[i][2],v_c[i][3]);
  }
  if(isnan(r_c[i])){
    printf("i=%d\tr is nan.\n",i);
  }
  if(isnan(v2_c[i])){
    printf("i=%d\tv2 is nan.\n",i);
  }
  if(isnan(r_dot_v[i])){
    printf("i=%d\tr_dot_v is nan.\n",i);
  }
  */

  ((ele_p+i)->axis) = 1.0/(2.0/r_c[i] - v2_c[i]/mu);


  if(isnan((ele_p+i)->axis)){
    printf("i=%d\taxis is nan.\n",i);
  }


  if(((ele_p+i)->axis)<0.0){
    printf("i=%d\taxis=%e < 0 双曲線軌道\n",i,((ele_p+i)->axis));
    ((ele_p+i)->ecc) = NAN;
    ((ele_p+i)->u) = NAN;
    ((ele_p+i)->inc) = NAN;
    ((ele_p+i)->omega) = NAN;
    ((ele_p+i)->Omega) = NAN;
    ((ele_p+i)->r_h) = NAN;

    //printf("\tr=%f[AU]\tR_planet=%f\n",sqrt((x_c[i][1]-x_c[PLANET_NO][1])*(x_c[i][1]-x_c[PLANET_NO][1])+(x_c[i][2]-x_c[PLANET_NO][2])*(x_c[i][2]-x_c[PLANET_NO][2])+(x_c[i][3]-x_c[PLANET_NO][3])*(x_c[i][3]-x_c[PLANET_NO][3])),PLANET_RADIUS);
  }


  ((ele_p+i)->ecc) = sqrt((1.0-r_c[i]/((ele_p+i)->axis))*(1.0-r_c[i]/((ele_p+i)->axis)) + r_dot_v[i]*r_dot_v[i]/mu/((ele_p+i)->axis));


  //printf("i=%d\tecc=%f\n",i,ele[i].ecc);
  if(isnan((ele_p+i)->ecc)){
    printf("i=%d\tecc is nan.\n",i);
  }


  if(((ele_p+i)->ecc)==0.0){
    ((ele_p+i)->u) = 0.0;
  }else{

    esin_u = r_dot_v[i]/sqrt(mu*((ele_p+i)->axis));
    ecos_u = 1.0-r_c[i]/((ele_p+i)->axis);
    radian = atan2(esin_u,ecos_u);
    if(radian<0.0){
      ((ele_p+i)->u) = radian + 2.0*M_PI;
    }else{
      ((ele_p+i)->u) = radian;
    }
  }

  /*
  if(isnan(ele[i].u)){
    printf("i=%d\tu is nan.\n",i);
  }
  */


  for(k=1;k<=3;++k){

    P[i][k] = x_c[i][k]*cos(((ele_p+i)->u))/r_c[i] - sqrt(((ele_p+i)->axis)/mu)*v_c[i][k]*sin(((ele_p+i)->u));
    Q[i][k] = (x_c[i][k]*sin(((ele_p+i)->u))/r_c[i] + sqrt(((ele_p+i)->axis)/mu)*v_c[i][k]*(cos(((ele_p+i)->u))-((ele_p+i)->ecc)))/sqrt(1.0-((ele_p+i)->ecc));
  }


  if(isnan(P[i][1])||isnan(P[i][2])||isnan(P[i][3])){
    printf("i=%d\tP is nan.\t[1]=%f\t[2]=%f\t[3]=%f\n",i,P[i][1],P[i][2],P[i][3]);
  }
  if(isnan(Q[i][1])||isnan(Q[i][2])||isnan(Q[i][3])){
    printf("i=%d\tQ is nan.\t[1]=%f\t[2]=%f\t[3]=%f\n",i,Q[i][1],Q[i][2],Q[i][3]);
  }


  sin_inc = sqrt(P[i][3]*P[i][3] + Q[i][3]*Q[i][3]);
  cos_inc = P[i][1]*Q[i][2] - P[i][2]*Q[i][1];
  radian = atan2(sin_inc,cos_inc);


  if(radian<0.0){
    ((ele_p+i)->inc) = radian + 2.0*M_PI;
  }else{
    ((ele_p+i)->inc) = radian;
  }


  sin_omega = P[i][3]/sin_inc;
  cos_omega = Q[i][3]/sin_inc;
  radian = atan2(sin_omega,cos_omega);
  if(radian<0.0){
    ((ele_p+i)->omega) = radian + 2.0*M_PI;
  }else{
    ((ele_p+i)->omega) = radian;
  }


  sin_Omega = (P[i][2]*Q[i][3] - Q[i][2]*P[i][3])/sin_inc;
  cos_Omega = (P[i][1]*Q[i][3] - Q[i][1]*P[i][3])/sin_inc;
  radian = atan2(sin_Omega,cos_Omega);
  if(radian<0.0){
    ((ele_p+i)->Omega) = radian + 2.0*M_PI;
  }else{
    ((ele_p+i)->Omega) = radian;
  }


  if(sin_inc==0.0){
    ((ele_p+i)->omega) = 0.0;
    ((ele_p+i)->Omega) = 0.0;
  }


#ifndef M_0
  ((ele_p+i)->r_h) = ((ele_p+i)->axis)*cbrt(((ele_p+i)->mass)/3.0);
#else
  ((ele_p+i)->r_h) = ((ele_p+i)->axis)*cbrt(((ele_p+i)->mass)/M_0/3.0);
#endif


  if(isnan((ele_p+i)->inc)){
    printf("i=%d\tinc is nan.\n",i);
  }
  if(isnan((ele_p+i)->omega)){
    printf("i=%d\tomega is nan.\n",i);
  }
  if(isnan((ele_p+i)->Omega)){
    printf("i=%d\tOmega is nan.\n",i);
  }


  return;
}


/*P計算*/
double Calculate_P(int i,int k,CONST struct orbital_elements *ele_p){
  if(k==1){
    return cos(((ele_p+i)->omega))*cos(((ele_p+i)->Omega)) - sin(((ele_p+i)->omega))*sin(((ele_p+i)->Omega))*cos(((ele_p+i)->inc));
  }else if(k==2){
    return cos(((ele_p+i)->omega))*sin(((ele_p+i)->Omega)) + sin(((ele_p+i)->omega))*cos(((ele_p+i)->Omega))*cos(((ele_p+i)->inc));
  }else{
    return sin(((ele_p+i)->omega))*sin(((ele_p+i)->inc));
  }
}


/*Q計算*/
double Calculate_Q(int i,int k,CONST struct orbital_elements *ele_p){
  if(k==1){
    return -sin(((ele_p+i)->omega))*cos(((ele_p+i)->Omega)) - cos(((ele_p+i)->omega))*sin(((ele_p+i)->Omega))*cos(((ele_p+i)->inc));
  }else if(k==2){
    return -sin(((ele_p+i)->omega))*sin(((ele_p+i)->Omega)) + cos(((ele_p+i)->omega))*cos(((ele_p+i)->Omega))*cos(((ele_p+i)->inc));
  }else{
    return cos(((ele_p+i)->omega))*sin(((ele_p+i)->inc));
  }
}


/*初期位置、速度計算*/
void InitialCondition(int i,double P[][4],double Q[][4],double x_0[][4],double v_0[][4],double v2_0[],double r_dot_v[],double r_0[],CONST struct orbital_elements *ele_p){

#if INDIRECT_TERM

#if !defined(G) && !defined(M_0)
  double mu = 1.0*(1.0 + ((ele_p+i)->mass));
#else
  double mu = G*(M_0 + ((ele_p+i)->mass));
#endif

#else

#if !defined(G) && !defined(M_0)
  double mu = 1.0;
#else
  double mu = G*M_0;
#endif

#endif

  int k;
  for(k=1;k<=3;k++){
    P[i][k] = Calculate_P(i,k,ele_p);
    Q[i][k] = Calculate_Q(i,k,ele_p);

    x_0[i][k] = ((ele_p+i)->axis)*P[i][k]*(cos(((ele_p+i)->u))-((ele_p+i)->ecc)) + ((ele_p+i)->axis)*sqrt(1.0-((ele_p+i)->ecc)*((ele_p+i)->ecc))*Q[i][k]*sin(((ele_p+i)->u));
  }
  //printf("x=%f\ty=%f\tz=%f\n",x_0[i][1],x_0[i][2],x_0[i][3]);

  r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離.


  for(k=1;k<=3;++k){
    v_0[i][k] = sqrt(mu/((ele_p+i)->axis))/r_0[i]*(-((ele_p+i)->axis)*P[i][k]*sin(((ele_p+i)->u)) + ((ele_p+i)->axis)*sqrt(1.0-((ele_p+i)->ecc)*((ele_p+i)->ecc))*Q[i][k]*cos(((ele_p+i)->u)));
  }

  r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積.
  v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗.
  //printf("vx=%f\tvy=%f\tvz=%f\n",v_0[i][1],v_0[i][2],v_0[i][3]);

  return;
}









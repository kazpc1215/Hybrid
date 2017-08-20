#include "hybrid.h"

/*軌道要素計算*/
int Calculate_OrbitalElements(int i,double x_c[][4],double v_c[][4],struct orbital_elements ele[],double P[][4],double Q[][4],double r_c[],double v2_c[],double r_dot_v[]){
  
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

  
  ele[i].axis = 1.0/(2.0/r_c[i] - v2_c[i]/(G*M_0));

  if(isnan(ele[i].axis)){
    printf("i=%d\taxis is nan.\n",i);
  }

  if(ele[i].axis<0.0){
    printf("i=%d\taxis=%e < 0 双曲線軌道. axis -> -1*axis\n",i,ele[i].axis);
    ele[i].axis *= -1.0;
    //printf("\tr=%f[AU]\tR_planet=%f\n",sqrt((x_c[i][1]-x_c[PLANET_NO][1])*(x_c[i][1]-x_c[PLANET_NO][1])+(x_c[i][2]-x_c[PLANET_NO][2])*(x_c[i][2]-x_c[PLANET_NO][2])+(x_c[i][3]-x_c[PLANET_NO][3])*(x_c[i][3]-x_c[PLANET_NO][3])),PLANET_RADIUS);
  }

  
  ele[i].ecc = sqrt((1.0-r_c[i]/ele[i].axis)*(1.0-r_c[i]/ele[i].axis) + r_dot_v[i]*r_dot_v[i]/(G*M_0*ele[i].axis));

  //printf("i=%d\tecc=%f\n",i,ele[i].ecc);
  if(isnan(ele[i].ecc)){
    printf("i=%d\tecc is nan.\n",i);
  }
  
  if(ele[i].ecc==0.0){
    ele[i].u = 0.0;
  }else{
    esin_u = r_dot_v[i]/sqrt(G*M_0*ele[i].axis);
    ecos_u = 1.0-r_c[i]/ele[i].axis;
    radian = atan2(esin_u,ecos_u);
    if(radian<0.0){
      ele[i].u = radian + 2.0*M_PI;
    }else{
      ele[i].u = radian;
    }
  }

  if(isnan(ele[i].u)){
    printf("i=%d\tu is nan.\n",i);
  }

  
  if(isnan(P[i][1])||isnan(P[i][2])||isnan(P[i][3])){
    printf("i=%d\tpre P is nan.\t[1]=%f\t[2]=%f\t[3]=%f\n",i,P[i][1],P[i][2],P[i][3]);
  }
  if(isnan(Q[i][1])||isnan(Q[i][2])||isnan(Q[i][3])){
    printf("i=%d\tpre Q is nan.\t[1]=%f\t[2]=%f\t[3]=%f\n",i,Q[i][1],Q[i][2],Q[i][3]);
  }

  
  for(k=1;k<=3;++k){
    P[i][k] = x_c[i][k]*cos(ele[i].u)/r_c[i] - sqrt(ele[i].axis/(G*M_0))*v_c[i][k]*sin(ele[i].u);
    Q[i][k] = (x_c[i][k]*sin(ele[i].u)/r_c[i] + sqrt(ele[i].axis/(G*M_0))*v_c[i][k]*(cos(ele[i].u)-ele[i].ecc))/sqrt(fabs(1.0-ele[i].ecc));
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
    ele[i].inc = radian + 2.0*M_PI;
  }else{
    ele[i].inc = radian;
  }


  sin_omega = P[i][3]/sin_inc;
  cos_omega = Q[i][3]/sin_inc;
  radian = atan2(sin_omega,cos_omega);
  if(radian<0.0){
    ele[i].omega = radian + 2.0*M_PI;
  }else{
    ele[i].omega = radian;
  }

  
  sin_Omega = (P[i][2]*Q[i][3] - Q[i][2]*P[i][3])/sin_inc;
  cos_Omega = (P[i][1]*Q[i][3] - Q[i][1]*P[i][3])/sin_inc;
  radian = atan2(sin_Omega,cos_Omega);
  if(radian<0.0){
    ele[i].Omega = radian + 2.0*M_PI;
  }else{
    ele[i].Omega = radian;
  }	  

  
  if(sin_inc==0.0){
    ele[i].omega = 0.0;
    ele[i].Omega = 0.0;
  }
  

  ele[i].r_h = ele[i].axis*cbrt(ele[i].mass/M_0/3.0);

  
  if(isnan(ele[i].inc)){
    printf("i=%d\tinc is nan.\n",i);
  }
  if(isnan(ele[i].omega)){
    printf("i=%d\tomega is nan.\n",i);
  }
  if(isnan(ele[i].Omega)){
    printf("i=%d\tOmega is nan.\n",i);
  }
  

  return 0;
}

/*P計算*/
double Calculate_P(int i,int k,struct orbital_elements ele[]){
  if(k==1){
    return cos(ele[i].omega)*cos(ele[i].Omega) - sin(ele[i].omega)*sin(ele[i].Omega)*cos(ele[i].inc);
  }else if(k==2){
    return cos(ele[i].omega)*sin(ele[i].Omega) + sin(ele[i].omega)*cos(ele[i].Omega)*cos(ele[i].inc);
  }else{
    return sin(ele[i].omega)*sin(ele[i].inc);
  }
}

/*Q計算*/
double Calculate_Q(int i,int k,struct orbital_elements ele[]){
  if(k==1){
    return -sin(ele[i].omega)*cos(ele[i].Omega) - cos(ele[i].omega)*sin(ele[i].Omega)*cos(ele[i].inc);
  }else if(k==2){
    return -sin(ele[i].omega)*sin(ele[i].Omega) + cos(ele[i].omega)*cos(ele[i].Omega)*cos(ele[i].inc);
  }else{
    return cos(ele[i].omega)*sin(ele[i].inc);
  }
}



/*初期位置、速度計算*/
void InitialCondition(int i,double P[][4],double Q[][4],double x_0[][4],double v_0[][4],double v2_0[],double r_dot_v[],double r_0[],struct orbital_elements ele[]){
  int k;
  for(k=1;k<=3;k++){
    P[i][k] = Calculate_P(i,k,ele);
    Q[i][k] = Calculate_Q(i,k,ele);
	
    x_0[i][k] = ele[i].axis*P[i][k]*(cos(ele[i].u)-ele[i].ecc) + ele[i].axis*sqrt(1.0-ele[i].ecc*ele[i].ecc)*Q[i][k]*sin(ele[i].u);
  }
  //printf("x=%f\ty=%f\tz=%f\n",x_0[i][1],x_0[i][2],x_0[i][3]);
           
  r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離


      
  for(k=1;k<=3;++k){
    v_0[i][k] = sqrt(G*M_0/ele[i].axis)/r_0[i]*(-ele[i].axis*P[i][k]*sin(ele[i].u) + ele[i].axis*sqrt(1.0-ele[i].ecc*ele[i].ecc)*Q[i][k]*cos(ele[i].u));
  }

  r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積
  v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗
  //printf("vx=%f\tvy=%f\tvz=%f\n",v_0[i][1],v_0[i][2],v_0[i][3]);
}









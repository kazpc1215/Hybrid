#include "hybrid.h"

/*相互重力加速度*/
double Acceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double abs_r2[]){
  double rij3;
  rij3 = (abs_r2[j] + EPSILON*EPSILON)*sqrt(abs_r2[j] + EPSILON*EPSILON);
  rij3 = 1.0/rij3;

#ifndef G
  return ele[j].mass*(x_0[j][k] - x_0[i][k])*rij3;
#else
  return G*ele[j].mass*(x_0[j][k] - x_0[i][k])*rij3;
#endif
}


/*相互重力加加速度*/
double dAcceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v_ij[],double abs_r2[]){
  double rij3;
  double rij5;
  rij3 = (abs_r2[j] + EPSILON*EPSILON)*sqrt(abs_r2[j] + EPSILON*EPSILON);
  rij3 = 1.0/rij3;
  rij5 = (abs_r2[j] + EPSILON*EPSILON)*(abs_r2[j] + EPSILON*EPSILON)*sqrt(abs_r2[j] + EPSILON*EPSILON);
  rij5 = 1.0/rij5;

#ifndef G
  return ele[j].mass*((v_0[j][k] - v_0[i][k])*rij3 - 3*r_dot_v_ij[j]*(x_0[j][k] - x_0[i][k])*rij5);
#else
  return G*ele[j].mass*((v_0[j][k] - v_0[i][k])*rij3 - 3*r_dot_v_ij[j]*(x_0[j][k] - x_0[i][k])*rij5);
#endif
}


/*加速度indirect項*/
double Acceleration_indirect(int i,int k,struct orbital_elements ele[],double x_0[][4],double r_0[]){
  double r3;
  r3 = r_0[i]*r_0[i]*r_0[i];
  r3 = 1.0/r3;

#ifndef G
  return -1*ele[i].mass*x_0[i][k]*r3;
#else
  return -1*G*ele[j].mass*x_0[j][k]*r3;
#endif
}


/*加加速度indirect項*/
double dAcceleration_indirect(int i,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_0[],double r_dot_v[]){
  double r3;
  double r5;
  r3 = r_0[i]*r_0[i]*r_0[i];
  r3 = 1.0/r3;
  r5 = r_0[i]*r_0[i]*r_0[i]*r_0[i]*r_0[i];
  r5 = 1.0/r5;
  
#ifndef G
  return -1*ele[i].mass*(v_0[i][k]*r3 - 3*r_dot_v[i]*x_0[i][k]*r5);
#else
  return -1*G*ele[j].mass*(v_0[j][k]*r3 - 3*r_dot_v[j]*x_0[i][k]*r5);
#endif
}


/*外力加速度*/
double External_Acceleration(int i,int k,double x_0[][4],double r_0[]){
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
double External_dAcceleration(int i,int k,double x_0[][4],double v_0[][4],double r_0[],double r_dot_v[]){
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


#include "hybrid.h"
#include "func.h"


void Rotation_3D_xaxis(int i,double x_eject[][4],double theta){
  double tmp_y = x_eject[i][2];
  double tmp_z = x_eject[i][3];
  x_eject[i][2] = cos(theta)*tmp_y - sin(theta)*tmp_z;
  x_eject[i][3] = sin(theta)*tmp_y + cos(theta)*tmp_z;
  return;
}


void Rotation_3D_yaxis(int i,double x_eject[][4],double theta){
  double tmp_x = x_eject[i][1];
  double tmp_z = x_eject[i][3];
  x_eject[i][1] = cos(theta)*tmp_x + sin(theta)*tmp_z;
  x_eject[i][3] = - sin(theta)*tmp_x + cos(theta)*tmp_z;
  return;
}


void Rotation_3D_zaxis(int i,double x_eject[][4],double theta){
  double tmp_x = x_eject[i][1];
  double tmp_y = x_eject[i][2];
  x_eject[i][1] = cos(theta)*tmp_x - sin(theta)*tmp_y;
  x_eject[i][2] = sin(theta)*tmp_x + cos(theta)*tmp_y;
  return;
}


void CenterOfGravity(double x_0[][4],double v_0[][4],double x_G[],double v_G[],struct orbital_elements ele[]){
  int i,k;
  double M;

#ifndef M_0
  M = 1.0;
#else
  M = M_0;
#endif
  for(i=1;i<=global_n;++i){
    M += ele[i].mass;
  }
  
  for(k=1;k<=3;++k){
    x_G[k] = 0.0;
    v_G[k] = 0.0;
    for(i=1;i<=global_n;++i){
      x_G[k] += ele[i].mass*x_0[i][k];
      v_G[k] += ele[i].mass*v_0[i][k];
    }
    x_G[k] /= M;
    v_G[k] /= M;
  }
  
  return;
}

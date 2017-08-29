#include "hybrid.h"


/*r_i,v_iの内積*/
double InnerProduct(int i,double x_0[][4],double v_0[][4]){ 
  int k;
  double r_dot_v = 0.0;
  for(k=1;k<=3;k++){
    r_dot_v += x_0[i][k]*v_0[i][k]; 
  }
  return r_dot_v;
}

/*中心星からの距離の2乗*/
double RadiusFromCenter(int i,double x_0[][4]){
  int k;
  double r_0 = 0.0;
  for(k=1;k<=3;k++){
    r_0 += x_0[i][k]*x_0[i][k];  
  }
  r_0 = sqrt(r_0);
  return r_0;
}

/*速度の2乗*/
double SquareOfVelocity(int i,double v_0[][4]){
  int k;
  double v2_0 = 0.0;
  for(k=1;k<=3;k++){
    v2_0 += v_0[i][k]*v_0[i][k]; 
  }
  return v2_0;
}

/*相対距離の2乗*/
double SquareOfRelativeDistance(int i,int j,double x_0[][4]){
  return (x_0[j][1] - x_0[i][1])*(x_0[j][1] - x_0[i][1]) + (x_0[j][2] - x_0[i][2])*(x_0[j][2] - x_0[i][2]) + (x_0[j][3] - x_0[i][3])*(x_0[j][3] - x_0[i][3]);
}

/*相対速度の2乗*/
double SquareOfRelativeVelocity(int i,int j,double v_0[][4]){
  return (v_0[j][1] - v_0[i][1])*(v_0[j][1] - v_0[i][1]) + (v_0[j][2] - v_0[i][2])*(v_0[j][2] - v_0[i][2]) + (v_0[j][3] - v_0[i][3])*(v_0[j][3] - v_0[i][3]);
}

/*r_ij, v_ijの内積*/
double RelativeInnerProduct(int i,int j,double x_0[][4],double v_0[][4]){
  return (x_0[j][1] - x_0[i][1])*(v_0[j][1] - v_0[i][1]) + (x_0[j][2] - x_0[i][2])*(v_0[j][2] - v_0[i][2]) + (x_0[j][3] - x_0[i][3])*(v_0[j][3] - v_0[i][3]);
}




void Rotation_3D_xaxis(int i,double x_eject[][4],double theta){
  double tmp_y = x_eject[i][2];
  double tmp_z = x_eject[i][3];
  x_eject[i][2] = cos(theta)*tmp_y - sin(theta)*tmp_z;
  x_eject[i][3] = sin(theta)*tmp_y + cos(theta)*tmp_z;
}

void Rotation_3D_yaxis(int i,double x_eject[][4],double theta){
  double tmp_x = x_eject[i][1];
  double tmp_z = x_eject[i][3];
  x_eject[i][1] = cos(theta)*tmp_x + sin(theta)*tmp_z;
  x_eject[i][3] = - sin(theta)*tmp_x + cos(theta)*tmp_z;
}

void Rotation_3D_zaxis(int i,double x_eject[][4],double theta){
  double tmp_x = x_eject[i][1];
  double tmp_y = x_eject[i][2];
  x_eject[i][1] = cos(theta)*tmp_x - sin(theta)*tmp_y;
  x_eject[i][2] = sin(theta)*tmp_x + cos(theta)*tmp_y;
}

void swap(double *a, double *b){
  double tmp;
  tmp = (*a);
  (*a) = (*b);
  (*b) = tmp;
}







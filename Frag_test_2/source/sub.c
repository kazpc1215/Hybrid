#include "hybrid.h"


/*r_i,v_iの内積*/
double InnerProduct(int i,double x_0[][4],double v_0[][4],double r_dot_v[]){ 
  int k;
  r_dot_v[i] = 0.0;
  for(k=1;k<=3;k++){
    r_dot_v[i] += x_0[i][k]*v_0[i][k]; 
  }
  return r_dot_v[i];
}

/*中心星からの距離の2乗*/
double RadiusFromCenter(int i,double x_0[][4],double r_0[]){
  int k;
  r_0[i] = 0.0;
  for(k=1;k<=3;k++){
    r_0[i] += x_0[i][k]*x_0[i][k];  
  }
  r_0[i] = sqrt(r_0[i]);
  //printf("r_0[%d]=%f\n",i,r_0[i]);
  return r_0[i];
}

/*速度の2乗*/
double SquareOfVelocity(int i,double v_0[][4],double v2_0[]){
  int k;
  v2_0[i] = 0.0;
  for(k=1;k<=3;k++){
    v2_0[i] += v_0[i][k]*v_0[i][k]; 
  }
  return v2_0[i];
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



/*回転座標系への変換 x*/
double RotatingCoordinate_X(struct orbital_elements ele[],double x_0[][4],double t_sys){
  return x_0[2][1]*cos(sqrt(G*M_0/ele[1].axis/ele[1].axis/ele[1].axis)*t_sys) + x_0[2][2]*sin(sqrt(G*M_0/ele[1].axis/ele[1].axis/ele[1].axis)*t_sys);
}

/*回転座標系への変換 y*/
double RotatingCoordinate_Y(struct orbital_elements ele[],double x_0[][4],double t_sys){
  return -x_0[2][1]*sin(sqrt(G*M_0/ele[1].axis/ele[1].axis/ele[1].axis)*t_sys) + x_0[2][2]*cos(sqrt(G*M_0/ele[1].axis/ele[1].axis/ele[1].axis)*t_sys);
}








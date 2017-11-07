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


void CenterOfGravity(const double x_0[][4],const double v_0[][4],double x_G[],double v_G[],struct orbital_elements ele[]){
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


#if EXECUTION_TIME
void Calculate_Exetime(uint64_t start_main,uint64_t end_main){

  int i,j;
  double exetime_main = (double)(end_main-start_main) * sTimebaseInfo.numer / sTimebaseInfo.denom * 1.0E-9;
  double exetime_others = 0.0;

  int exetime_num[7]={0,1,2,3,4,5,6};

  double exetime_array[7]={
    exetime.Energy*1.0E-9,
    exetime.Orbital_Elements*1.0E-9,
    exetime.Predictor*1.0E-9,
    exetime.Corrector*1.0E-9,
    exetime.Iteration*1.0E-9,
    exetime.Collision_Judgement*1.0E-9,
    exetime.Fragmentation*1.0E-9
  };

  char exetime_name[7][30]={
    "Energy\t\t\t",
    "Orbital_Elements\t",
    "Predictor\t\t",
    "Corrector\t\t",
    "Iteration\t\t",
    "Collision_Judgement\t",
    "Fragmentation\t\t"
  };

  for(i=0;i<7;++i){
    for(j=i+1;j<7;++j){
      if(exetime_array[i] < exetime_array[j]){
	Swap_int(&exetime_num[i],&exetime_num[j]);
	Swap_double(&exetime_array[i],&exetime_array[j]);
      }
    }
  }

  printf("Execution Time\t(total\t= %e [s])\n",exetime_main);
  for(i=0;i<7;++i){
    printf("%s= %e [s]\t%2.2f [%%]\n",exetime_name[exetime_num[i]],exetime_array[i],exetime_array[i]/exetime_main*100.0);
    exetime_others += exetime_array[i];
  }
  exetime_others = exetime_main - exetime_others;
  printf("Others\t\t\t= %e [s]\t%2.2f [%%]\n",exetime_others,exetime_others/exetime_main*100.0);

  return;
}
#endif

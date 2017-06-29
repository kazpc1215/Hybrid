#include "hybrid.h"


void NeighborSearch(int i,struct orbital_elements ele[],struct fragmentation frag[],double x_0[][4]){

  int j,l;
  double radius[N_tr+1];
  double theta[N_tr+1];
  double S;
  double M;
  double v;
  double delta_theta=DELTA_THETA;

  for(l=1;l<=NEIGHBOR_MAX;l++){
    frag[i].neighborlist[l] = 0;
  }


  radius[i] = sqrt(x_0[i][1]*x_0[i][1] + x_0[i][2]*x_0[i][2]);
  theta[i] = atan2(x_0[i][2],x_0[i][1]);  //[-pi:pi]



  frag[i].delta_r_out = DELTA_R;  //固定
  frag[i].delta_r_in = DELTA_R;  //固定
  if(radius[i]+frag[i].delta_r_out>=OUTER_AXIS*(1.0+ECC_RMS)){
    frag[i].delta_r_out = OUTER_AXIS*(1.0+ECC_RMS) - radius[i];
  }
  if(radius[i]-frag[i].delta_r_in<=INNER_AXIS*(1.0-ECC_RMS)){
    frag[i].delta_r_in = radius[i] - INNER_AXIS*(1.0-ECC_RMS);
  }
  S = 2.0*(frag[i].delta_r_out + frag[i].delta_r_in)*radius[i]*delta_theta;
  
 
  
  //printf("delta_r[%d]=%f\n",i,frag[i].delta_r);

  
  l = 1;
  for(j=1;j<=N_tr;j++){
    if(j!=i){
      radius[j] = sqrt(x_0[j][1]*x_0[j][1] + x_0[j][2]*x_0[j][2]);
      theta[j] = atan2(x_0[j][2],x_0[j][1]);  //[-pi:pi]
      if((radius[j]-radius[i]>0.0 && radius[j]-radius[i]<=frag[i].delta_r_out) || (radius[i]-radius[j]>0.0 && radius[i]-radius[j]<=frag[i].delta_r_in)){  //動径方向
	if(fabs(theta[j] - theta[i])<=delta_theta || 2.0*M_PI - fabs(theta[j] - theta[i])<=delta_theta){  //角度方向
	  frag[i].neighborlist[l] = j;
	  l++;
	}
      }
    }
  }
  
  frag[i].neighbornumber = l-1;



  v=0.0;
  M=ele[i].mass;  //ターゲットiの質量も含める
  if(frag[i].neighbornumber!=0){
    for(j=1;j<=frag[i].neighbornumber;j++){
      v += RandomVelocity(i,j,ele);
      M += ele[frag[i].neighborlist[j]].mass;  //領域iの総質量
    }
    frag[i].v_ave = v/(double)frag[i].neighbornumber;  //領域iの平均速度

    frag[i].sigma = M/S;  //領域iの表面密度
    frag[i].n_s = frag[i].neighbornumber/S;  //領域iの表面密度
  }else{
    frag[i].v_ave = 0.0;
    frag[i].sigma = 0.0;
    frag[i].n_s = 0.0;
  }
  
}


double RandomVelocity(int i,int j,struct orbital_elements ele[]){
  double eij2;
  double iij2;

  eij2 = ele[i].ecc*ele[i].ecc + ele[j].ecc*ele[j].ecc - 2.0*ele[i].ecc*ele[j].ecc*cos(ele[i].omega + ele[i].Omega - ele[j].omega - ele[j].Omega);

  iij2 = ele[i].inc*ele[i].inc + ele[j].inc*ele[j].inc - 2.0*ele[i].inc*ele[j].inc*cos(ele[i].Omega - ele[j].Omega);

  return sqrt((eij2 + iij2)*G*M_0/ele[i].axis);
}

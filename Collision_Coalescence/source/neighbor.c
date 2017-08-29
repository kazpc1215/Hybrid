#include "hybrid.h"


void NeighborSearch(int i,struct orbital_elements ele[],struct fragmentation frag[],double x_0[][4]){

  int j,l,m;
  double radius[global_n+1];
  double theta[global_n+1];
  double S;
  double M;
  double v;
  double delta_theta=DELTA_THETA;

  
  radius[i] = sqrt(x_0[i][1]*x_0[i][1] + x_0[i][2]*x_0[i][2]);
  theta[i] = atan2(x_0[i][2],x_0[i][1]);  //[-pi:pi]

  
  m=1;
  do{

    for(l=1;l<=NEIGHBOR_MAX;l++){
      frag[i].neighborlist[l] = 0;
    }
    frag[i].neighbornumber = 0;
    
    frag[i].delta_r_out = (double)m*DELTA_R;  //外側.
    frag[i].delta_r_in = (double)m*DELTA_R;  //内側.
  
    S = 2.0*(frag[i].delta_r_out + frag[i].delta_r_in)*radius[i]*delta_theta;

    //printf("i=%d\tS=%e\n",i,S);
    //printf("delta_r[%d]=%f\n",i,frag[i].delta_r);
  
    l = 1;
    for(j=global_n_p+1;j<=global_n;j++){  //惑星抜き.
      if(j!=i){
	radius[j] = sqrt(x_0[j][1]*x_0[j][1] + x_0[j][2]*x_0[j][2]);
	theta[j] = atan2(x_0[j][2],x_0[j][1]);  //[-pi:pi]
	if((radius[j]-radius[i]>=0.0 && radius[j]-radius[i]<=frag[i].delta_r_out) || (radius[i]-radius[j]>=0.0 && radius[i]-radius[j]<=frag[i].delta_r_in)){  //動径方向.
	  if(fabs(theta[j] - theta[i])<=delta_theta || 2.0*M_PI - fabs(theta[j] - theta[i])<=delta_theta){  //角度方向.
	    frag[i].neighborlist[l] = j;
	    l++;
	  }
	}
      }
    }
  
    frag[i].neighbornumber = l-1;

    m++;
    
  }while(frag[i].neighbornumber<10);  //近傍粒子が10個未満なら、10個以上になるまでdelta_rをm倍に広げる.
  


  

  v=0.0;
  M=ele[i].mass;  //ターゲットiの質量も含める.
  if(frag[i].neighbornumber!=0){
    for(j=1;j<=frag[i].neighbornumber;j++){
      v += RandomVelocity(i,frag[i].neighborlist[j],ele);
      M += ele[frag[i].neighborlist[j]].mass;  //領域iの総質量.
      
      if(isnan(RandomVelocity(i,frag[i].neighborlist[j],ele))){
	printf("i=%d,j=%d\tvij is nan.\n",i,frag[i].neighborlist[j]);
	printf("i=%d\taxis=%e\tecc=%e\tinc=%e\tu=%e\tOmega=%e\tomega=%e\n",i,ele[i].axis,ele[i].ecc,ele[i].inc,ele[i].u,ele[i].Omega,ele[i].omega);
	printf("j=%d\taxis=%e\tecc=%e\tinc=%e\tu=%e\tOmega=%e\tomega=%e\n",frag[i].neighborlist[j],ele[frag[i].neighborlist[j]].axis,ele[frag[i].neighborlist[j]].ecc,ele[frag[i].neighborlist[j]].inc,ele[frag[i].neighborlist[j]].u,ele[frag[i].neighborlist[j]].Omega,ele[frag[i].neighborlist[j]].omega);
      }
      
    }
    if(isnan(v)){
      printf("i=%d\tv_tot is nan.\n",i);
    }
    frag[i].v_ave = v/(double)frag[i].neighbornumber;  //領域iの平均速度.

    //printf("i=%d\tmass=%e\n",i,ele[i].mass);
    //printf("i=%d\tM=%e\n",i,M);
      
    frag[i].sigma = M/S;  //領域iの表面密度.
    frag[i].n_s = frag[i].neighbornumber/S;  //領域iの表面密度.
  }else{
    frag[i].v_ave = 0.0;
    frag[i].sigma = 0.0;
    frag[i].n_s = 0.0;
  }
  
}


double RandomVelocity(int i,int j,struct orbital_elements ele[]){
  double eij2;
  double iij2;

  eij2 = fabs(ele[i].ecc*ele[i].ecc + ele[j].ecc*ele[j].ecc - 2.0*ele[i].ecc*ele[j].ecc*cos(ele[i].omega + ele[i].Omega - ele[j].omega - ele[j].Omega));

  iij2 = fabs(ele[i].inc*ele[i].inc + ele[j].inc*ele[j].inc - 2.0*ele[i].inc*ele[j].inc*cos(ele[i].Omega - ele[j].Omega));
  
  if(isnan(ele[i].ecc)){
    printf("i=%d\tecc is nan. (in RandomVelocity)\n",i);
  }
  if(isnan(ele[j].ecc)){
    printf("j=%d\tecc is nan. (in RandomVelocity)\n",j);
  }
  if(isnan(ele[i].inc)){
    printf("i=%d\tinc is nan. (in RandomVelocity).\n",i);
  }
  if(isnan(ele[j].inc)){
    printf("j=%d\tinc is nan. (in RandomVelocity)\n",j);
  }
  if(isnan(ele[i].omega)){
    printf("i=%d\tomega is nan. (in RandomVelocity)\n",i);
  }
  if(isnan(ele[j].omega)){
    printf("j=%d\tomega is nan. (in RandomVelocity)\n",j);
  }
  if(isnan(ele[i].Omega)){
    printf("i=%d\tOmega is nan. (in RandomVelocity)\n",i);
  }
  if(isnan(ele[j].Omega)){
    printf("j=%d\tOmega is nan. (in RandomVelocity)\n",j);
  }
  
  if(isnan(eij2)){
    printf("i=%d,j=%d\teij2 is nan. (in RandomVelocity)\n",i,j);
    return -1;
  }
  if(isnan(iij2)){
    printf("i=%d,j=%d\tiij2 is nan. (in RandomVelocity)\n",i,j);
    return -1;
  }
  if(isnan(ele[i].axis)){
    printf("i=%d\taxis is nan. (in RandomVelocity)\taxis=%f\n",i,ele[i].axis);
  }

  if(isnan(sqrt((eij2 + iij2)*G*M_0/ele[i].axis))){
    printf("i=%d,j=%d\tvij is nan.(in RandomVelocity)\n",i,j);
    
    printf("eij2=%e\tiij2=%e\taxis=%e\n",eij2,iij2,ele[i].axis);
  }
  
  return sqrt((eij2 + iij2)*G*M_0/ele[i].axis);
}

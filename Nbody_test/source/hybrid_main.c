#include "hybrid.h"
 


int main(void){

  int i,i_sys,j,k,ite,interval;
  double t_sys;
  //double t_ene[TIME_INTERVAL_MAX]={TIME_INTERVAL};
  double t_data,delta_t=2.0*M_PI*10.0;
  
  double t_[N_tr+1],dt_[N_tr+1],Dt[N_tr+1];
  double step=0.0;
  
  double x_0[N_tr+1][4],r_0[N_tr+1],v_0[N_tr+1][4],v2_0[N_tr+1];
  double x_p[N_tr+1][4],r_p[N_tr+1],v_p[N_tr+1][4],v2_p[N_tr+1];
  double x_c[N_tr+1][4],r_c[N_tr+1],v_c[N_tr+1][4],v2_c[N_tr+1];
  
  double abs_r[N_tr+1],abs_r2[N_tr+1],abs_v[N_tr+1],abs_v2[N_tr+1],r_dot_v_ij[N_tr+1],r_dot_v[N_tr+1];
  
  double a_0[N_tr+1][4],adot_0[N_tr+1][4];
  double a[N_tr+1][4],adot[N_tr+1][4],adot2_dt2[N_tr+1][4],adot3_dt3[N_tr+1][4];

  double abs_a[N_tr+1],abs_adot[N_tr+1],abs_adot2[N_tr+1],abs_adot3[N_tr+1];
  
  double E[N_tr+1];
  double E_tot,E_tot_0;
  double abs_L,abs_L_0;

  double P[N_tr+1][4],Q[N_tr+1][4];

  //clock_t start,end;

  double t_check=2.0*M_PI*0.1;

  double mass_tot;
  

  struct orbital_elements ele[N_tr+1];

  struct fragmentation frag[N_tr+1];

  struct parameter para;
  
  mkdir(STR(DIRECTORY), 0755);  //ディレクトリを作成  755 = rwxr-xr-x

  srand(RAND_SEED);



  //初期値
  /*
  para.alpha = (11.0 + 3.0*P_FRAG)/(6.0 + 3.0*P_FRAG);
  para.s_1 = s_1_FRAG(para);
  para.s_2 = s_2_FRAG(para);
  para.s_3 = s_3_FRAG(para);
  para.h_0 = 0.061*17.3*pow(1.68E6*RHO,-2.0/3.0);  // g/cc = 1.68E6 M_0/AU^3, F(I) = 17.3 として
  para.Q_tilda = Q_0_FRAG*1.13E-13*pow(RHO/3.0,0.55)*pow(2.0E12,P_FRAG);  //erg/g = 1.13E-13 AU^2/(yr/2pi)^2 として

  printf("alpha=%f\ts_1=%f\ts_2=%f\ts_3=%f\n",para.alpha,para.s_1,para.s_2,para.s_3);
  */
  

  for(i=1;i<=N_tr;++i){
    sprintf(ele[i].name,"tracer%04d",i);
    ele[i].mass = M_TOT/(double)N_tr;  //トレーサー質量
    
    ele[i].ecc = sqrt(-log(((double)rand())/((double)RAND_MAX+1.0)))*ECC_RMS;  //離心率  //Rayleigh分布
    
    //ele[i].ecc = ECC_RMS;
    
    ele[i].axis = ((double)rand())/((double)RAND_MAX+1.0)*(OUTER_AXIS-INNER_AXIS)+INNER_AXIS ;  //長半径

    ele[i].u = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;  //離心近点離角

    ele[i].inc = sqrt(-log(((double)rand())/((double)RAND_MAX+1.0)))*INC_RMS;  //軌道傾斜角  //Rayleigh分布

    //ele[i].inc = INC_RMS;
    
    ele[i].Omega = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;  //昇交点経度
    ele[i].omega = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;  //近点引数

    ele[i].r_h = ele[i].axis*cbrt(ele[i].mass/((double)M_0)/3.0);

    ele[i].orinum = i;
  }



  for(i=1;i<=N_tr;++i){  
    InitialCondition(i,P,Q,x_0,v_0,r_0,ele);  //初期位置、速度計算
         
    printf("%s\tx_0[%d][1]=%f\tx_0[%d][2]=%f\tx_0[%d][3]=%f\n",ele[i].name,i,x_0[i][1],i,x_0[i][2],i,x_0[i][3]);
    printf("%s\tv_0[%d][1]=%f\tv_0[%d][2]=%f\tv_0[%d][3]=%f\n",ele[i].name,i,v_0[i][1],i,v_0[i][2],i,v_0[i][3]);
  }  //i loop
    
    
    
    
#if ORBITALELEMENTS_FILE
  FILE *fporbit;   //初期の軌道要素をファイルへ書き出し
  char orbit[100];
  for(i=1;i<=N_tr;++i){
    sprintf(orbit,"%s%s.dat",STR(DIRECTORY),ele[i].name);
    fporbit = fopen(orbit,"w");
    if(fporbit==NULL){
      printf("orbit 0 error\n");
      return -1;
    }

    fprintf(fporbit,"#t[yr]\te\ta\tu\tI\tOMEGA\tomega\tR_H\n");
    fprintf(fporbit,"%e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",0.0,ele[i].ecc,ele[i].axis,ele[i].u,ele[i].inc,ele[i].Omega,ele[i].omega,ele[i].r_h);
  
    fclose(fporbit);
  }
#endif
    


  for(i=1;i<=N_tr;++i){
    v2_0[i] = SquareOfVelocity(i,v_0,v2_0);  //速度の2乗
  }


  E_tot_0 = 0.0;  
  E_tot_0 = Calculate_Energy(i,j,ele,x_0,v_0,v2_0,r_0,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,E,E_tot_0);  //初期エネルギー,その他  コメントアウトしちゃだめなやつ
  //printf("%e\t%.15e\n",0.0,E_tot_0);

#if ENERGY_FILE
  FILE *fpEne;   //初期エネルギーをファイルへ書き出し
  char Ene[50];
  sprintf(Ene,"%sENERGY.dat",STR(DIRECTORY));
  fpEne = fopen(Ene,"w");
  if(fpEne==NULL){
    printf("Ene 0 error\n");
    return -1;
  }
  fprintf(fpEne,"#t\tE_tot\tE error\n");
  fprintf(fpEne,"%e\t%.15e\t%e\n",0.0,E_tot_0,0.0);
  fclose(fpEne);

  abs_L_0 = AngularMomentum(i,ele,x_0,v_0,abs_L_0);  //角運動量の大きさ
  //printf("abs_L_0=%.15e\n",abs_L_0);
#endif
      
 
  for(i=1;i<=N_tr;++i){     
    r_dot_v[i] = InnerProduct(i,x_0,v_0,r_dot_v);  //r_i,v_iの内積
  }

  
  for(i=1;i<=N_tr;++i){  //test particle の加速度
    for(k=1;k<=3;++k){
      a_0[i][k] = All_Acceleration(i,j,k,ele,x_0,r_0,abs_r2,a_0);  //初期の加速度
      adot_0[i][k] = All_dAcceleration(i,j,k,ele,x_0,v_0,r_dot_v,r_dot_v_ij,r_0,abs_r2,adot_0);
      //printf("a_0[%d][%d]=%f\tadot_0[%d][%d]=%f\n",i,k,a_0[i][k],i,k,adot_0[i][k]);
    }
  }
  

  for(i=1;i<=N_tr;++i){ 
    dt_[i] = Timestep_i_0(i,a_0,adot_0,abs_a,abs_adot,dt_);  //初期のタイムステップ計算
    //printf("initial dt_[%d]=%e\n",i,dt_[i]);
  }
    


  for(i=1;i<=N_tr;++i){  
    if(i==1){
      t_sys = dt_[1];
      i_sys = 1;
    }else if(dt_[i] < t_sys){
      t_sys = dt_[i];  //dt_i が最小のものを選ぶ
      i_sys = i;  //i_sysを選ぶ
    } 
  }


  for(i=1;i<=N_tr;++i){
    t_[i] = 0.0;
  }


  

#if FRAGMENTATION
  //start = clock();

  mass_tot = 0.0;
  for(i=1;i<=N_tr;++i){    	

    NeighborSearch(i,ele,frag,x_0,r_0);  //近傍(扇形領域に入った)粒子探索
      
    /*
      printf("i=%d\tneighbornumber=%d\n",i,frag[i].neighbornumber);
      for(j=1;j<=frag[i].neighbornumber;j++){
      printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
      }
      
      printf("i=%d\tv_ave=%f\tsigma=%f\n",i,frag[i].v_ave,frag[i].sigma);
    */

    MassFlux(i,ele,frag,para);  //質量フラックス計算

    frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール

    frag[i].t_frag = frag[i].dt_frag;

    //printf("F[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\n",i,frag[i].flux,i,frag[i].sigma,i,frag[i].dt_frag/2.0/M_PI,i,dt_[i]/2.0/M_PI);

    mass_tot += ele[i].mass;
       
      
  }

  //printf("t=%e\tmass_tot=%.15e\tM_TOT=%.15e\n",0.0,mass_tot,M_TOT);

  //printf("t_sys=%e[yr]\tmass[1]=%e\n",t_sys/2.0/M_PI,ele[1].mass);

  //end = clock();
	
  //printf("t=%e[yr]\tfrag calculation time = %f [sec]\n",t_sys/2.0/M_PI,(double)(end-start)/CLOCKS_PER_SEC);


  FILE *fpfrag;   //初期総質量をファイルへ書き出し
  char fragfile[50];
  sprintf(fragfile,"%sTotalMass.dat",STR(DIRECTORY));
  fpfrag = fopen(fragfile,"w");
  if(fpfrag==NULL){
    printf("fragfile 0 error\n");
    return -1;
  }
  fprintf(fpfrag,"#t[year]\tmass_tot\tM_TOT\n");
  //fprintf(fpfrag,"%e\t%.15e\t%e\n",0.0,mass_tot,M_TOT);
  fclose(fpfrag);

  
  
#endif 




  



  //printf("-----\n");
    
  ////////////////////////////////////////////////////////////////////////////////////

  interval = 0;
  t_data = delta_t;
  
  while(t_sys<T_MAX){
    
    if(t_sys<t_data){  
      //individual timestep

     

      for(i=1;i<=N_tr;++i){ 
	Dt[i] = t_sys - t_[i]; 
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,Dt);  //予測子 t_sysにおけるすべての粒子を計算
      }
	
      for(i=1;i<=N_tr;++i){
	if(i==i_sys){  
	  Corrector_sys(i_sys,j,ele,x_p,v_p,r_p,v2_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,t_sys,dt_);  //修正子 i_sys のみ
	}else{
	  for(k=1;k<=3;++k){  //i_sys 以外の粒子は予測子を使う
	    x_c[i][k] = x_p[i][k];
	    v_c[i][k] = v_p[i][k];
	  }
	  r_c[i] = RadiusFromCenter(i,x_c,r_c);  //中心からの距離
	  v2_c[i] = SquareOfVelocity(i,v_c,v2_c);  //速度の2乗
	}
      }  //i loop
	
	     
      for(ite=1;ite<=ITE_MAX;++ite){  //iteration 3回 
	Iteration_sys(i_sys,j,ele,x_p,v_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,dt_);  // i_sys のみ
      }
      


       
	
    }else{  
      //t_ene[interval] ですべての粒子をそろえ、エネルギー、軌道要素等計算
      
      t_sys = t_data;
      
      
      for(i=1;i<=N_tr;++i){
	Dt[i] = t_data - t_[i];
	dt_[i] = Dt[i];
      }

      for(i=1;i<=N_tr;++i){ 	  
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,Dt);  //予測子 t_sysにおけるすべての粒子を計算
      }
	
      for(i=1;i<=N_tr;++i){
	Corrector_sys(i,j,ele,x_p,v_p,r_p,v2_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,t_sys,dt_);
      }

      for(ite=1;ite<=ITE_MAX;++ite){  //iteration 3回 
	for(i=1;i<=N_tr;++i){	  
	  Iteration_sys(i,j,ele,x_p,v_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,dt_);
	}
      }


#if ENERGY_FILE

      E_tot = 0.0;
      E_tot = Calculate_Energy(i,j,ele,x_c,v_c,v2_c,r_c,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,E,E_tot);  //エネルギー計算
	
      sprintf(Ene,"%sENERGY.dat",STR(DIRECTORY));
      fpEne = fopen(Ene,"a");
      if(fpEne==NULL){
	printf("Ene error\n");
	return -1;
      }
      fprintf(fpEne,"%e\t%.15e\t%.15e\n",t_sys,E_tot,(E_tot-E_tot_0)/fabs(E_tot_0));
      fclose(fpEne);

      abs_L = AngularMomentum(i,ele,x_c,v_c,abs_L);
#endif
	

      
      
      
#if ORBITALELEMENTS_FILE
      
      for(i=1;i<=N_tr;++i){
	Calculate_OrbitalElements(i,x_c,v_c,ele,P,Q,r_c,v2_c,r_dot_v);  //軌道要素計算  ファイルへ書き出し
	sprintf(orbit,"%s%s.dat",STR(DIRECTORY),ele[i].name);
	fporbit = fopen(orbit,"a");
	if(fporbit==NULL){
	  printf("orbit error\n");
	  return -1;
	}
	
	fprintf(fporbit,"%e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",t_sys/2.0/M_PI,ele[i].ecc,ele[i].axis,ele[i].u,ele[i].inc,ele[i].Omega,ele[i].omega,ele[i].r_h);
	
	fclose(fporbit);
      }
#endif
      
      //interval++;
      t_data += delta_t;
      
    }
    
    /*for(i=1;i<=N;++i){
      printf("%s\tx_c[%d][1]=%f\tx_c[%d][2]=%f\tx_c[%d][3]=%f\n",ele[i].name,i,x_c[i][1],i,x_c[i][2],i,x_c[i][3]);
      printf("%s\tv_c[%d][1]=%f\tv_c[%d][2]=%f\tv_c[%d][3]=%f\n",ele[i].name,i,v_c[i][1],i,v_c[i][2],i,v_c[i][3]);
      }*/



    
#if FRAGMENTATION
    //start = clock();
    
    mass_tot = 0.0;
    for(i=1;i<=N_tr;++i){    
      
      if(t_sys>frag[i].t_frag){
	frag[i].t_frag += frag[i].dt_frag;
	
	NeighborSearch(i,ele,frag,x_c,r_c);  //近傍(扇形領域に入った)粒子探索
	
	/*
	  printf("i=%d\tneighbornumber=%d\n",i,frag[i].neighbornumber);
	  for(j=1;j<=frag[i].neighbornumber;j++){
	  printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
	  }
	*/
	//printf("i=%d\tv_ave=%f\tsigma=%f\n",i,frag[i].v_ave,frag[i].sigma);
	
	
	MassFlux(i,ele,frag,para);  //質量フラックス計算
	
	frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール

	if(isnan(frag[i].dt_frag)){
	  //frag[i].dt_frag = dt_[i]*100.0;  //NaN処理
	  return -1;
	}
	
	ele[i].mass = MassDepletion(i,ele);  //トレーサー質量の減少を計算
	
	//printf("F[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\tr_c[%d]=%f\n",i,frag[i].flux,i,frag[i].sigma,i,frag[i].dt_frag/2.0/M_PI,i,dt_[i]/2.0/M_PI,i,r_c[i]);


      }
      mass_tot += ele[i].mass;
    }
	
    //printf("t=%e\tmass_tot=%.15f\tM_TOT=%.15e\n",t_sys,mass_tot,M_TOT);
	
	
	
    //printf("t_sys=%e[yr]\tmass[1]=%e\n",t_sys/2.0/M_PI,ele[1].mass);
	
    //end = clock();
	
    //printf("t=%e[yr]\tfrag calculation time = %f [sec]\n",t_sys/2.0/M_PI,(double)(end-start)/CLOCKS_PER_SEC);
	

    if(t_sys>t_check){
      fpfrag = fopen(fragfile,"a");
      if(fpfrag==NULL){
	printf("fragfile error\n");
	return -1;
      }
      fprintf(fpfrag,"%e\t%.15e\t%e\n",t_sys/2.0/M_PI,mass_tot,M_TOT);
      fclose(fpfrag);
      t_check *= 1.2;
    }

    
#endif 

	
    
    
    
    if(fmod(step,1.0E5)==0.0){
      //printf("i_sys=%03d\tt=%.15e\tE=%.15e\tL=%.15e\tr_min=%.15e\n",i_sys,t_sys,E_tot,abs_L,r_min);  //全エネルギー,全角運動量
      printf("step=%e\tN_tr=%d\ti_sys=%03d\tt=%.2e[yr]",step,N_tr,i_sys,t_sys/2.0/M_PI);
      printf("\n");
    }
    
    
    t_[i_sys] += dt_[i_sys];  //i_sys のみ時間更新
    
    
    

    dt_[i_sys] = Timestep_i_sys(i_sys,a,adot,adot2_dt2,adot3_dt3,abs_a,abs_adot,abs_adot2,abs_adot3,dt_);  //i_sys のみタイムステップ計算
    

    
    
    for(k=1;k<=3;++k){  //i_sys のみ更新
      x_0[i_sys][k] = x_c[i_sys][k];
      v_0[i_sys][k] = v_c[i_sys][k];
      a_0[i_sys][k] = a[i_sys][k];
      adot_0[i_sys][k] = adot[i_sys][k];
    }
    
    
    t_sys = t_[1] + dt_[1];
    i_sys = 1;
    for(i=2;i<=N_tr;++i){  
      if((t_[i] + dt_[i]) < t_sys){
	t_sys = t_[i] + dt_[i];  //dt_i が最小のものを選ぶ
	i_sys = i;  //i_sysを選ぶ
      }
    }
    
    
    
    step+=1.0;
  }  //t loop
  

  
#if ENERGY_FILE
  printf("dt_[i_sys]=%e\tE_error=%.15e\tL_error=%.15e\n",dt_[i_sys],(E_tot-E_tot_0)/fabs(E_tot_0),(abs_L-abs_L_0)/abs_L_0);
#endif
  
  printf("step=%e\n",step);
  /*
  for(i=0;i<TIME_INTERVAL_MAX;i++){
    printf("t_ene[%d]=%e\n",i,t_ene[i]);
  } 
  */
}

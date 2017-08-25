#define EXTERN
#include "hybrid.h"

int global_n = N_tr + N_p;  //全粒子数
int global_n_p = N_p;  //原始惑星の数

int main(void){

  int i,i_sys,k,ite,interval;
  int i_col,j_col;
  double t_sys;
  double t_ene[TIME_INTERVAL_MAX]={TIME_INTERVAL};

  double t_[N_p+N_tr+1]={},dt_[N_p+N_tr+1]={},Dt[N_p+N_tr+1]={};
  double step=0.0;
  
  double x_0[N_p+N_tr+1][4]={},r_0[N_p+N_tr+1]={},v_0[N_p+N_tr+1][4]={},v2_0[N_p+N_tr+1]={};
  double x_p[N_p+N_tr+1][4]={},r_p[N_p+N_tr+1]={},v_p[N_p+N_tr+1][4]={},v2_p[N_p+N_tr+1]={};
  double x_c[N_p+N_tr+1][4]={},r_c[N_p+N_tr+1]={},v_c[N_p+N_tr+1][4]={},v2_c[N_p+N_tr+1]={};
  
  double abs_r[N_p+N_tr+1]={},abs_r2[N_p+N_tr+1]={},abs_v[N_p+N_tr+1]={},abs_v2[N_p+N_tr+1]={},r_dot_v_ij[N_p+N_tr+1]={},r_dot_v[N_p+N_tr+1]={};
  
  double a_0[N_p+N_tr+1][4]={},adot_0[N_p+N_tr+1][4]={};
  double a[N_p+N_tr+1][4]={},adot[N_p+N_tr+1][4]={},adot2_dt2[N_p+N_tr+1][4]={},adot3_dt3[N_p+N_tr+1][4]={};

  double abs_a[N_p+N_tr+1]={},abs_adot[N_p+N_tr+1]={},abs_adot2[N_p+N_tr+1]={},abs_adot3[N_p+N_tr+1]={};
  
  double E_tot,E_tot_0;
  double abs_L,abs_L_0;

  double P[N_p+N_tr+1][4]={},Q[N_p+N_tr+1][4]={};


  //clock_t start,end;


  struct orbital_elements ele[N_p+N_tr+1]={};


#if FRAGMENTATION
  struct fragmentation frag[N_p+N_tr+1]={};
  double t_check=2.0*M_PI*0.1;
  double mass_tot_all;
  struct parameter para;
#endif


  
  mkdir(STR(DIRECTORY), 0755);  //ディレクトリを作成  755 = rwxr-xr-x

  char cat_header[200];
  char headerfile[20]="hybrid.h";
  sprintf(cat_header,"cat %s > %sheaderfile.txt",headerfile,STR(DIRECTORY));
  system(cat_header);


  char cat_main[200];
  char mainfile[20]="hybrid_main.c";
  sprintf(cat_main,"cat %s > %smainfile.txt",mainfile,STR(DIRECTORY));
  system(cat_main);
  
  srand(RAND_SEED);



  //初期値

#if FRAGMENTATION
  para.alpha = (11.0 + 3.0*P_FRAG)/(6.0 + 3.0*P_FRAG);
  para.s_1 = s_1_FRAG(para);
  para.s_2 = s_2_FRAG(para);
  para.s_3 = s_3_FRAG(para);
  para.h_0 = 0.061*17.3*pow(1.68E6*RHO,-2.0/3.0);  // g/cc = 1.68E6 M_0/AU^3, F(I) = 17.3 として
  para.Q_D = Q_0_FRAG*1.13E-13*pow(RHO/3.0,0.55)*pow(M_MAX*1.989E12,P_FRAG);  //erg/g = 1.13E-13 AU^2/(yr/2pi)^2 として

  printf("alpha=%f\ts_1=%f\ts_2=%f\ts_3=%f\n",para.alpha,para.s_1,para.s_2,para.s_3);
#endif



  for(i=1;i<=global_n_p;++i){  //惑星
    sprintf(ele[i].name,"Planet%02d",i);
    ele[i].mass = PLANET_MASS;
    ele[i].axis = 1.0 + 0.5/((double)global_n_p)*(double)i;
    ele[i].ecc = PLANET_ECC;
    ele[i].inc = PLANET_INC;
    ele[i].u = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;
    ele[i].omega = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;
    ele[i].Omega = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;
    ele[i].r_h = ele[i].axis*cbrt(ele[i].mass/M_0/3.0);
    ele[i].radius = cbrt(3.0/4.0/M_PI*ele[i].mass*1.989E33/PLANET_DENSITY)/1.496E13;
    ele[i].orinum = i;

    InitialCondition(i,P,Q,x_0,v_0,v2_0,r_dot_v,r_0,ele);  //初期位置、速度計算 //惑星のみ
  }


#if N_tr != 0
  double x_eject[N_p+N_tr+1][4]={};
  double v_eject[N_p+N_tr+1][4]={};
  double tmp_x,tmp_y,tmp_r,tmp_theta;
  //double tmp_rand1;
  double tmp_rand2;
  double tmp_v;
  
  for(i=global_n_p+1;i<=global_n;++i){
    sprintf(ele[i].name,"tracer%04d",i-global_n_p);
    ele[i].mass = M_TOT/(double)N_tr;
    ele[i].orinum = i;


    /*
    tmp_r = PLANET_RADIUS*(1.0 + 1.0*((double)rand())/((double)RAND_MAX+1.0));
    //tmp_rand1 = ((double)rand())/((double)RAND_MAX+1.0)*M_PI;  //theta
    tmp_rand2 = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;  //phi
    */
    tmp_r = PLANET_RADIUS*(1.0 + 0.1*(int)((double)(i-global_n_p-1)/100.0));
    tmp_rand2 = 2.0*M_PI/100.0*(double)(i-global_n_p-1);
    
    
    
    //cone
    x_eject[i][1] = tmp_r*cos(EJECTION_CONE_ANGLE);  //破片のx座標
    x_eject[i][2] = tmp_r*sin(EJECTION_CONE_ANGLE)*cos(tmp_rand2);  //破片のy座標
    x_eject[i][3] = tmp_r*sin(EJECTION_CONE_ANGLE)*sin(tmp_rand2);  //破片のz座標
    

       
    /*
    //isotropic
    x_eject[i][1] = tmp_r*sin(tmp_rand1)*cos(tmp_rand2);  //破片のx座標
    x_eject[i][2] = tmp_r*sin(tmp_rand1)*sin(tmp_rand2);  //破片のx座標
    x_eject[i][3] = tmp_r*cos(tmp_rand1);  //破片のx座標
    */



    //Rotation_3D_zaxis(i,x_eject,M_PI);  //z軸周りに180度回転
    //Rotation_3D_zaxis(i,x_eject,M_PI/2.0);  //z軸周りに90度回転
    Rotation_3D_zaxis(i,x_eject,-M_PI/2.0);  //z軸周りに-90度回転


    
    printf("%s\tx_eject[%d][1]=%f\tx_eject[%d][2]=%f\tx_eject[%d][3]=%f\n",ele[i].name,i,x_eject[i][1],i,x_eject[i][2],i,x_eject[i][3]);


    //tmp_v = EJECTION_VELOCITY;
    tmp_v = EJECTION_VELOCITY*(0.9+0.1*tmp_r/PLANET_RADIUS);
    tmp_theta = EJECTION_CONE_ANGLE*tmp_r/PLANET_RADIUS;
    //tmp_theta = EJECTION_CONE_ANGLE;
    
    //cone
    v_eject[i][1] = tmp_v*cos(tmp_theta);  //破片の速度x成分
    v_eject[i][2] = tmp_v*sin(tmp_theta)*cos(tmp_rand2);  //破片の速度y成分
    v_eject[i][3] = tmp_v*sin(tmp_theta)*sin(tmp_rand2);  //破片の速度z成分
    
    /*
    //isotropic
    v_eject[i][1] = tmp_v*sin(tmp_rand1)*cos(tmp_rand2);  //破片の速度x成分
    v_eject[i][2] = tmp_v*sin(tmp_rand1)*sin(tmp_rand2);  //破片の速度y成分
    v_eject[i][3] = tmp_v*cos(tmp_rand1);  //破片の速度z成分
    */



    //Rotation_3D_zaxis(i,v_eject,M_PI);  //z軸周りに180度回転
    //Rotation_3D_zaxis(i,v_eject,M_PI/2.0);  //z軸周りに90度回転
    Rotation_3D_zaxis(i,v_eject,-M_PI/2.0);  //z軸周りに-90度回転
    

    
    printf("%s\tv_eject[%d][1]=%f\tv_eject[%d][2]=%f\tv_eject[%d][3]=%f\n",ele[i].name,i,v_eject[i][1],i,v_eject[i][2],i,v_eject[i][3]);
    //////////////////ここまでで、惑星中心、xyは軌道面上、x軸は太陽から惑星の方向/////////////////////


    //位置
    tmp_x = x_eject[i][1];
    tmp_y = x_eject[i][2];

    x_eject[i][1] = cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x - sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;

    x_eject[i][2] = sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x + cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;

    //速度
    tmp_x = v_eject[i][1];
    tmp_y = v_eject[i][2];

    v_eject[i][1] = cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x - sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;

    v_eject[i][2] = sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x + cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;
    
    
    //////////////////ここまでで、惑星中心、xyは軌道面上、x軸は惑星の近日点の方向/////////////////////
    

    
    Rotation_3D_zaxis(i,x_eject,ele[PLANET_NO].Omega);  //位置
    Rotation_3D_xaxis(i,x_eject,ele[PLANET_NO].inc);
    Rotation_3D_zaxis(i,x_eject,ele[PLANET_NO].omega);


    Rotation_3D_zaxis(i,v_eject,ele[PLANET_NO].Omega);  //速度
    Rotation_3D_xaxis(i,v_eject,ele[PLANET_NO].inc);
    Rotation_3D_zaxis(i,v_eject,ele[PLANET_NO].omega); 
    //////////////////ここまでで、惑星中心に平行移動した基準系/////////////////////
    
   
    for(k=1;k<=3;++k){
      x_0[i][k] = x_0[PLANET_NO][k] + x_eject[i][k];  //基準系での破片の座標
      v_0[i][k] = v_0[PLANET_NO][k] + v_eject[i][k];
    }
    

    
    r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離


    r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積
    v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗
  }

  for(i=global_n_p+1;i<=global_n;++i){
    Calculate_OrbitalElements(i,x_0,v_0,ele,P,Q,r_0,v2_0,r_dot_v);
    //ele[i].r_h = ele[i].axis*cbrt(ele[i].mass/((double)M_0)/3.0);
  }
#endif
  

  
  for(i=1;i<=global_n;++i){  
    //InitialCondition(i,P,Q,x_0,v_0,r_0,ele);  //初期位置、速度計算
         
    printf("%s\tx_0[%d][1]=%f\tx_0[%d][2]=%f\tx_0[%d][3]=%f\n",ele[i].name,i,x_0[i][1],i,x_0[i][2],i,x_0[i][3]);
    printf("%s\tv_0[%d][1]=%f\tv_0[%d][2]=%f\tv_0[%d][3]=%f\n",ele[i].name,i,v_0[i][1],i,v_0[i][2],i,v_0[i][3]);
  }  //i loop


  

  FILE *fpposivelo;   //初期位置、速度をファイルへ書き出し
  char posivelofile[100];
  sprintf(posivelofile,"%sPosi_Velo.dat",STR(DIRECTORY));
  fpposivelo= fopen(posivelofile,"w");
  if(fpposivelo==NULL){
    printf("posivelofile 0 error\n");
    return -1;
  }
  fprintf(fpposivelo,"#t[year]\ti\tx\ty\tz\tr_0(3次元)\tr_0(xy平面に射影)\tv_x\tv_y\tv_z\tabs_v\n");
  for(i=1;i<=global_n;i++){
    fprintf(fpposivelo,"%e\t%4d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\n",0.0,i,x_0[i][1],x_0[i][2],x_0[i][3],r_0[i],sqrt(x_0[i][1]*x_0[i][1]+x_0[i][2]*x_0[i][2]),v_0[i][1],v_0[i][2],v_0[i][3],sqrt(v_0[i][1]*v_0[i][1]+v_0[i][2]*v_0[i][2]+v_0[i][3]*v_0[i][3]));
  }
  fprintf(fpposivelo,"\n\n");
  fclose(fpposivelo);
  


  
  
  
#if ORBITALELEMENTS_FILE
  FILE *fporbit;   //初期の軌道要素をファイルへ書き出し
  char orbit[200];
  for(i=1;i<=global_n;++i){
    sprintf(orbit,"%s%s.dat",STR(DIRECTORY),ele[i].name);
    fporbit = fopen(orbit,"w");
    if(fporbit==NULL){
      printf("orbit 0 error\n");
      return -1;
    }

    fprintf(fporbit,"#t\te\ta\tu\tI\tOMEGA\tomega\tR_H\tradius\tmass\n");
    fprintf(fporbit,"%e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",0.0,ele[i].ecc,ele[i].axis,ele[i].u,ele[i].inc,ele[i].Omega,ele[i].omega,ele[i].r_h,ele[i].radius,ele[i].mass);
  
    fclose(fporbit);
  }
#endif


  /*
  for(i=1;i<=N_p+N_tr;i++){
    v2_0[i] = SquareOfVelocity(i,v_0,v2_0);  //速度の2乗
  }  
  */


  E_tot_0 = 0.0;
  E_tot_0 = Calculate_Energy(ele,x_0,v_0,v2_0,r_0,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij);  //初期エネルギー、相対距離、相対速度、相対距離と相対速度の内積  コメントアウトしちゃだめなやつ
  //printf("%e\t%.15e\n",0.0,E_tot_0);

  
#if ENERGY_FILE
  FILE *fpEne;   //初期エネルギーをファイルへ書き出し
  char Ene[100];
  sprintf(Ene,"%sENERGY.dat",STR(DIRECTORY));
  fpEne = fopen(Ene,"w");
  if(fpEne==NULL){
    printf("Ene 0 error\n");
    return -1;
  }
  fprintf(fpEne,"#t\tE_tot\tE error\n");
  fprintf(fpEne,"%e\t%.15e\t%e\n",0.0,E_tot_0,0.0);
  fclose(fpEne);

  abs_L_0 = 0.0;
  abs_L_0 = AngularMomentum(i,ele,x_0,v_0);  //角運動量の大きさ
  //printf("abs_L_0=%.15e\n",abs_L_0);
#endif
      


  for(i=1;i<=global_n;i++){
    r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積
  }
      
  
  
  for(i=1;i<=global_n;++i){
    for(k=1;k<=3;++k){
      a_0[i][k] = All_Acceleration(i,k,ele,x_0,r_0,abs_r2);  //初期の加速度
      adot_0[i][k] = All_dAcceleration(i,k,ele,x_0,v_0,r_dot_v,r_dot_v_ij,r_0,abs_r2);
      //printf("a_0[%d][%d]=%f\tadot_0[%d][%d]=%f\n",i,k,a_0[i][k],i,k,adot_0[i][k]);
    }
  }

  

  for(i=1;i<=global_n;++i){ 
    dt_[i] = Timestep_i_0(i,a_0,adot_0,abs_a,abs_adot);  //初期のタイムステップ計算
    //printf("initial dt_[%d]=%e\n",i,dt_[i]);
  }
    


   
  t_sys = dt_[1];
  i_sys = 1;
  for(i=2;i<=global_n;++i){
    if(dt_[i] < t_sys){
      t_sys = dt_[i];  //dt_i が最小のものを選ぶ
      i_sys = i;  //i_sysを選ぶ
    } 
  }

  
  for(i=1;i<=global_n;++i){
    t_[i] = 0.0;
  }


  

#if FRAGMENTATION
  //start = clock();

  mass_tot_all = 0.0;
  for(i=global_n_p+1;i<=global_n;++i){

    frag[i].fragtimes = 0;
    
    NeighborSearch(i,ele,frag,x_0);  //近傍(扇形領域に入った)粒子探索
      
    
    printf("i=%d\tneighbornumber=%d\n",i,frag[i].neighbornumber);
    /*
      for(j=1;j<=frag[i].neighbornumber;j++){
      printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
      }
    printf("i=%d\tv_ave=%f\tsigma=%f\n",i,frag[i].v_ave,frag[i].sigma);
    */
    //printf("initial\tF[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\n",i,frag[i].flux,i,frag[i].sigma,i,frag[i].dt_frag/2.0/M_PI,i,dt_[i]/2.0/M_PI);

    MassFlux(i,ele,frag,para);  //質量フラックス計算

    frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール

    frag[i].t_frag = frag[i].dt_frag;

    printf("\tinitial\tF[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\n",i,frag[i].flux,i,frag[i].sigma,i,frag[i].dt_frag/2.0/M_PI,i,dt_[i]/2.0/M_PI);
    
    printf("\ti=%d\tv_ave=%f\tsigma=%f\tecc=%f\tr_0=%f\tdelta_r_out=%f\tdelta_r_in=%f\n",i,frag[i].v_ave,frag[i].sigma,ele[i].ecc,r_0[i],frag[i].delta_r_out,frag[i].delta_r_in);


    mass_tot_all += ele[i].mass;
  }



  //printf("t=%e\tmass_tot=%.15e\tM_TOT=%.15e\n",0.0,mass_tot,M_TOT);

  //printf("t_sys=%e[yr]\tmass[1]=%e\n",t_sys/2.0/M_PI,ele[1].mass);

  //end = clock();
	
  //printf("t=%e[yr]\tfrag calculation time = %f [sec]\n",t_sys/2.0/M_PI,(double)(end-start)/CLOCKS_PER_SEC);


  FILE *fpfrag;   //初期総質量をファイルへ書き出し
  char fragfile[100];
  sprintf(fragfile,"%sTotalMass.dat",STR(DIRECTORY));
  fpfrag = fopen(fragfile,"w");
  if(fpfrag==NULL){
    printf("fragfile 0 error\n");
    return -1;
  }
  fprintf(fpfrag,"#t[year]\tmass_tot_all\tM_TOT\n");
  fprintf(fpfrag,"%e\t%.15f\t%.15f\n",0.0,mass_tot_all,M_TOT);
  fclose(fpfrag);


  

  FILE *fpposimass;   //初期位置、質量などをファイルへ書き出し
  char posimassfile[100];
  sprintf(posimassfile,"%sPosi_Mass.dat",STR(DIRECTORY));
  fpposimass= fopen(posimassfile,"w");
  if(fpposimass==NULL){
    printf("posimassfile 0 error\n");
    return -1;
  }
  fprintf(fpposimass,"#t[year]\ti\tx\ty\tz\tr_0(3次元)\tr_0(xy平面に射影)\tmass\tdelta_r\tsigma\tn_s\tneighbornumber\n");
  for(i=1;i<=global_n;i++){
    fprintf(fpposimass,"%e\t%4d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%d\n",0.0,i,x_0[i][1],x_0[i][2],x_0[i][3],r_0[i],sqrt(x_0[i][1]*x_0[i][1]+x_0[i][2]*x_0[i][2]),ele[i].mass,frag[i].delta_r_out,frag[i].delta_r_in,frag[i].sigma,frag[i].n_s,frag[i].neighbornumber);
  }
  fprintf(fpposimass,"\n\n");
  
  fclose(fpposimass);
  
  
#endif 




  



  //printf("-----\n");
    
  ////////////////////////////////////////////////////////////////////////////////////

  interval = 0;

  while(TIME_INTERVAL_MAX>interval){
    
    if(t_sys<t_ene[interval]){  
      //individual timestep

     

      for(i=1;i<=global_n;++i){ 
	Dt[i] = t_sys - t_[i]; 
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,Dt);  //予測子 t_sysにおけるすべての粒子を計算
      }

      
      if(Collision_Judgement(ele,x_p,abs_r,abs_r2,&i_col,&j_col)==1){  //予測子を用いた衝突判定

	/////////////////////////衝突した場合/////////////////////////
	printf("collision\ti=%d, j=%d\n",i_col,j_col);
	printf("r_ij=%.15e\tradius[%d]+radius[%d]=%.15e\n",abs_r[j_col],i_col,j_col,ele[i_col].radius + ele[j_col].radius);

	for(i=1;i<=global_n;++i){
	  Corrector_sys(i,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,Dt);  //修正子 すべての粒子 t_sysで揃えるためDt[i]を使う
	}

	for(ite=1;ite<=ITE_MAX;++ite){  //iteration 3回
	  for(i=1;i<=global_n;++i){
	    Iteration_sys(i,ele,x_p,v_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,Dt);  // すべての粒子 t_sysで揃えるためDt[i]を使う
	  }
	}


	//新しい合体粒子を作る　0番目の要素はコピーに使うだけ
	ele[0].mass = ele[i_col].mass + ele[j_col].mass;
	for(k=1;k<=3;++k){
	  x_0[0][k] = (ele[i_col].mass*x_c[i_col][k] + ele[j_col].mass*x_c[j_col][k])/ele[0].mass;
	  v_0[0][k] = (ele[i_col].mass*v_c[i_col][k] + ele[j_col].mass*v_c[j_col][k])/ele[0].mass;
	}

	//i_colを新しい合体粒子の番号にする
	ele[i_col].mass = ele[0].mass;
	ele[i_col].radius = cbrt(3.0/4.0/M_PI*ele[i_col].mass*1.989E33/PLANET_DENSITY)/1.496E13;
	for(k=1;k<=3;++k){
	  x_0[i_col][k] = x_0[0][k];
	  v_0[i_col][k] = v_0[0][k];
	}

	
	
	//j_colとglobal_n番目の粒子を入れ替え、global_nとglobal_n_pを1つ減らす
	ele[0] = ele[j_col];  //構造体のためswap関数は使えない　0番目の要素はコピーに使うだけ
	ele[j_col] = ele[global_n];
	ele[global_n] = ele[0];
	for(k=1;k<=3;++k){
	  swap(&x_0[j_col][k],&x_0[global_n][k]);
	  swap(&v_0[j_col][k],&v_0[global_n][k]);
	}
	global_n--;
	global_n_p--;

	//以下、すべての粒子の加速度などを再計算
	for(i=1;i<=global_n;++i){
	  r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離
	  r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積
	  v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗
	}

	for(i=1;i<=global_n;++i){
	  Calculate_OrbitalElements(i,x_0,v_0,ele,P,Q,r_0,v2_0,r_dot_v);
	}

	E_tot = 0.0;
	E_tot = Calculate_Energy(ele,x_0,v_0,v2_0,r_0,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij);  //エネルギー、相対距離、相対速度、相対距離と相対速度の内積  コメントアウトしちゃだめなやつ

#if ENERGY_FILE
	
	sprintf(Ene,"%sENERGY.dat",STR(DIRECTORY));
	fpEne = fopen(Ene,"a");
	if(fpEne==NULL){
	  printf("Ene error\n");
	  return -1;
	}
	fprintf(fpEne,"#collision occur\t%e[yr]\n",t_sys/2.0/M_PI);
	fprintf(fpEne,"%e\t%.15e\t%.15e\n",t_sys,E_tot,(E_tot-E_tot_0)/fabs(E_tot_0));
	fclose(fpEne);

	abs_L = AngularMomentum(i,ele,x_0,v_0);
#endif
	
	
	for(i=1;i<=global_n;++i){
	  for(k=1;k<=3;++k){
	    a_0[i][k] = All_Acceleration(i,k,ele,x_0,r_0,abs_r2);  //加速度
	    adot_0[i][k] = All_dAcceleration(i,k,ele,x_0,v_0,r_dot_v,r_dot_v_ij,r_0,abs_r2);
	    //printf("a_0[%d][%d]=%f\tadot_0[%d][%d]=%f\n",i,k,a_0[i][k],i,k,adot_0[i][k]);
	  }
	}

	for(i=1;i<=global_n;++i){
	  t_[i] += Dt[i];  //すべての粒子の時間はt_sysで揃っている
	}
	
	
	//exit(-1);

	//////////////////////////////////////////////////////////////

	
      }else{

	/////////////////////////衝突しない場合/////////////////////////
	for(i=1;i<=global_n;++i){
	  if(i==i_sys){  
	    Corrector_sys(i_sys,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,dt_);  //修正子 i_sys のみ
	  }else{
	    for(k=1;k<=3;++k){  //i_sys 以外の粒子は予測子を使う
	      x_c[i][k] = x_p[i][k];
	      v_c[i][k] = v_p[i][k];
	    }
	    r_c[i] = RadiusFromCenter(i,x_c);  //中心からの距離
	    v2_c[i] = SquareOfVelocity(i,v_c);  //速度の2乗
	  }
	}

	     
	for(ite=1;ite<=ITE_MAX;++ite){  //iteration 3回 
	  Iteration_sys(i_sys,ele,x_p,v_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,dt_);  // i_sys のみ
	}
	////////////////////////////////////////////////////////////////

	
      }

      
	
    }else{  
      //t_ene[interval] ですべての粒子をそろえ、エネルギー、軌道要素等計算
      
      t_sys = t_ene[interval];
      
      
      for(i=1;i<=global_n;++i){
	Dt[i] = t_ene[interval] - t_[i];
	dt_[i] = Dt[i];
      }

      for(i=1;i<=global_n;++i){ 	  
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,Dt);  //予測子 t_sysにおけるすべての粒子を計算
      }
	
      for(i=1;i<=global_n;++i){
	Corrector_sys(i,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,dt_);
      }

      for(ite=1;ite<=ITE_MAX;++ite){  //iteration 3回 
	for(i=1;i<=global_n;++i){	  
	  Iteration_sys(i,ele,x_p,v_p,x_c,v_c,r_c,v2_c,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij,r_dot_v,dt_);
	}
      }




      fpposivelo = fopen(posivelofile,"a");  //位置、速度をファイルへ書き出し
      if(fpposivelo==NULL){
	printf("posivelofile error\n");
	return -1;
      }
      for(i=1;i<=global_n;i++){
	fprintf(fpposivelo,"%e\t%4d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\n",t_sys/2.0/M_PI,i,x_c[i][1],x_c[i][2],x_c[i][3],r_c[i],sqrt(x_c[i][1]*x_c[i][1]+x_c[i][2]*x_c[i][2]),v_c[i][1],v_c[i][2],v_c[i][3],sqrt(v_c[i][1]*v_c[i][1]+v_c[i][2]*v_c[i][2]+v_c[i][3]*v_c[i][3]));
      }
      fprintf(fpposivelo,"\n\n");
  
      fclose(fpposivelo);



      

#if ENERGY_FILE

      E_tot = 0.0;
      E_tot = Calculate_Energy(ele,x_c,v_c,v2_c,r_c,abs_r,abs_r2,abs_v,abs_v2,r_dot_v_ij);  //エネルギー計算
	
      sprintf(Ene,"%sENERGY.dat",STR(DIRECTORY));
      fpEne = fopen(Ene,"a");
      if(fpEne==NULL){
	printf("Ene error\n");
	return -1;
      }
      fprintf(fpEne,"%e\t%.15e\t%.15e\n",t_sys,E_tot,(E_tot-E_tot_0)/fabs(E_tot_0));
      fclose(fpEne);

      abs_L = AngularMomentum(i,ele,x_c,v_c);
#endif
	

      
      
      
#if ORBITALELEMENTS_FILE
      
      for(i=1;i<=global_n;++i){
	Calculate_OrbitalElements(i,x_c,v_c,ele,P,Q,r_c,v2_c,r_dot_v);  //軌道要素計算  ファイルへ書き出し
	sprintf(orbit,"%s%s.dat",STR(DIRECTORY),ele[i].name);
	fporbit = fopen(orbit,"a");
	if(fporbit==NULL){
	  printf("orbit error\n");
	  return -1;
	}
	
	fprintf(fporbit,"%e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",t_sys,ele[i].ecc,ele[i].axis,ele[i].u,ele[i].inc,ele[i].Omega,ele[i].omega,ele[i].r_h,ele[i].radius,ele[i].mass);
	
	fclose(fporbit);
      }
#endif
      
      interval++;

    }
    
    /*for(i=1;i<=N;++i){
      printf("%s\tx_c[%d][1]=%f\tx_c[%d][2]=%f\tx_c[%d][3]=%f\n",ele[i].name,i,x_c[i][1],i,x_c[i][2],i,x_c[i][3]);
      printf("%s\tv_c[%d][1]=%f\tv_c[%d][2]=%f\tv_c[%d][3]=%f\n",ele[i].name,i,v_c[i][1],i,v_c[i][2],i,v_c[i][3]);
      }*/



    
#if FRAGMENTATION
    //start = clock();
    
    
    mass_tot_all = 0.0;
    for(i=global_n_p+1;i<=global_n;++i){    
      
      //if(t_sys>frag[i].t_frag){
      if(t_[i]>frag[i].t_frag){
	frag[i].t_frag += frag[i].dt_frag;
	frag[i].fragtimes++;

	Calculate_OrbitalElements(i,x_c,v_c,ele,P,Q,r_c,v2_c,r_dot_v);  //軌道要素計算
	
	NeighborSearch(i,ele,frag,x_c);  //近傍(扇形領域に入った)粒子探索
	
	
	//printf("i=%d\tneighbornumber=%d\n",i,frag[i].neighbornumber);
	/*
	  for(j=1;j<=frag[i].neighbornumber;j++){
	  printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
	  }
	*/
	//printf("i=%d\tv_ave=%f\tsigma=%f\tecc=%f\tr_c=%f\tdelta_r=%f\n",i,frag[i].v_ave,frag[i].sigma,ele[i].ecc,r_c[i],frag[i].delta_r);

	MassFlux(i,ele,frag,para);  //質量フラックス計算
	frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール

	if(isnan(frag[i].dt_frag)){
	  //frag[i].dt_frag = dt_[i]*100.0;  //NaN処理
	  printf("time=%e[yr]\tfrag[%d].neighbornumber=%d\n",t_sys/2.0/M_PI,i,frag[i].neighbornumber);
	  /*
	  for(j=1;j<=frag[i].neighbornumber;j++){
	    printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
	  }
	  */
	  printf("i=%d\tv_ave=%f\tsigma=%f\tecc=%f\tr_c=%f\tdelta_r_out=%f\tdelta_r_in=%f\n",i,frag[i].v_ave,frag[i].sigma,ele[i].ecc,r_c[i],frag[i].delta_r_out,frag[i].delta_r_in);
	  printf("axis=%e\tecc=%e\tinc=%e\tu=%e\tOmega=%e\tomega=%e\n",ele[i].axis,ele[i].ecc,ele[i].inc,ele[i].u,ele[i].Omega,ele[i].omega);
	  printf("x=%f\ty=%f\tz=%f\n",x_c[i][1],x_c[i][2],x_c[i][3]);
	  return -1;
	}
	//frag[i].fragtimes = 0;
	
	
	ele[i].mass = MassDepletion(i,ele);  //トレーサー質量の減少を計算
	
	//printf("F[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\tr_c[%d]=%f\n",i,frag[i].flux,i,frag[i].sigma,i,frag[i].dt_frag/2.0/M_PI,i,dt_[i]/2.0/M_PI,i,r_c[i]);

      }
      mass_tot_all += ele[i].mass;
    }


    
    //printf("t=%e\tmass_tot=%.15f\tM_TOT=%.15e\n",t_sys,mass_tot,M_TOT);		
    //printf("t_sys=%e[yr]\tmass[1]=%e\n",t_sys/2.0/M_PI,ele[1].mass);
	
    //end = clock();
	
    //printf("t=%e[yr]\tfrag calculation time = %f [sec]\n",t_sys/2.0/M_PI,(double)(end-start)/CLOCKS_PER_SEC);
	

    if(t_sys>t_check){
      fpfrag = fopen(fragfile,"a");  //総質量をファイルへ書き出し
      if(fpfrag==NULL){
	printf("fragfile error\n");
	return -1;
      }
      fprintf(fpfrag,"%e\t%.15f\t%.15f\n",t_sys/2.0/M_PI,mass_tot_all,M_TOT);
      fclose(fpfrag);

      fpposimass = fopen(posimassfile,"a");  //位置、質量などをファイルへ書き出し
      if(fpposimass==NULL){
	printf("posimassfile error\n");
	return -1;
      }
      for(i=1;i<=global_n;i++){
	fprintf(fpposimass,"%e\t%04d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%d\n",t_sys/2.0/M_PI,i,x_c[i][1],x_c[i][2],x_c[i][3],r_c[i],sqrt(x_c[i][1]*x_c[i][1]+x_c[i][2]*x_c[i][2]),ele[i].mass,frag[i].delta_r_out,frag[i].delta_r_in,frag[i].sigma,frag[i].n_s,frag[i].neighbornumber);
      }
      fprintf(fpposimass,"\n\n");
      fclose(fpposimass);
      
      t_check *= sqrt(sqrt(sqrt(10.0)));  //logでは10を8分割
    }

    
#endif 

	
    
    
    
    if(fmod(step,1.0E6)==0.0){
    //if(fmod(step,1.0E2)==0.0){
      //printf("i_sys=%03d\tt=%.15e\tE=%.15e\tL=%.15e\tr_min=%.15e\n",i_sys,t_sys,E_tot,abs_L,r_min);  //全エネルギー,全角運動量
      printf("step=%e\tN=%d\ti_sys=%03d\tt=%.2e[yr]",step,global_n,i_sys,t_sys/2.0/M_PI);
      printf("\n");
    }
    


    if((i_col != 0) && (j_col != 0)){  //衝突した場合

      for(i=1;i<=global_n;++i){ 
	dt_[i] = Timestep_i_0(i,a_0,adot_0,abs_a,abs_adot);  //タイムステップ計算
	//printf("initial dt_[%d]=%e\n",i,dt_[i]);
      }

      t_sys = t_[1] + dt_[1];
      i_sys = 1;
      for(i=2;i<=global_n;++i){  
	if((t_[i] + dt_[i]) < t_sys){
	  t_sys = t_[i] + dt_[i];  //dt_i が最小のものを選ぶ
	  i_sys = i;  //i_sysを選ぶ
	}
      }
      
    }else if((i_col == 0) && (j_col == 0)){  //衝突しない場合
      
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
      for(i=2;i<=global_n;++i){
	if((t_[i] + dt_[i]) < t_sys){
	  t_sys = t_[i] + dt_[i];  //dt_i が最小のものを選ぶ
	  i_sys = i;  //i_sysを選ぶ
	}
      }
      
    }else{
      printf("Collision Judgement error\ti_col=%d\tj_col=%d\n",i_col,j_col);
      exit(-1);
    }
    
    
    
    
    step+=1.0;
  }  //t loop
  

  
#if ENERGY_FILE
  printf("dt_[i_sys]=%e\tE_error=%.15e\tL_error=%.15e\n",dt_[i_sys],(E_tot-E_tot_0)/fabs(E_tot_0),(abs_L-abs_L_0)/abs_L_0);
#endif
  
  printf("step=%e\n",step);
  
  for(i=0;i<TIME_INTERVAL_MAX;i++){
    printf("t_ene[%d]=%e\n",i,t_ene[i]);
  } 
}

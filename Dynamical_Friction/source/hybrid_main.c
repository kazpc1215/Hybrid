#define EXTERN
#include "hybrid.h"
#include "func.h"


//グローバル変数初期化
int global_n = N_p + N_tr;  //全粒子数.
int global_n_p = N_p;  //原始惑星の数.


#if EXECUTION_TIME
struct execution_time exetime =
  {
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0}
  };
#endif


int main(void){


#if EXECUTION_TIME
  //時間計測用.
  struct timeval realtime_start,realtime_end,realtime_start_main,realtime_end_main;
  struct rusage usage_start,usage_end,usage_start_main,usage_end_main;
#if FRAGMENTATION
  struct timeval realtime_start_2,realtime_end_2;
  struct rusage usage_start_2,usage_end_2;
#endif

  gettimeofday(&realtime_start_main,NULL);
  getrusage(RUSAGE_SELF,&usage_start_main);
#endif


#ifdef _OPENMP
  printf("OMP_NUM_THREADS: %s\n",getenv("OMP_NUM_THREADS"));
  printf("threads: %d\n", omp_get_max_threads());
#endif


  struct stat st;  //ファイル存在確認用.


  int i=0,j=0,i_sys=0,k=0,ite=0,i_col=0,j_col=0;
  double t_sys=0.0,t_tmp=0.0,step=0.0;
  static double t_[N_p+N_tr+1]={},dt_[N_p+N_tr+1]={},Dt[N_p+N_tr+1]={};
  static double x_0[N_p+N_tr+1][4]={},r_0[N_p+N_tr+1]={},v_0[N_p+N_tr+1][4]={},v2_0[N_p+N_tr+1]={};
  static double x_p[N_p+N_tr+1][4]={},r_p[N_p+N_tr+1]={},v_p[N_p+N_tr+1][4]={},v2_p[N_p+N_tr+1]={};
  static double x_c[N_p+N_tr+1][4]={},r_c[N_p+N_tr+1]={},v_c[N_p+N_tr+1][4]={},v2_c[N_p+N_tr+1]={};
  static double abs_r[N_p+N_tr+1]={},r_dot_v_ij[N_p+N_tr+1]={},r_dot_v[N_p+N_tr+1]={};
  static double a_0[N_p+N_tr+1][4]={},adot_0[N_p+N_tr+1][4]={};
  static double a[N_p+N_tr+1][4]={},adot[N_p+N_tr+1][4]={},adot2_dt2[N_p+N_tr+1][4]={},adot3_dt3[N_p+N_tr+1][4]={};
  double E_tot=0.0,E_tot_0=0.0,dE_correct=0.0;
  double abs_L=0.0,abs_L_0=0.0;


#if DT_LOG
  int interval;
  double t_ene[TIME_INTERVAL_MAX]={TIME_INTERVAL};
#else
  double t_ene=DT_ENE;
#endif

#if INDIRECT_TERM
  double x_G[4]={},v_G[4]={};
#endif


  static struct orbital_elements ele[N_p+N_tr+1]={};
  //struct orbital_elements *ele_p = ele;


#if FRAGMENTATION
  static struct fragmentation frag[N_p+N_tr+1]={};
  double t_check=2.0*M_PI*0.1;
  double mass_tot_all;
  struct parameter para;
  FILE *fpfrag;   //初期総質量をファイルへ書き出し.
  char fragfile[200]={};
  FILE *fpposimass;   //初期位置、質量などをファイルへ書き出し.
  char posimassfile[200]={};
#endif


#if ENERGY_FILE
  FILE *fpEne;
  char Ene[200]={};
#endif


#if POSI_VELO_FILE
  FILE *fpposivelo;
  char posivelofile[200]={};
#endif


#if POSI_VELO_ROT_FILE
  static double x_rot[N_p+N_tr+1][4]={};
  static double r_xy[N_p+N_tr+1]={},theta=0.0;
  FILE *fpposi_rot;
  char posi_rot[200]={};
#endif


#if COLLISION
  double dE_heat=0.0,dE_grav=0.0,dE_c=0.0,v_imp=0.0;
#if COLLISION_FILE
  FILE *fpcollision;
  char collisionfile[200]={};
  int n_col=0;
#endif
#endif


#if ORBITALELEMENTS_FILE
  FILE *fporbit;
  char orbit[200]={};
#endif


  FILE *fpinitial;
  char initialfile[200]={};

  FILE *fptempread;
  char tempreadfile[200]={};
  char buf[500]={};


  //////////////////////////////ここまで変数宣言//////////////////////////////////


#ifdef DIRECTORY
  mkdir(STR(DIRECTORY), 0755);  //ディレクトリを作成. 755 = rwxr-xr-x.
#elif DIRECTORY_FILE
  /*
    char mkdir_command[200]={};
    char dirname[200]={};
    sprintf(dirname,"../data/%s/",STR(DIRECTORY_FILE));
    mkdir(dirname, 0755);  //大きなディレクトリを作成. 755 = rwxr-xr-x.
    sprintf(dirname,"../data/%s/b%4.0f_%s/",STR(DIRECTORY_FILE),b*1E3,STR(DIRECTORY_FILE));
    sprintf(mkdir_command,"mkdir %s",dirname);  //小さなディレクトリを作成.
    system(mkdir_command);
    printf("making directory (%s)\n",dirname);
  */
#endif


#if ENERGY_FILE
  sprintf(Ene,"%sENERGY.dat",
#ifdef DIRECTORY
	  STR(DIRECTORY)
#elif DIRECTORY_FILE
	  dirname
#endif
	  );
#endif


#if POSI_VELO_FILE
  sprintf(posivelofile,"%sPosi_Velo.dat",
#ifdef DIRECTORY
	  STR(DIRECTORY)
#elif DIRECTORY_FILE
	  dirname
#endif
	  );
#endif


#if FRAGMENTATION
    sprintf(fragfile,"%sTotalMass.dat",
#ifdef DIRECTORY
	  STR(DIRECTORY)
#elif DIRECTORY_FILE
	  dirname
#endif
	  );

    sprintf(posimassfile,"%sPosi_Mass.dat",
#ifdef DIRECTORY
	    STR(DIRECTORY)
#elif DIRECTORY_FILE
	    dirname
#endif
	    );
#endif


  sprintf(initialfile,"%sinitial.dat",
#ifdef DIRECTORY
	  STR(DIRECTORY)
#elif DIRECTORY_FILE
	  dirname
#endif
	  );


  sprintf(tempreadfile,"%stempread.dat",
#ifdef DIRECTORY
	  STR(DIRECTORY)
#elif DIRECTORY_FILE
	  dirname
#endif
	  );



  if(stat(tempreadfile,&st)==0){  //読み込むファイルの存在確認.

    printf("file: '%s' exists.\n",tempreadfile);

    fptempread = fopen(tempreadfile,"r");
    if(fptempread==NULL){
      printf("tempreadfile error\n");
      return -1;
    }

    fgets(buf,sizeof(buf),fptempread);  //読み飛ばし.
    fgets(buf,sizeof(buf),fptempread);
    sscanf(buf,"%lf\t%lf\t%lf\t%d\t%d\t%d\t%lf\t%lf\t%lf\t%lf\n",
	   &t_tmp,
	   &t_sys,
	   &t_ene,
	   &global_n_p,
	   &global_n,
	   &i_sys,
	   &step,
	   &E_tot_0,
	   &abs_L_0,
	   &dE_correct
	   );

    fgets(buf,sizeof(buf),fptempread);  //読み飛ばし.
    fgets(buf,sizeof(buf),fptempread);  //読み飛ばし.
    fgets(buf,sizeof(buf),fptempread);  //読み飛ばし.

    for(i=1;i<=global_n;++i){
      if(fgets(buf,sizeof(buf),fptempread)!=NULL){
	sscanf(buf,"%s\t%lf\t%lf\t%lf\t%*f\t%lf\t%lf\t%lf\t%*f\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
	       ele[i].name,
	       &x_0[i][1],
	       &x_0[i][2],
	       &x_0[i][3],
	       &v_0[i][1],
	       &v_0[i][2],
	       &v_0[i][3],
	       &a_0[i][1],
	       &a_0[i][2],
	       &a_0[i][3],
	       &adot_0[i][1],
	       &adot_0[i][2],
	       &adot_0[i][3],
	       &t_[i],
	       &dt_[i],
	       &ele[i].mass
	       );

	t_[i] = 2.0*M_PI*t_[i];
	dt_[i] = 2.0*M_PI*dt_[i];

	ele[i].radius = cbrt(3.0/4.0/M_PI*ele[i].mass*1.989E33/PLANET_DENSITY)/1.496E13;

	r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離.
	v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗.
	r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積.

      }else{
	printf("%s: i=%d line is NULL.\n",
	       tempreadfile,
	       i
	       );
      }
    }

    fclose(fptempread);

    /*
    for(i=1;i<=global_n_p;++i){
      sprintf(ele[i].name,"Planet%02d",ele[i].orinum);
    }
    for(i=global_n_p+1;i<=global_n;++i){
      sprintf(ele[i].name,"tracer%06d",ele[i].orinum-global_n_p);
    }
    */

  }else{


    printf("file: '%s' does not exist.\n",tempreadfile);


    char cat_header[200]={};
    char headerfile[10]="hybrid.h";
    sprintf(cat_header,"cat %s > %sheaderfile.txt",
	    headerfile,
#ifdef DIRECTORY
	    STR(DIRECTORY)
#elif DIRECTORY_FILE
	    dirname
#endif
	    );
    system(cat_header);  //headerファイルをテキストとしてdataに残す


    char cat_main[200]={};
    char mainfile[20]="hybrid_main.c";
    sprintf(cat_main,"cat %s > %smainfile.txt",
	    mainfile,
#ifdef DIRECTORY
	    STR(DIRECTORY)
#elif DIRECTORY_FILE
	    dirname
#endif
	    );
    system(cat_main);  //mainファイルをテキストとしてdataに残す


    ///////////////////////////////ここまで初期処理//////////////////////////////////


    srand(RAND_SEED);


    /*
      ele[1].mass = PLANET_MASS;
      ele[1].axis = PLANET_INNER_AXIS;
      #ifndef M_0
      ele[1].r_h = ele[1].axis*cbrt(ele[1].mass/3.0);
      #else
      ele[1].r_h = ele[1].axis*cbrt(ele[1].mass/M_0/3.0);
      #endif

      for(i=2;i<=global_n_p;++i){
      ele[i].mass = PLANET_MASS;
      ele[i].axis = ele[i-1].axis * (1.0/DELTA_AXIS + 0.5*cbrt((ele[i-1].mass+ele[i].mass)/3.0))/(1.0/DELTA_AXIS - 0.5*cbrt((ele[i-1].mass+ele[i].mass)/3.0));  //相互Hill半径 の DELTA_AXIS倍 間隔.

      #ifndef M_0
      ele[i].r_h = ele[i].axis*cbrt(ele[i].mass/3.0);
      #else
      ele[i].r_h = ele[i].axis*cbrt(ele[i].mass/M_0/3.0);
      #endif
      }
    */


    for(i=1;i<=global_n_p;++i){  //惑星.
      Initial_OrbitalElements_Planet(i,ele);  //初期軌道要素.
      InitialCondition(i,x_0,v_0,v2_0,r_dot_v,r_0,ele);  //初期位置、速度計算.
    }


#if N_tr != 0

#if FRAGMENTATION
    para.alpha = (11.0 + 3.0*P_FRAG)/(6.0 + 3.0*P_FRAG);
    para.s_1 = s_1_FRAG(&para);
    para.s_2 = s_2_FRAG(&para);
    para.s_3 = s_3_FRAG(&para);
    para.h_0 = 0.061*17.3*pow(1.68E6*RHO,-2.0/3.0);  // g/cc = 1.68E6 M_0/AU^3, F(I) = 17.3 として.
    para.Q_D = Q_0_FRAG*1.13E-13*pow(RHO/3.0,0.55)*pow(M_MAX*1.989E12,P_FRAG);  //erg/g = 1.13E-13 AU^2/(yr/2pi)^2 として.

    printf("alpha=%f\ts_1=%f\ts_2=%f\ts_3=%f\n",
	   para.alpha,
	   para.s_1,
	   para.s_2,
	   para.s_3
	   );
#endif


#if EJECTION
    static double x_eject[N_p+N_tr+1][4]={};
    static double v_eject[N_p+N_tr+1][4]={};
    double tmp_x,tmp_y,tmp_r,tmp_theta;
    //double tmp_rand1;
    double tmp_rand2;
    double tmp_v;
#ifndef G
    double ejection_velocity = sqrt(2.0*ele[PLANET_NO].mass/ele[PLANET_NO].radius);
#else
    double ejection_velocity = sqrt(2.0*G*ele[PLANET_NO].mass/ele[PLANET_NO].radius);
#endif

    for(i=global_n_p+1;i<=global_n;++i){
      sprintf(ele[i].name,"tracer%06d",i-global_n_p);
      ele[i].mass = M_TOT/(double)N_tr;
      ele[i].orinum = i;


      /*
	tmp_r = ele[PLANET_NO].radius*(1.0 + 1.0*((double)rand())/((double)RAND_MAX+1.0));
	//tmp_rand1 = ((double)rand())/((double)RAND_MAX+1.0)*M_PI;  //theta
	tmp_rand2 = ((double)rand())/((double)RAND_MAX+1.0)*2.0*M_PI;  //phi
      */
      tmp_r = ele[PLANET_NO].radius*(1.0 + 0.1*(int)((double)(i-global_n_p-1)/100.0));
      tmp_rand2 = 2.0*M_PI/100.0*(double)(i-global_n_p-1);


      //cone
      x_eject[i][1] = tmp_r*cos(EJECTION_CONE_ANGLE);  //破片のx座標.
      x_eject[i][2] = tmp_r*sin(EJECTION_CONE_ANGLE)*cos(tmp_rand2);  //破片のy座標.
      x_eject[i][3] = tmp_r*sin(EJECTION_CONE_ANGLE)*sin(tmp_rand2);  //破片のz座標.


      /*
      //isotropic
      x_eject[i][1] = tmp_r*sin(tmp_rand1)*cos(tmp_rand2);  //破片のx座標.
      x_eject[i][2] = tmp_r*sin(tmp_rand1)*sin(tmp_rand2);  //破片のx座標.
      x_eject[i][3] = tmp_r*cos(tmp_rand1);  //破片のx座標.
      */


      //Rotation_3D_zaxis(i,x_eject,M_PI);  //z軸周りに180度回転.
      //Rotation_3D_zaxis(i,x_eject,M_PI/2.0);  //z軸周りに90度回転.
      Rotation_3D_zaxis(i,x_eject,-M_PI/2.0);  //z軸周りに-90度回転.


      //printf("%s\tx_eject[%d][1]=%f\tx_eject[%d][2]=%f\tx_eject[%d][3]=%f\n",ele[i].name,i,x_eject[i][1],i,x_eject[i][2],i,x_eject[i][3]);


      //tmp_v = ejection_velocity;
      tmp_v = ejection_velocity*(0.9+0.1*tmp_r/ele[PLANET_NO].radius);
      tmp_theta = EJECTION_CONE_ANGLE*tmp_r/ele[PLANET_NO].radius;
      //tmp_theta = EJECTION_CONE_ANGLE;


      //cone
      v_eject[i][1] = tmp_v*cos(tmp_theta);  //破片の速度x成分.
      v_eject[i][2] = tmp_v*sin(tmp_theta)*cos(tmp_rand2);  //破片の速度y成分.
      v_eject[i][3] = tmp_v*sin(tmp_theta)*sin(tmp_rand2);  //破片の速度z成分.


      /*
      //isotropic
      v_eject[i][1] = tmp_v*sin(tmp_rand1)*cos(tmp_rand2);  //破片の速度x成分.
      v_eject[i][2] = tmp_v*sin(tmp_rand1)*sin(tmp_rand2);  //破片の速度y成分.
      v_eject[i][3] = tmp_v*cos(tmp_rand1);  //破片の速度z成分..
      */


      //Rotation_3D_zaxis(i,v_eject,M_PI);  //z軸周りに180度回転.
      //Rotation_3D_zaxis(i,v_eject,M_PI/2.0);  //z軸周りに90度回転.
      Rotation_3D_zaxis(i,v_eject,-M_PI/2.0);  //z軸周りに-90度回転.


      //printf("%s\tv_eject[%d][1]=%f\tv_eject[%d][2]=%f\tv_eject[%d][3]=%f\n",ele[i].name,i,v_eject[i][1],i,v_eject[i][2],i,v_eject[i][3]);
      //////////////////ここまでで、惑星中心、xyは軌道面上、x軸は太陽から惑星の方向/////////////////////


      //位置.
      tmp_x = x_eject[i][1];
      tmp_y = x_eject[i][2];

      x_eject[i][1] = cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x - sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;

      x_eject[i][2] = sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x + cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;

      //速度.
      tmp_x = v_eject[i][1];
      tmp_y = v_eject[i][2];

      v_eject[i][1] = cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x - sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;

      v_eject[i][2] = sin((sqrt(1.0-ele[PLANET_NO].ecc*ele[PLANET_NO].ecc)*sin(ele[PLANET_NO].u))/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_x + cos((ele[PLANET_NO].u-ele[PLANET_NO].ecc)/(1.0-ele[PLANET_NO].ecc*cos(ele[PLANET_NO].u)))*tmp_y;


      //////////////////ここまでで、惑星中心、xyは軌道面上、x軸は惑星の近日点の方向/////////////////////


      //位置.
      Rotation_3D_zaxis(i,x_eject,ele[PLANET_NO].Omega);
      Rotation_3D_xaxis(i,x_eject,ele[PLANET_NO].inc);
      Rotation_3D_zaxis(i,x_eject,ele[PLANET_NO].omega);

      //速度.
      Rotation_3D_zaxis(i,v_eject,ele[PLANET_NO].Omega);
      Rotation_3D_xaxis(i,v_eject,ele[PLANET_NO].inc);
      Rotation_3D_zaxis(i,v_eject,ele[PLANET_NO].omega);
      //////////////////ここまでで、惑星中心に平行移動した基準系/////////////////////


      for(k=1;k<=3;++k){
	x_0[i][k] = x_0[PLANET_NO][k] + x_eject[i][k];  //基準系での破片の座標.
	v_0[i][k] = v_0[PLANET_NO][k] + v_eject[i][k];
      }


      r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離.
      v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗.
      r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積.
    }
#endif


#if ORBITING_SMALL_PARTICLE
    for(i=global_n_p+1;i<=global_n;++i){  //微惑星.
      Initial_OrbitalElements_Tracer(i,ele);  //初期軌道要素.
      InitialCondition(i,x_0,v_0,v2_0,r_dot_v,r_0,ele);  //初期位置、速度計算.
    }
#endif


#if POSI_VELO_FILE
    //初期位置、速度をファイルへ書き出し.
    fpposivelo= fopen(posivelofile,"w");
    if(fpposivelo==NULL){
      printf("posivelofile 0 error\n");
      return -1;
    }
    fprintf(fpposivelo,"#t[yr]\ti\tx\ty\tz\tr_0(3D)\tr_0(2D)\tv_x\tv_y\tv_z\tabs_v\n");
    for(i=1;i<=global_n;i++){
      fprintf(fpposivelo,"%.15e\t%4d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\n",
	      0.0,
	      i,
	      x_0[i][1],
	      x_0[i][2],
	      x_0[i][3],
	      r_0[i],
	      sqrt(x_0[i][1]*x_0[i][1]+x_0[i][2]*x_0[i][2]),
	      v_0[i][1],
	      v_0[i][2],
	      v_0[i][3],
	      sqrt(v_0[i][1]*v_0[i][1]+v_0[i][2]*v_0[i][2]+v_0[i][3]*v_0[i][3])
	      );
    }
    fprintf(fpposivelo,"\n\n");
    fclose(fpposivelo);
#endif


#if POSI_VELO_ROT_FILE
    //回転座標系でプロット
    r_xy[PLANET_NO] = sqrt(x_0[PLANET_NO][1]*x_0[PLANET_NO][1]+x_0[PLANET_NO][2]*x_0[PLANET_NO][2]);
    r_xy[PLANETESIMAL_NO] = sqrt(x_0[PLANETESIMAL_NO][1]*x_0[PLANETESIMAL_NO][1]+x_0[PLANETESIMAL_NO][2]*x_0[PLANETESIMAL_NO][2]);
    theta = atan2(x_0[PLANET_NO][2],x_0[PLANET_NO][1]);


    x_rot[PLANETESIMAL_NO][1] = x_0[PLANETESIMAL_NO][1];
    x_rot[PLANETESIMAL_NO][2] = x_0[PLANETESIMAL_NO][2];
    Rotation_3D_zaxis(PLANETESIMAL_NO,x_rot,-theta);


    x_rot[PLANET_NO][1] = x_0[PLANET_NO][1];
    x_rot[PLANET_NO][2] = x_0[PLANET_NO][2];
    Rotation_3D_zaxis(PLANET_NO,x_rot,-theta);


    sprintf(posi_rot,"%s%s_posi_rot.dat",
#ifdef DIRECTORY
	    STR(DIRECTORY)
#elif DIRECTORY_FILE
	    dirname
#endif
	    ,ele[PLANETESIMAL_NO].name);
    fpposi_rot = fopen(posi_rot,"w");
    if(fpposi_rot==NULL){
      printf("posi_rot error\n");
      return -1;
    }
    fprintf(fpposi_rot,"#t[yr]\tx_rot[2]\ty_rot[2]\tz[2]\tr_xy[2]\ttheta[2]\tradius[2]\tx_rot[1]\ty_rot[1]\tz[1]\tr_xy[1]\ttheta[1]\tradius[1]\tr_Hill\n");
    fprintf(fpposi_rot,"%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
	    0.0,
	    x_rot[PLANETESIMAL_NO][1],
	    x_rot[PLANETESIMAL_NO][2],
	    x_0[PLANETESIMAL_NO][3],
	    r_xy[PLANETESIMAL_NO],
	    atan2(x_rot[PLANETESIMAL_NO][2],x_rot[PLANETESIMAL_NO][1]),
	    ele[PLANETESIMAL_NO].radius,
	    x_rot[PLANET_NO][1],
	    x_rot[PLANET_NO][2],
	    x_0[PLANET_NO][3],
	    r_xy[PLANET_NO],
	    atan2(x_rot[PLANET_NO][2],x_rot[PLANET_NO][1]),
	    ele[PLANET_NO].radius,
	    ele[PLANET_NO].r_h
	    );
    fclose(fpposi_rot);
#endif


#if ORBITALELEMENTS_FILE

#if EXECUTION_TIME
    gettimeofday(&realtime_start,NULL);
    getrusage(RUSAGE_SELF,&usage_start);
#endif
    //初期の軌道要素をファイルへ書き出し.
    for(i=1;i<=global_n;++i){
      sprintf(orbit,"%s%s.dat",
#ifdef DIRECTORY
	      STR(DIRECTORY)
#elif DIRECTORY_FILE
	      dirname
#endif
	      ,ele[i].name);
      fporbit = fopen(orbit,"w");
      if(fporbit==NULL){
	printf("orbit 0 error\n");
	exit(-1);
      }

      fprintf(fporbit,"#t[yr]\te\ta\tu\tI\tOMEGA\tomega\tR_H\tradius\tmass\n");
      fprintf(fporbit,"%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
	      0.0,
	      ele[i].ecc,
	      ele[i].axis,
	      ele[i].u,
	      ele[i].inc,
	      ele[i].Omega,
	      ele[i].omega,
	      ele[i].r_h,
	      ele[i].radius,
	      ele[i].mass
	      );
      fclose(fporbit);
    }
#if EXECUTION_TIME
    gettimeofday(&realtime_end,NULL);
    getrusage(RUSAGE_SELF,&usage_end);
    exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
    exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
    exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif


#if ENERGY_FILE

#if INDIRECT_TERM
    CenterOfGravity(x_0,v_0,x_G,v_G,ele);  //重心計算.
#endif

#if EXECUTION_TIME
    gettimeofday(&realtime_start,NULL);
    getrusage(RUSAGE_SELF,&usage_start);
#endif
    //初期エネルギー計算.
    E_tot_0 = 0.0;
    E_tot_0 = Calculate_Energy(ele,x_0,
#if INDIRECT_TERM
			       v_0,v_G,
#else
			       v2_0,
#endif
			       r_0);

    //初期エネルギーをファイルへ書き出し.
    fpEne = fopen(Ene,"w");
    if(fpEne==NULL){
      printf("Ene 0 error\n");
      return -1;
    }
    fprintf(fpEne,"#t[yr]\tE_tot\trelative E error\trelative dE_correct\tstep\n");
    fprintf(fpEne,"%.15e\t%.15e\t%.15e\t%.15e\t%15e\n",
	    0.0,
	    E_tot_0,
	    0.0,
	    dE_correct/fabs(E_tot_0),
	    0.0
	    );
    fclose(fpEne);

    //角運動量の大きさ計算.
    abs_L_0 = 0.0;
    abs_L_0 = AngularMomentum(i,ele,x_0,v_0);
#if EXECUTION_TIME
    gettimeofday(&realtime_end,NULL);
    getrusage(RUSAGE_SELF,&usage_end);
    exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
    exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
    exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif


    fpinitial = fopen(initialfile,"w");
    if(fpinitial==NULL){
      printf("initialfile error\n");
      return -1;
    }
    fprintf(fpinitial,"#t_tmp\tt_sys\ti_sys\tE_tot_0\tabs_L_0\tdE_correct\n");
    fprintf(fpinitial,"%.15e\t%.15e\t%6d\t\t%.15e\t%.15e\t%.15e\n",
	    t_tmp,
	    t_sys,
	    i_sys,
	    E_tot_0,
	    abs_L_0,
	    dE_correct
	    );
    fprintf(fpinitial,"\n\n");
    fprintf(fpinitial,"#number\tx[AU]\ty[AU]\tz[AU]\t|r|[AU]\tvx[2piAU/yr]\tvy[2piAU/yr]\tvz[2piAU/yr]\t|v|[2piAU/yr]\tdt[yr]\tmass[Msun]\n");
    for(i=1;i<=global_n;++i){
      fprintf(fpinitial,"%6d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%e\t%e\n",
	      i,
	      x_0[i][1],
	      x_0[i][2],
	      x_0[i][3],
	      r_0[i],
	      v_0[i][1],
	      v_0[i][2],
	      v_0[i][3],
	      sqrt(v2_0[i]),
	      dt_[i]/2.0/M_PI,
	      ele[i].mass
	      );
    }
    fclose(fpinitial);


#if N_tr != 0

#if FRAGMENTATION

#if EXECUTION_TIME
    gettimeofday(&realtime_start,NULL);
    getrusage(RUSAGE_SELF,&usage_start);
#endif

    mass_tot_all = 0.0;
    for(i=global_n_p+1;i<=global_n;++i){

      frag[i].fragtimes = 0;
      NeighborSearch(i,ele,frag,x_0);  //近傍(扇形領域に入った)粒子探索.
      printf("i=%d\tneighbornumber=%d\n",
	     i,
	     frag[i].neighbornumber
	     );
      /*
	for(j=1;j<=frag[i].neighbornumber;j++){
	printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
	}
	printf("i=%d\tv_ave=%f\tsigma=%f\n",i,frag[i].v_ave,frag[i].sigma);
      */
      //printf("initial\tF[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\n",i,frag[i].flux,i,frag[i].sigma,i,frag[i].dt_frag/2.0/M_PI,i,dt_[i]/2.0/M_PI);
      MassFlux(i,ele,frag,&para);  //質量フラックス計算.
      frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール.
      frag[i].t_frag = frag[i].dt_frag;
      printf("\tinitial\tF[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\n",
	     i,
	     frag[i].flux,
	     i,
	     frag[i].sigma,
	     i,
	     frag[i].dt_frag/2.0/M_PI,
	     i,
	     dt_[i]/2.0/M_PI
	     );
      printf("\ti=%d\tv_ave=%f\tsigma=%f\tecc=%f\tr_0=%f\tdelta_r_out=%f\tdelta_r_in=%f\n",
	     i,
	     frag[i].v_ave,
	     frag[i].sigma,
	     ele[i].ecc,
	     r_0[i],
	     frag[i].delta_r_out,
	     frag[i].delta_r_in
	     );
      mass_tot_all += ele[i].mass;
    }


    //printf("t=%e\tmass_tot=%.15e\tM_TOT=%.15e\n",0.0,mass_tot,M_TOT);
    //printf("t_sys=%e[yr]\tmass[1]=%e\n",t_sys/2.0/M_PI,ele[1].mass);
    //printf("t=%e[yr]\tfrag calculation time = %f [sec]\n",t_sys/2.0/M_PI,(double)(end-start)/CLOCKS_PER_SEC);



    fpfrag = fopen(fragfile,"w");
    if(fpfrag==NULL){
      printf("fragfile 0 error\n");
      return -1;
    }
    fprintf(fpfrag,"#t[yr]\tmass_tot_all\tM_TOT\n");
    fprintf(fpfrag,"%.15e\t%.15f\t%.15f\n",
	    0.0,
	    mass_tot_all,
	    M_TOT
	    );
    fclose(fpfrag);


    fpposimass= fopen(posimassfile,"w");
    if(fpposimass==NULL){
      printf("posimassfile 0 error\n");
      return -1;
    }
    fprintf(fpposimass,"#t[yr]\ti\tx\ty\tz\tr_0(3D)\tr_0(2D)\tmass\tdelta_r\tsigma\tn_s\tneighbornumber\n");
    for(i=1;i<=global_n;i++){
      fprintf(fpposimass,"%.15e\t%4d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%d\n",
	      0.0,
	      i,
	      x_0[i][1],
	      x_0[i][2],
	      x_0[i][3],
	      r_0[i],
	      sqrt(x_0[i][1]*x_0[i][1]+x_0[i][2]*x_0[i][2]),
	      ele[i].mass,
	      frag[i].delta_r_out,
	      frag[i].delta_r_in,
	      frag[i].sigma,
	      frag[i].n_s,
	      frag[i].neighbornumber
	      );
    }
    fprintf(fpposimass,"\n\n");
    fclose(fpposimass);

#if EXECUTION_TIME
    gettimeofday(&realtime_end,NULL);
    getrusage(RUSAGE_SELF,&usage_end);
    exetime.Fragmentation[0] += Cal_time(realtime_start,realtime_end);
    exetime.Fragmentation[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
    exetime.Fragmentation[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif

#endif

    ////////////////////////////ここまででファイルを上書きオープン/////////////////////////


  }


  ////////////////////////////////////ここまでで初期条件//////////////////////////////////////


  if(stat(tempreadfile,&st)!=0){  //読み込むファイルがない場合.

    //#pragma omp parallel for private(j,k,abs_r,r_dot_v_ij)
    for(i=1;i<=global_n;++i){
      for(j=1;j<=
#if INTERACTION_ALL
	    global_n
#elif INTERACTION_PLANET_TRACER
	    global_n
#elif INTERACTION_TEST_PARTICLE
	    global_n_p
#endif
	    ;++j){
	if(i!=j){
	  abs_r[j] = RelativeDistance(i,j,x_0);  //絶対値.
	  r_dot_v_ij[j] = RelativeInnerProduct(i,j,x_0,v_0);  //r_ij,v_ijの内積.
	}else{
	  abs_r[i] = 0.0;
	  r_dot_v_ij[i] = 0.0;
	}
      }  //j loop

      for(k=1;k<=3;++k){
	a_0[i][k] = All_Acceleration(i,k,ele,x_0,r_0,abs_r);  //初期の加速度.
	adot_0[i][k] = All_dAcceleration(i,k,ele,x_0,v_0,r_dot_v,r_dot_v_ij,r_0,abs_r);
	//printf("a_0[%d][%d]=%f\tadot_0[%d][%d]=%f\n",i,k,a_0[i][k],i,k,adot_0[i][k]);
      }
    }


    for(i=1;i<=global_n;++i){
      //初期のタイムステップ計算.
      dt_[i] = Timestep_i_0(i,a_0,adot_0);
      //printf("initial dt_[%d]=%e\n",i,dt_[i]);
    }

  }


  /////////////////////////////ここまでで加速度，タイムステップ計算//////////////////////////////


#if EXECUTION_TIME
  gettimeofday(&realtime_start,NULL);
  getrusage(RUSAGE_SELF,&usage_start);
#endif
  for(i=global_n_p+1;i<=global_n;++i){
    Calculate_OrbitalElements(i,x_0,v_0,ele,r_0,v2_0,r_dot_v);
  }
#if EXECUTION_TIME
  gettimeofday(&realtime_end,NULL);
  getrusage(RUSAGE_SELF,&usage_end);
  exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
  exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
  exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif
#endif


  printf("-----\n");
  printf("#step\t\tNp\tNtr\ti_sys\tdt[i_sys]\t\tt_tmp[yr]\t\tt_sys[yr]\n");
  printf("%e\t%3d\t%6d\t%6d\t%.15e\t%.15e\t%.15e\n",
	 step,
	 global_n_p,
	 global_n-global_n_p,
	 i_sys,
	 dt_[i_sys]/2.0/M_PI,
	 t_tmp/2.0/M_PI,
	 t_sys/2.0/M_PI
	 );

  ////////////////////////////////////////////////////////////////////////////////////

#if DT_LOG
  interval = 0;
#endif

  while(
#if DT_LOG
	TIME_INTERVAL_MAX > interval
#else
	t_sys + t_tmp <= T_MAX
#endif
	){

    step+=1.0;

    t_sys = t_[1] + dt_[1];
    i_sys = 1;
    for(i=2;i<=global_n;++i){
      if((t_[i] + dt_[i]) < t_sys){
	t_sys = t_[i] + dt_[i];  //dt_[i]が最小のものを選ぶ.
	i_sys = i;  //i_sysを選ぶ.
     }
    }


    if(
#if DT_LOG
       t_sys + t_tmp < t_ene[interval]
#else
       t_sys + t_tmp < t_ene
#endif
       ){

      //individual timestep

#if EXECUTION_TIME
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      //#pragma omp parallel for schedule(runtime)
      for(i=1;i<=global_n;++i){
	Dt[i] = t_sys - t_[i];
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,r_dot_v,Dt);  //予測子 t_sysにおけるすべての粒子を計算.
      }
#if EXECUTION_TIME
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Predictor[0] += Cal_time(realtime_start,realtime_end);
      exetime.Predictor[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Predictor[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


      if(
#if COLLISION
	 (i_sys <= global_n_p) && Collision_Judgement(i_sys,ele,x_p,abs_r,&i_col,&j_col)
#else
	 false
#endif
	 ){  //予測子を用いた衝突判定.

#if COLLISION
	/////////////////////////衝突した場合/////////////////////////
	printf("collision\ti=%d, j=%d\n",i_col,j_col);
	printf("r_ij=%.15e\tradius[%d]+radius[%d]=%.15e\n",
	       abs_r[j_col],
	       i_col,
	       j_col,
	       ele[i_col].radius + ele[j_col].radius
	       );


	//t_sysで揃えるためDt[i]を使う.
#if EXECUTION_TIME
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(i=1;i<=global_n;++i){
	  Corrector_sys(i,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,Dt);  //修正子 すべての粒子.
	}
#if EXECUTION_TIME
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Corrector[0] += Cal_time(realtime_start,realtime_end);
	exetime.Corrector[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Corrector[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(ite=1;ite<=ITE_MAX;++ite){  //iteration.
	  for(i=1;i<=global_n;++i){
	    Iteration_sys(i,ele,x_p,v_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,Dt);  //すべての粒子.
	  }
	}
#if EXECUTION_TIME
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Iteration[0] += Cal_time(realtime_start,realtime_end);
	exetime.Iteration[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Iteration[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


	for(i=1;i<=global_n;++i){  //位置と速度を更新.
	  for(k=1;k<=3;++k){
	    x_0[i][k] = x_c[i][k];
	    v_0[i][k] = v_c[i][k];
	  }
	}


#if COALESCENCE
	//新しい合体粒子を作る. 0番目の要素はコピーに使うだけ.
	for(k=1;k<=3;++k){
	  x_0[0][k] = (ele[i_col].mass*x_0[i_col][k] + ele[j_col].mass*x_0[j_col][k])/(ele[i_col].mass + ele[j_col].mass);
	  v_0[0][k] = (ele[i_col].mass*v_0[i_col][k] + ele[j_col].mass*v_0[j_col][k])/(ele[i_col].mass + ele[j_col].mass);
	}


#if EXECUTION_TIME
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	//衝突合体する際のエネルギーの補正量を計算
	Energy_Correction(i_col,j_col,x_0,v_0,ele,&dE_heat,&dE_grav,&dE_c,&v_imp);
#if EXECUTION_TIME
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
	exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif
#endif


#if COLLISION_FILE
	//衝突時の位置速度をファイルへ書き出し.
	n_col++;
	sprintf(collisionfile,"%sCollision_%02d.dat",
#ifdef DIRECTORY
		STR(DIRECTORY)
#elif DIRECTORY_FILE
		dirname
#endif
		,n_col
		);
	fpcollision= fopen(collisionfile,"w");
	if(fpcollision==NULL){
	  printf("collisionfile 0 error\n");
	  exit(-1);
	}
	fprintf(fpcollision,"#i_col=%d\tj_col=%d\tr_ij=%.15e\tradius[%d]+radius[%d]=%.15e\n",
		i_col,
		j_col,
		abs_r[j_col],
		i_col,
		j_col,
		ele[i_col].radius + ele[j_col].radius
		);
	fprintf(fpcollision,"#dE_heat=%e\tdE_grav=%e\tdE_c=%e\tv_imp=%e\n",
		dE_heat,
		dE_grav,
		dE_c,
		v_imp
		);
	fprintf(fpcollision,"#t[yr]\ti\tx\ty\tz\tr_0(3D)\tr_0(2D)\tv_x\tv_y\tv_z\tabs_v\tR_Hill\tRadius\n");
	for(i=1;i<=global_n;i++){
	  fprintf(fpcollision,"%.15e\t%4d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15e\t%.15e\n",
		  (t_sys+t_tmp)/2.0/M_PI,
		  i,
		  x_c[i][1],
		  x_c[i][2],
		  x_c[i][3],
		  r_c[i],
		  sqrt(x_c[i][1]*x_c[i][1]+x_c[i][2]*x_c[i][2]),
		  v_c[i][1],
		  v_c[i][2],
		  v_c[i][3],
		  sqrt(v_c[i][1]*v_c[i][1]+v_c[i][2]*v_c[i][2]+v_c[i][3]*v_c[i][3]),
		  ele[i].r_h,
		  ele[i].radius
		  );
	}
	fclose(fpcollision);
#endif


#if COALESCENCE
	Coalescence(i_col,j_col,x_0,v_0,ele);  //合体後の操作.
#endif


#if RELOCATE_PARTICLE
	if(j_col>global_n_p){
	  Initial_OrbitalElements_Tracer(j_col,ele);  //衝突後に粒子を再配置.
	}
#endif


	//以下、すべての粒子の加速度などを再計算.
	for(i=1;i<=global_n;++i){
	  r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離.
	  v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗.
	  r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積.
	}

#if EXECUTION_TIME
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(i=1;i<=global_n;++i){
	  Calculate_OrbitalElements(i,x_0,v_0,ele,r_0,v2_0,r_dot_v);
	}
#if EXECUTION_TIME
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
	exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if ENERGY_FILE

#if INDIRECT_TERM
	CenterOfGravity(x_0,v_0,x_G,v_G,ele);  //重心計算.
	//printf("x_G=%.15e\ty_G=%.15e\tz_G=%.15e\tvx_G=%.15e\tvy_G=%.15e\tvz_G=%.15e\n",x_G[1],x_G[2],x_G[3],v_G[1],v_G[2],v_G[3]);
#endif

#if EXECUTION_TIME
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	E_tot = Calculate_Energy(ele,x_0,
#if INDIRECT_TERM
				 v_0,v_G,
#else
				 v2_0,
#endif
				 r_0);  //エネルギー計算.
	dE_correct += - dE_heat - dE_grav - dE_c;  //エネルギー補正計算
	E_tot += dE_correct;  //補正をする


	fpEne = fopen(Ene,"a");
	if(fpEne==NULL){
	  printf("Ene error\n");
	  return -1;
	}
	fprintf(fpEne,"#collision occur\t%e[yr]\n",(t_sys+t_tmp)/2.0/M_PI);
	fprintf(fpEne,"#dE_heat=%e\tdE_grav=%e\tdE_c=%e\tv_imp=%e\n",
		dE_heat,
		dE_grav,
		dE_c,
		v_imp
		);
	fprintf(fpEne,"%.15e\t%.15e\t%.15e\t%.15e\t%15e\n",
		(t_sys+t_tmp)/2.0/M_PI,
		E_tot,
		(E_tot-E_tot_0)/fabs(E_tot_0),
		dE_correct/fabs(E_tot_0),
		step
		);
	fclose(fpEne);

	abs_L = AngularMomentum(i,ele,x_0,v_0);

#if EXECUTION_TIME
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
	exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif


	//#pragma omp parallel for private(j,k,abs_r,r_dot_v_ij)
	for(i=1;i<=global_n;++i){
	  for(j=1;j<=
#if INTERACTION_ALL
		global_n
#elif INTERACTION_PLANET_TRACER
		global_n
#elif INTERACTION_TEST_PARTICLE
		global_n_p
#endif
		;++j){
	    if(i!=j){
	      abs_r[j] = RelativeDistance(i,j,x_0);  //絶対値.
	      r_dot_v_ij[j] = RelativeInnerProduct(i,j,x_0,v_0);  //r_ij,v_ijの内積.
	    }else{
	      abs_r[i] = 0.0;
	      r_dot_v_ij[i] = 0.0;
	    }
	  }  //j loop

	  for(k=1;k<=3;++k){
	    a_0[i][k] = All_Acceleration(i,k,ele,x_0,r_0,abs_r);  //加速度.
	    adot_0[i][k] = All_dAcceleration(i,k,ele,x_0,v_0,r_dot_v,r_dot_v_ij,r_0,abs_r);
	    //printf("a_0[%d][%d]=%f\tadot_0[%d][%d]=%f\n",i,k,a_0[i][k],i,k,adot_0[i][k]);
	  }
	}
	//////////////////////////////////////////////////////////////
#endif

      }else{

	/////////////////////////衝突しない場合/////////////////////////
#if EXECUTION_TIME
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif

	//#pragma omp parallel for private(k) schedule(runtime)
	for(i=1;i<=global_n;++i){
	  if(i!=i_sys){
	    //i_sys以外の粒子は予測子を使う.
	    for(k=1;k<=3;++k){
	      x_c[i][k] = x_p[i][k];
	      v_c[i][k] = v_p[i][k];
	    }
	    r_c[i] = RadiusFromCenter(i,x_p);  //中心からの距離.
	    v2_c[i] = SquareOfVelocity(i,v_p);  //速度の2乗.
	    r_dot_v[i] = InnerProduct(i,x_p,v_p);  //r_i,v_iの内積.
	  }
	}

	Corrector_sys(i_sys,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,dt_);  //修正子. i_sys のみ.
#if EXECUTION_TIME
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Corrector[0] += Cal_time(realtime_start,realtime_end);
	exetime.Corrector[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Corrector[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(ite=1;ite<=ITE_MAX;++ite){  //iteration.
	  Iteration_sys(i_sys,ele,x_p,v_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,dt_);  //i_sysのみ.
	}
#if EXECUTION_TIME
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Iteration[0] += Cal_time(realtime_start,realtime_end);
	exetime.Iteration[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Iteration[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

	////////////////////////////////////////////////////////////////
      }


    }else{
      //t_ene[interval] ですべての粒子をそろえ、エネルギー、軌道要素等計算.

      for(i=1;i<=global_n;++i){

#if DT_LOG
	Dt[i] = t_ene[interval] - t_[i] - t_tmp;
	t_[i] = 0.0;
#else
	Dt[i] = t_ene - t_[i] - t_tmp;
	t_[i] = 0.0;
#endif
	dt_[i] = Dt[i];
      }


#if DT_LOG
      t_tmp = t_ene[interval];
      t_sys = 0.0;
#else
      t_tmp = t_ene;
      t_sys = 0.0;
#endif


#if EXECUTION_TIME
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(i=1;i<=global_n;++i){
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,r_dot_v,Dt);  //予測子. t_eneにおけるすべての粒子を計算.
      }
#if EXECUTION_TIME
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Predictor[0] += Cal_time(realtime_start,realtime_end);
      exetime.Predictor[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Predictor[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(i=1;i<=global_n;++i){
	Corrector_sys(i,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,dt_);
      }
#if EXECUTION_TIME
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Corrector[0] += Cal_time(realtime_start,realtime_end);
      exetime.Corrector[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Corrector[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(ite=1;ite<=ITE_MAX;++ite){  //iteration.
	for(i=1;i<=global_n;++i){
	  Iteration_sys(i,ele,x_p,v_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,dt_);
	}
      }
#if EXECUTION_TIME
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Iteration[0] += Cal_time(realtime_start,realtime_end);
      exetime.Iteration[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Iteration[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if POSI_VELO_FILE
      fpposivelo = fopen(posivelofile,"a");  //位置、速度をファイルへ書き出し.
      if(fpposivelo==NULL){
	printf("posivelofile error\n");
	return -1;
      }

      for(i=1;i<=global_n;i++){
	fprintf(fpposivelo,"%.15e\t%4d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\n",
		(t_sys+t_tmp)/2.0/M_PI,
		i,
		x_c[i][1],
		x_c[i][2],
		x_c[i][3],
		r_c[i],
		sqrt(x_c[i][1]*x_c[i][1]+x_c[i][2]*x_c[i][2]),
		v_c[i][1],
		v_c[i][2],
		v_c[i][3],
		sqrt(v_c[i][1]*v_c[i][1]+v_c[i][2]*v_c[i][2]+v_c[i][3]*v_c[i][3])
		);
      }
      fprintf(fpposivelo,"\n\n");

      fclose(fpposivelo);
#endif


#if ENERGY_FILE

#if INDIRECT_TERM
      CenterOfGravity(x_c,v_c,x_G,v_G,ele);  //重心計算
#endif

#if EXECUTION_TIME
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      E_tot = 0.0;
      E_tot = Calculate_Energy(ele,x_c,
#if INDIRECT_TERM
			       v_c,v_G,
#else
			       v2_c,
#endif
			       r_c);  //エネルギー計算.

      E_tot += dE_correct;  //補正を常にする


      fpEne = fopen(Ene,"a");
      if(fpEne==NULL){
	printf("Ene error\n");
	return -1;
      }
      fprintf(fpEne,"%.15e\t%.15e\t%.15e\t%.15e\t%15e\n",
	      (t_sys+t_tmp)/2.0/M_PI,
	      E_tot,
	      (E_tot-E_tot_0)/fabs(E_tot_0),
	      dE_correct/fabs(E_tot_0),
	      step
	      );
      fclose(fpEne);

      abs_L = AngularMomentum(i,ele,x_c,v_c);
#if EXECUTION_TIME
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
      exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif


#if ORBITALELEMENTS_FILE

#if EXECUTION_TIME
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(i=1;i<=global_n;++i){
	Calculate_OrbitalElements(i,x_c,v_c,ele,r_c,v2_c,r_dot_v);  //軌道要素計算. ファイルへ書き出し.
	sprintf(orbit,"%s%s.dat",
#ifdef DIRECTORY
		STR(DIRECTORY)
#elif DIRECTORY_FILE
		dirname
#endif
		,ele[i].name);
	fporbit = fopen(orbit,"a");
	if(fporbit==NULL){
	  printf("orbit error\n");
	  exit(-1);
	}

	fprintf(fporbit,"%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
		(t_sys+t_tmp)/2.0/M_PI,
		ele[i].ecc,
		ele[i].axis,
		ele[i].u,
		ele[i].inc,
		ele[i].Omega,
		ele[i].omega,
		ele[i].r_h,
		ele[i].radius,
		ele[i].mass
		);

	fclose(fporbit);
      }
#if EXECUTION_TIME
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
      exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif


#if DT_LOG
      interval++;
#else
      t_ene += DT_ENE;
#endif

    }

    /*for(i=1;i<=N;++i){
      printf("%s\tx_c[%d][1]=%f\tx_c[%d][2]=%f\tx_c[%d][3]=%f\n",ele[i].name,i,x_c[i][1],i,x_c[i][2],i,x_c[i][3]);
      printf("%s\tv_c[%d][1]=%f\tv_c[%d][2]=%f\tv_c[%d][3]=%f\n",ele[i].name,i,v_c[i][1],i,v_c[i][2],i,v_c[i][3]);
      }*/



#if FRAGMENTATION

#if EXECUTION_TIME
    gettimeofday(&realtime_start,NULL);
    getrusage(RUSAGE_SELF,&usage_start);
#endif
    mass_tot_all = 0.0;
    for(i=global_n_p+1;i<=global_n;++i){

      //if(t_sys + t_tmp > frag[i].t_frag){
      if(t_[i] + t_tmp > frag[i].t_frag){
	frag[i].t_frag += frag[i].dt_frag;
	frag[i].fragtimes++;


#if EXECUTION_TIME
	gettimeofday(&realtime_start_2,NULL);
	getrusage(RUSAGE_SELF,&usage_start_2);
#endif
	Calculate_OrbitalElements(i,x_c,v_c,ele,r_c,v2_c,r_dot_v);  //軌道要素計算.
#if EXECUTION_TIME
	gettimeofday(&realtime_end_2,NULL);
	getrusage(RUSAGE_SELF,&usage_end_2);
	exetime.Energy[0] += Cal_time(realtime_start_2,realtime_end_2);
	exetime.Energy[1] += Cal_time(usage_start_2.ru_utime,usage_end_2.ru_utime);
	exetime.Energy[2] += Cal_time(usage_start_2.ru_stime,usage_end_2.ru_stime);
#endif


	NeighborSearch(i,ele,frag,x_c);  //近傍(扇形領域に入った)粒子探索.


	//printf("i=%d\tneighbornumber=%d\n",i,frag[i].neighbornumber);
	/*
	  for(j=1;j<=frag[i].neighbornumber;j++){
	  printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
	  }
	*/
	//printf("i=%d\tv_ave=%f\tsigma=%f\tecc=%f\tr_c=%f\tdelta_r=%f\n",i,frag[i].v_ave,frag[i].sigma,ele[i].ecc,r_c[i],frag[i].delta_r);

	MassFlux(i,ele,frag,&para);  //質量フラックス計算.
	frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール.

	if(isnan(frag[i].dt_frag)){
	  //frag[i].dt_frag = dt_[i]*100.0;  //NaN処理.
	  printf("time=%.15e[yr]\tfrag[%d].neighbornumber=%d\n",
		 (t_sys+t_tmp)/2.0/M_PI,
		 i,
		 frag[i].neighbornumber
		 );
	  /*
	    for(j=1;j<=frag[i].neighbornumber;j++){
	    printf("\tneighborlist[%d]=%d\n",j,frag[i].neighborlist[j]);
	    }
	  */
	  printf("i=%d\tv_ave=%f\tsigma=%f\tecc=%f\tr_c=%f\tdelta_r_out=%f\tdelta_r_in=%f\n",
		 i,
		 frag[i].v_ave,
		 frag[i].sigma,
		 ele[i].ecc,
		 r_c[i],
		 frag[i].delta_r_out,
		 frag[i].delta_r_in
		 );
	  printf("axis=%e\tecc=%e\tinc=%e\tu=%e\tOmega=%e\tomega=%e\n",
		 ele[i].axis,
		 ele[i].ecc,
		 ele[i].inc,
		 ele[i].u,
		 ele[i].Omega,
		 ele[i].omega
		 );
	  printf("x=%f\ty=%f\tz=%f\n",
		 x_c[i][1],
		 x_c[i][2],
		 x_c[i][3]
		 );
	  return -1;
	}
	//frag[i].fragtimes = 0;


	ele[i].mass = MassDepletion(i,ele);  //トレーサー質量の減少を計算.

	//printf("F[%d]=%e\tsigma[%d]=%e\tdt_frag[%d]=%e[yr]\tdt_[%d]=%e[yr]\tr_c[%d]=%f\n",i,frag[i].flux,i,frag[i].sigma,i,frag[i].dt_frag/2.0/M_PI,i,dt_[i]/2.0/M_PI,i,r_c[i]);

      }
      mass_tot_all += ele[i].mass;
    }


    //printf("t=%e\tmass_tot=%.15f\tM_TOT=%.15e\n",t_sys,mass_tot,M_TOT);
    //printf("t_sys=%e[yr]\tmass[1]=%e\n",t_sys/2.0/M_PI,ele[1].mass);


    //printf("t=%e[yr]\tfrag calculation time = %f [sec]\n",t_sys/2.0/M_PI,(double)(end-start)/CLOCKS_PER_SEC);


    if(t_sys + t_tmp > t_check){
      fpfrag = fopen(fragfile,"a");  //総質量をファイルへ書き出し.
      if(fpfrag==NULL){
	printf("fragfile error\n");
	return -1;
      }
      fprintf(fpfrag,"%.15e\t%.15f\t%.15f\n",
	      (t_sys+t_tmp)/2.0/M_PI,
	      mass_tot_all,
	      M_TOT);
      fclose(fpfrag);

      fpposimass = fopen(posimassfile,"a");  //位置、質量などをファイルへ書き出し.
      if(fpposimass==NULL){
	printf("posimassfile error\n");
	return -1;
      }
      for(i=1;i<=global_n;i++){
	fprintf(fpposimass,"%.15e\t%04d\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%d\n",
		(t_sys+t_tmp)/2.0/M_PI,
		i,
		x_c[i][1],
		x_c[i][2],
		x_c[i][3],
		r_c[i],
		sqrt(x_c[i][1]*x_c[i][1]+x_c[i][2]*x_c[i][2]),
		ele[i].mass,
		frag[i].delta_r_out,
		frag[i].delta_r_in,
		frag[i].sigma,
		frag[i].n_s,
		frag[i].neighbornumber
		);
      }
      fprintf(fpposimass,"\n\n");
      fclose(fpposimass);

      t_check *= sqrt(sqrt(sqrt(10.0)));  //logでは10を8分割.
    }

#if EXECUTION_TIME
    gettimeofday(&realtime_end,NULL);
    getrusage(RUSAGE_SELF,&usage_end);
    exetime.Fragmentation[0] += Cal_time(realtime_start,realtime_end);
    exetime.Fragmentation[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
    exetime.Fragmentation[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif


#if POSI_VELO_ROT_FILE
    if((i_col == 0) && (j_col == 0)){  //衝突しない場合.
      r_xy[PLANET_NO] = sqrt(x_c[PLANET_NO][1]*x_c[PLANET_NO][1]+x_c[PLANET_NO][2]*x_c[PLANET_NO][2]);
      r_xy[PLANETESIMAL_NO] = sqrt(x_c[PLANETESIMAL_NO][1]*x_c[PLANETESIMAL_NO][1]+x_c[PLANETESIMAL_NO][2]*x_c[PLANETESIMAL_NO][2]);
      theta = atan2(x_c[PLANET_NO][2],x_c[PLANET_NO][1]);


      x_rot[PLANETESIMAL_NO][1] = x_c[PLANETESIMAL_NO][1];
      x_rot[PLANETESIMAL_NO][2] = x_c[PLANETESIMAL_NO][2];
      Rotation_3D_zaxis(PLANETESIMAL_NO,x_rot,-theta);


      x_rot[PLANET_NO][1] = x_c[PLANET_NO][1];
      x_rot[PLANET_NO][2] = x_c[PLANET_NO][2];
      Rotation_3D_zaxis(PLANET_NO,x_rot,-theta);


      fpposi_rot = fopen(posi_rot,"a");
      if(fpposi_rot==NULL){
	printf("posi error\n");
	return -1;
      }
      fprintf(fpposi_rot,"%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
	      (t_sys+t_tmp)/2.0/M_PI,
	      x_rot[PLANETESIMAL_NO][1],
	      x_rot[PLANETESIMAL_NO][2],
	      x_c[PLANETESIMAL_NO][3],
	      r_xy[PLANETESIMAL_NO],
	      atan2(x_rot[PLANETESIMAL_NO][2],x_rot[PLANETESIMAL_NO][1]),
	      ele[PLANETESIMAL_NO].radius,
	      x_rot[PLANET_NO][1],
	      x_rot[PLANET_NO][2],
	      x_c[PLANET_NO][3],
	      r_xy[PLANET_NO],
	      atan2(x_rot[PLANET_NO][2],x_rot[PLANET_NO][1]),
	      ele[PLANET_NO].radius,
	      ele[PLANET_NO].r_h
	      );
      fclose(fpposi_rot);
    }
#endif


#if ELIMINATE_PARTICLE
    for(i=1;i<=global_n;++i){
      //r_c[i]は計算してある
      if(r_c[i]<SOLAR_RADIUS || r_c[i]>SOLAR_SYSTEM_LIMIT){  //太陽に飲みこまれるか系外へ出て行くか.

	printf("i=%d is eliminated\tr[%d]=%e\tt_sys+t_tmp=%.15e[yr]\n",
	       i,
	       i,
	       r_c[i],
	       (t_sys+t_tmp)/2.0/M_PI
	       );

	//iとglobal_n_pを入れ替える.
	ele[0] = ele[i];  //構造体のためSwap_double関数は使えない. 0番目の要素はコピーに使うだけ.
	ele[i] = ele[global_n_p];
	ele[global_n_p] = ele[0];

	Swap_double(&t_[i],&t_[global_n_p]);
	Swap_double(&dt_[i],&dt_[global_n_p]);

	for(k=1;k<=3;++k){
	  Swap_double(&x_0[i][k],&x_0[global_n_p][k]);
	  Swap_double(&x_c[i][k],&x_c[global_n_p][k]);

	  Swap_double(&v_0[i][k],&v_0[global_n_p][k]);
	  Swap_double(&v_c[i][k],&v_c[global_n_p][k]);

	  Swap_double(&a_0[i][k],&a_0[global_n_p][k]);
	  Swap_double(&a[i][k],&a[global_n_p][k]);

	  Swap_double(&adot_0[i][k],&adot_0[global_n_p][k]);
	  Swap_double(&adot[i][k],&adot[global_n_p][k]);

	  Swap_double(&adot2_dt2[i][k],&adot2_dt2[global_n_p][k]);
	  Swap_double(&adot3_dt3[i][k],&adot3_dt3[global_n_p][k]);
	}

#if N_tr != 0
	//global_n_pとglobal_nを入れ替える.
	ele[0] = ele[global_n_p];  //構造体のためSwap_doubleは使えない. 0番目の要素はコピーに使うだけ.
	ele[global_n_p] = ele[global_n];
	ele[global_n] = ele[0];

	Swap_double(&t_[global_n_p],&t_[global_n]);
	Swap_double(&dt_[global_n_p],&dt_[global_n]);

	for(k=1;k<=3;++k){
	  Swap_double(&x_0[global_n_p][k],&x_0[global_n][k]);
	  Swap_double(&x_c[global_n_p][k],&x_c[global_n][k]);

	  Swap_double(&v_0[global_n_p][k],&v_0[global_n][k]);
	  Swap_double(&v_c[global_n_p][k],&v_c[global_n][k]);

	  Swap_double(&a_0[global_n_p][k],&a_0[global_n][k]);
	  Swap_double(&a[global_n_p][k],&a[global_n][k]);

	  Swap_double(&adot_0[global_n_p][k],&adot_0[global_n][k]);
	  Swap_double(&adot[global_n_p][k],&adot[global_n][k]);

	  Swap_double(&adot2_dt2[global_n_p][k],&adot2_dt2[global_n][k]);
	  Swap_double(&adot3_dt3[global_n_p][k],&adot3_dt3[global_n][k]);
	}
#endif

	//global_n_pを1つ減らす.
	global_n_p--;
	global_n = global_n_p + N_tr;
      }
    }
#endif


    if((i_col != 0) && (j_col != 0)){  //衝突した場合.

      for(i=1;i<=global_n;++i){
	t_[i] += Dt[i];  //すべての粒子の時間はt_sysに揃う.

	//printf("t_sys=%.16e\tt_[%d]=%.16e\n",t_sys,i,t_[i]);

	dt_[i] = Timestep_i_0(i,a_0,adot_0);  //すべての粒子のタイムステップ計算.
	//printf("initial dt_[%d]=%e\n",i,dt_[i]);
      }
      i_col = 0;  //リセット
      j_col = 0;  //リセット

    }else if((i_col == 0) && (j_col == 0)){  //衝突しない場合.

      t_[i_sys] += dt_[i_sys];  //i_sys のみ時間更新.

      dt_[i_sys] = Timestep_i_sys(i_sys,a,adot,adot2_dt2,adot3_dt3,dt_);  //i_sys のみタイムステップ計算.

      for(k=1;k<=3;++k){  //i_sys のみ更新.
	x_0[i_sys][k] = x_c[i_sys][k];
	v_0[i_sys][k] = v_c[i_sys][k];
	a_0[i_sys][k] = a[i_sys][k];
	adot_0[i_sys][k] = adot[i_sys][k];
      }

    }else{
      printf("Collision Judgement error\ti_col=%d\tj_col=%d\n",
	     i_col,
	     j_col
	     );
      exit(-1);
    }


    if(fmod(step,STEP_INTERVAL)==0.0){
      if(fmod(step,STEP_INTERVAL*50.0)==0.0){
	printf("#step\t\tNp\tNtr\ti_sys\tdt[i_sys]\t\tt_tmp[yr]\t\tt_sys[yr]\n");
      }
      printf("%e\t%3d\t%6d\t%6d\t%.15e\t%.15e\t%.15e\n",
	     step,
	     global_n_p,
	     global_n-global_n_p,
	     i_sys,
	     dt_[i_sys]/2.0/M_PI,
	     t_tmp/2.0/M_PI,
	     t_sys/2.0/M_PI
	     );

#if EXECUTION_TIME
      gettimeofday(&realtime_end_main,NULL);
      if(Cal_time(realtime_start_main,realtime_end_main)>BREAK_TIME){
	printf("-----\nreal time > %.f [s]\nTimer expired. Ending this program.\n",BREAK_TIME);

	break;  //time loopから抜ける.
      }
#endif
    }


  }  //t loop


  /////////////終了前に位置速度などを記録/////////////
  fptempread = fopen(tempreadfile,"w");
  if(fptempread==NULL){
    printf("tempreadfile error\n");
    return -1;
  }
  fprintf(fptempread,"#t_tmp\tt_sys\tt_ene\tglobal_n_p\tglobal_n\ti_sys\tstep\tE_tot_0\tabs_L_0\tdE_correct\n");
  fprintf(fptempread,"%.15e\t%.15e\t%.15e\t%6d\t%6d\t%6d\t%8e\t%.15e\t%.15e\t%.15e\n",
	  t_tmp,
	  t_sys,
	  t_ene,
	  global_n_p,
	  global_n,
	  i_sys,
	  step,
	  E_tot_0,
	  abs_L_0,
	  dE_correct
	  );
  fprintf(fptempread,"\n\n");
  fprintf(fptempread,"#name\tx[AU]\ty[AU]\tz[AU]\t|r|[AU]\tvx[AU(2pi/yr)]\tvy[AU(2pi/yr)]\tvz[AU(2pi/yr)]\t|v|[AU(2pi/yr)]\tax[AU(2pi/yr)^2]\tay[AU(2pi/yr)^2]\taz[AU(2pi/yr)^2]\tadotx[AU(2pi/yr)^3]\tadoty[AU(2pi/yr)^3]\tadotz[AU(2pi/yr)^3]\tt_i[yr]\tdt_i[yr]\tmass[Msun]\n");
  for(i=1;i<=global_n;++i){
    fprintf(fptempread,"%s\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
	    ele[i].name,
	    x_0[i][1],
	    x_0[i][2],
	    x_0[i][3],
	    r_0[i],
	    v_0[i][1],
	    v_0[i][2],
	    v_0[i][3],
	    sqrt(v2_0[i]),
	    a_0[i][1],
	    a_0[i][2],
	    a_0[i][3],
	    adot_0[i][1],
	    adot_0[i][2],
	    adot_0[i][3],
	    t_[i]/2.0/M_PI,
	    dt_[i]/2.0/M_PI,
	    ele[i].mass
	    );
  }
  fclose(fptempread);
  ////////////////////////////////////////////////


#if ENERGY_FILE
  printf("-----\n");
  printf("dt_[%d]\t= %e\nE_error\t= %.15e\nL_error\t= %.15e\ndE_correct\t= %.15e\n",
	 i_sys,
	 dt_[i_sys],
	 (E_tot-E_tot_0)/fabs(E_tot_0),
	 (abs_L-abs_L_0)/abs_L_0,
	 dE_correct/fabs(E_tot_0)
	 );
#endif

  printf("step\t= %.15e\n",step);


#if DT_LOG
  for(i=0;i<TIME_INTERVAL_MAX;i++){
    printf("t_ene[%d]\t= %e[yr]\n",
	   i,
	   t_ene[i]/2.0/M_PI
	   );
  }
#else
  printf("dt_ene\t= %e[yr]\n",DT_ENE/2.0/M_PI);
#endif


#if EXECUTION_TIME
  printf("-----\n");
  gettimeofday(&realtime_end_main,NULL);
  getrusage(RUSAGE_SELF,&usage_end_main);

  printf("real time\t= %.6f[s]\n",Cal_time(realtime_start_main,realtime_end_main));
  printf("user time\t= %.6f[s]\n",Cal_time(usage_start_main.ru_utime,usage_end_main.ru_utime));
  printf("system time\t= %.6f[s]\n",Cal_time(usage_start_main.ru_stime,usage_end_main.ru_stime));

  Sort_Exetime(realtime_start_main,realtime_end_main);
#endif
  printf("-----\n");
  return 0;
}


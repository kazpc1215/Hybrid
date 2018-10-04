#define EXTERN
#include "hybrid.h"
#include "func.h"


//グローバル変数初期化
int global_n = N_p + N_tr;  //全粒子数.
int global_n_p = N_p;  //原始惑星の数.
FILE *fplog;


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


int main(int argc, char **argv){

#if EXECUTION_TIME
  //時間計測用.
  struct timeval realtime_start_main,realtime_end_main;
  struct rusage usage_start_main,usage_end_main;
#if EXECUTION_TIME_FUNC
  struct timeval realtime_start,realtime_end;
  struct rusage usage_start,usage_end;
#if FRAGMENTATION
  struct timeval realtime_start_2,realtime_end_2;
  struct rusage usage_start_2,usage_end_2;
#endif
#endif

  gettimeofday(&realtime_start_main,NULL);
  getrusage(RUSAGE_SELF,&usage_start_main);
#endif  /*EXECUTION_TIME*/


  struct stat st;  //ファイル存在確認用.


  int i=0,j=0,i_sys=0,k=0,ite=0,i_col=0,j_col=0,n_col=0,myid=0,numprocs=0;
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
  double ecc_p_rms=0.0,inc_p_rms=0.0,ecc_tr_rms=0.0,inc_tr_rms=0.0;


  double t_ene=DT_ENE;


#if INDIRECT_TERM
  double x_G[4]={},v_G[4]={};
#endif


  static struct orbital_elements ele[N_p+N_tr+1]={};


#if FRAGMENTATION
  static struct fragmentation frag[N_p+N_tr+1]={};
  int n_fragcheck=0,n_center=0;
  double t_fragcheck=2.0*M_PI*0.1;
  double sigma_center=0.0,flux_center=0.0,v_ave=0.0,tau_dep_center=0.0;
  double orbital_r_min=0.0,orbital_r_max=0.0;
  double mass_tot_all=0.0,mass_tot_center=0.0;
  struct parameter para;
  FILE *fpfrag;  //初期総質量をファイルへ書き出し.
  char fragfile[200]={};
  FILE *fpposimass;  //初期位置、質量などをファイルへ書き出し.
  char posimassfile[200]={};
  FILE *fptempfragread;
  char tempfragreadfile[200]={};
#endif  /*FRAGMENTATION*/


#ifdef SUBDIRECTORY
  char dirname[200]={};
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
#endif
#endif  /*COLLISION*/


#if ORBITALELEMENTS_FILE
  FILE *fporbit;
  char orbit[200]={};
  FILE *fprms;
  char rmsfile[200]={};
#endif


  FILE *fpinitial;
  char initialfile[200]={};

  FILE *fptempread;
  char tempreadfile[200]={};

  char logfile[200]={};

  char buf[500]={};


  //////////////////////////////ここまで変数宣言//////////////////////////////////


  MPI_Init(&argc,&argv);  //MPI並列の始まり.
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);  //使えるCPUの数.
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);  //myidにそれぞれのCPU番号を書き込む.

  /////////////////////////////ここまでOpenMpとMPIの準備//////////////////////////////


  srand(myid+1);  //乱数の種をmyidで決める.


#ifdef DIRECTORY
  mkdir(STR(DIRECTORY), 0755);  //ディレクトリを作成. 755 = rwxr-xr-x.
#endif  /*DIRECTORY*/


#ifdef SUBDIRECTORY
  sprintf(dirname,"%s%s%02d/",STR(DIRECTORY),STR(SUBDIRECTORY),myid+1);
  mkdir(dirname, 0755);  //子ディレクトリを作成. 755 = rwxr-xr-x.
#endif  /*SUBDIRECTORY*/


#if ENERGY_FILE
  sprintf(Ene,"%sENERGY.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  );
#endif  /*ENERGY_FILE*/


#if POSI_VELO_FILE
  sprintf(posivelofile,"%sPosi_Velo.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  );
#endif  /*POSI_VELO_FILE*/


#if ORBITALELEMENTS_FILE
  sprintf(rmsfile,"%sRMS_Ntr%s.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  ,STR(N_tr)
	  );
#endif  /*ORBITALELEMENTS_FILE*/


#if FRAGMENTATION
  sprintf(fragfile,"%sSigma_dep.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  );


  sprintf(tempfragreadfile,"%stempfragread.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  );

#endif  /*FRAGMENTATION*/


  sprintf(initialfile,"%sinitial.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  );


  sprintf(tempreadfile,"%stempread.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  );


  sprintf(logfile,"%slog.txt",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	  );


  fplog = fopen(logfile,"a");

  fprintf(fplog,"myid = %d\tnumprocs = %d\n",myid,numprocs);

#ifdef _OPENMP
  fprintf(fplog,"OMP_NUM_THREADS: %s\n",getenv("OMP_NUM_THREADS"));
  fprintf(fplog,"threads: %d\n", omp_get_max_threads());

#pragma omp parallel
  {
    fprintf(fplog,". ");
  }
  fprintf(fplog,"\n");
#endif  /*_OPENMP*/


  if(stat(tempreadfile,&st)==0){  //読み込むファイルの存在確認.

    fprintf(fplog,"file: '%s' exists.\n",tempreadfile);

    fptempread = fopen(tempreadfile,"r");
    if(fptempread==NULL){
      fprintf(fplog,"tempreadfile error\n");
      return -1;
    }

    fgets(buf,sizeof(buf),fptempread);  //読み飛ばし.
    fgets(buf,sizeof(buf),fptempread);
    sscanf(buf,"%lf\t%lf\t%lf\t%d\t%d\t%d\t%d\t%lf\t%lf\t%lf\t%lf\n",
	   &t_tmp,
	   &t_sys,
	   &t_ene,
	   &global_n_p,
	   &global_n,
	   &i_sys,
	   &n_col,
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
	fprintf(fplog,"%s: i=%d line is NULL.\n",
	       tempreadfile,
	       i
	       );
      }
    }

    fclose(fptempread);


#if FRAGMENTATION
    if(stat(tempfragreadfile,&st)==0){  //読み込むファイル（破壊計算用）の存在確認.
      fprintf(fplog,"file: '%s' exists.\n",tempfragreadfile);

      fptempfragread = fopen(tempfragreadfile,"r");
      if(fptempfragread==NULL){
	fprintf(fplog,"tempfragreadfile error\n");
	return -1;
      }

      fgets(buf,sizeof(buf),fptempfragread);  //読み飛ばし.
      fgets(buf,sizeof(buf),fptempfragread);
      sscanf(buf,"%*f\t%*f\t%lf\t%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
	     &t_fragcheck,
	     &n_fragcheck,
	     &para.s_1,
	     &para.s_2,
	     &para.s_3,
	     &para.alpha,
	     &para.h_0,
	     &para.Q_D
	     );


      fgets(buf,sizeof(buf),fptempfragread);  //読み飛ばし.
      fgets(buf,sizeof(buf),fptempfragread);  //読み飛ばし.
      fgets(buf,sizeof(buf),fptempfragread);  //読み飛ばし.

      for(i=global_n_p+1;i<=global_n;++i){
	if(fgets(buf,sizeof(buf),fptempfragread)!=NULL){

	  sscanf(buf,"%*d\t%d\t%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
		 &frag[i].fragtimes,
		 &frag[i].neighbornumber,
		 &frag[i].delta_r_out,
		 &frag[i].delta_r_in,
		 &frag[i].sigma,
		 &frag[i].n_s,
		 &frag[i].v_ave,
		 &frag[i].flux,
		 &frag[i].t_frag,
		 &frag[i].dt_frag
		 );

	  frag[i].t_frag = 2.0*M_PI*frag[i].t_frag;
	  frag[i].dt_frag = 2.0*M_PI*frag[i].dt_frag;

	}else{
	  fprintf(fplog,"%s: i=%d line is NULL.\n",
		 tempfragreadfile,
		 i
		 );
	}
      }

      fclose(fptempfragread);
    }
#endif  /*FRAGMENTATION*/

  }else{


    fprintf(fplog,"file: '%s' does not exist. Start the initialization.\n",tempreadfile);

    fprintf(fplog,"-----\n");
    fprintf(fplog,"DIRECTORY\t%s\n",STR(DIRECTORY));
    fprintf(fplog,"N_tr\t%s\n",STR(N_tr));
    fprintf(fplog,"N_p\t%s\n",STR(N_p));
    fprintf(fplog,"RAND_SEED\t%s\n",STR(RAND_SEED));
    fprintf(fplog,"STEP_INTERVAL\t%s\n",STR(STEP_INTERVAL));
    fprintf(fplog,"BREAK_TIME\t%s\n",STR(BREAK_TIME));
    fprintf(fplog,"ENERGY_FILE\t%s\n",STR(ENERGY_FILE));
    fprintf(fplog,"ORBITALELEMENTS_FILE\t%s\n",STR(ORBITALELEMENTS_FILE));
    fprintf(fplog,"POSI_VELO_FILE\t%s\n",STR(POSI_VELO_FILE));
    fprintf(fplog,"POSI_VELO_ROT_FILE\t%s\n",STR(POSI_VELO_ROT_FILE));
    fprintf(fplog,"COLLISION_FILE\t%s\n",STR(COLLISION_FILE));
    fprintf(fplog,"EXECUTION_TIME\t%s\n",STR(EXECUTION_TIME));
    fprintf(fplog,"INTERACTION_ALL\t%s\n",STR(INTERACTION_ALL));
    fprintf(fplog,"INTERACTION_PLANET_TRACER\t%s\n",STR(INTERACTION_PLANET_TRACER));
    fprintf(fplog,"INTERACTION_TEST_PARTICLE\t%s\n",STR(INTERACTION_TEST_PARTICLE));
    fprintf(fplog,"INDIRECT_TERM\t%s\n",STR(INDIRECT_TERM));
    fprintf(fplog,"FRAGMENTATION\t%s\n",STR(FRAGMENTATION));
    fprintf(fplog,"COLLISION\t%s\n",STR(COLLISION));
#if COLLISION
    fprintf(fplog,"COALESCENCE\t%s\n",STR(COALESCENCE));
    fprintf(fplog,"RELOCATE_PARTICLE\t%s\n",STR(RELOCATE_PARTICLE));
#endif
    fprintf(fplog,"EJECTION\t%s\n",STR(EJECTION));
    fprintf(fplog,"ORBITING_SMALL_PARTICLE\t%s\n",STR(ORBITING_SMALL_PARTICLE));
    fprintf(fplog,"ELIMINATE_PARTICLE\t%s\n",STR(ELIMINATE_PARTICLE));
    fprintf(fplog,"ETA\t%s\n",STR(ETA));
    fprintf(fplog,"ITE_MAX\t%s\n",STR(ITE_MAX));
#if ELIMINATE_PARTICLE
    fprintf(fplog,"SOLAR_RADIUS\t%s\n",STR(SOLAR_RADIUS));
    fprintf(fplog,"SOLAR_SYSTEM_LIMIT\t%s\n",STR(SOLAR_SYSTEM_LIMIT));
#endif
    fprintf(fplog,"PLANET_MASS\t%s\n",STR(PLANET_MASS));
    fprintf(fplog,"PLANET_AXIS\t%s\n",STR(PLANET_AXIS));
    fprintf(fplog,"PLANET_ECC\t%s\n",STR(PLANET_ECC));
    fprintf(fplog,"PLANET_INC\t%s\n",STR(PLANET_INC));
    fprintf(fplog,"PLANET_DENSITY\t%s\n",STR(PLANET_DENSITY));
#if N_tr != 0
    fprintf(fplog,"M_TOT\t%s\n",STR(M_TOT));
#if EJECTION
    fprintf(fplog,"PLANET_OF_EJECTION\t%s\n",STR(PLANET_OF_EJECTION));
    fprintf(fplog,"EJECTION_CONE_ANGLE\t%s\n",STR(EJECTION_CONE_ANGLE));
#endif
#if ORBITING_SMALL_PARTICLE
    fprintf(fplog,"ECC_RMS\t%s\n",STR(ECC_RMS));
    fprintf(fplog,"INC_RMS\t%s\n",STR(INC_RMS));
    fprintf(fplog,"DELTA_HILL\t%s\n",STR(DELTA_HILL));
#endif
#if FRAGMENTATION
    fprintf(fplog,"DELTA_R\t%s\n",STR(DELTA_R));
    fprintf(fplog,"DELTA_THETA\t%s\n",STR(DELTA_THETA));
    fprintf(fplog,"NEIGHBOR_MAX\t%s\n",STR(NEIGHBOR_MAX));
    fprintf(fplog,"DEPLETION_TIME_EXPLICIT\t%s\n",STR(DEPLETION_TIME_EXPLICIT));
    fprintf(fplog,"RHO\t%s\n",STR(RHO));
    fprintf(fplog,"EPSILON_FRAG\t%s\n",STR(EPSILON_FRAG));
    fprintf(fplog,"B_FRAG\t%s\n",STR(B_FRAG));
    fprintf(fplog,"Q_0_FRAG\t%s\n",STR(Q_0_FRAG));
    fprintf(fplog,"P_FRAG\t%s\n",STR(P_FRAG));
    fprintf(fplog,"XI\t%s\n",STR(XI));
    fprintf(fplog,"M_MAX\t%s\n",STR(M_MAX));
#endif
#endif  /*N_tr != 0*/
    fprintf(fplog,"T_MAX\t%s\n",STR(T_MAX));
    fprintf(fplog,"DT_LOG\t%s\n",STR(DT_LOG));
    fprintf(fplog,"DT_ENE\t%s\n",STR(DT_ENE));
#if DT_LOG
    fprintf(fplog,"GEOMETRIC_RATIO\t%s\n",STR(GEOMETRIC_RATIO));
#endif
    fprintf(fplog,"-----\n");


    char cat_header[200]={};
    char headerfile[10]="hybrid.h";
    sprintf(cat_header,"cat %s > %sheaderfile.txt",
	    headerfile,
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	    );
    system(cat_header);  //headerファイルをテキストとしてdataに残す


    char cat_main[200]={};
    char mainfile[20]="hybrid_main.c";
    sprintf(cat_main,"cat %s > %smainfile.txt",
	    mainfile,
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	    );
    system(cat_main);  //mainファイルをテキストとしてdataに残す


    ///////////////////////////////ここまで初期処理//////////////////////////////////



#if N_p == 3
    ele[1].axis = PLANET_AXIS / MutualHillRadius_to_SemimajorAxis(DELTA_HILL) ;  //惑星2を中心に相互DELTA_HILLヒル内側へ離す.
    ele[2].axis = PLANET_AXIS;
    ele[3].axis = PLANET_AXIS * MutualHillRadius_to_SemimajorAxis(DELTA_HILL);  //惑星2を中心に相互DELTA_HILLヒル外側へ離す.
#elif N_p == 1
    ele[1].axis = PLANET_AXIS;
#endif

    for(i=1;i<=global_n_p;++i){  //惑星.
      InitialOrbitalElements_Planet(i,ele);  //初期軌道要素.
      InitialCondition(i,x_0,v_0,v2_0,r_dot_v,r_0,ele);  //初期位置、速度計算.
    }


#if N_tr != 0

#if EJECTION
    EjectionOfTracerFromPlanet(x_0,v_0,v2_0,r_dot_v,r_0,ele);
#endif


#if ORBITING_SMALL_PARTICLE
    for(i=global_n_p+1;i<=global_n;++i){  //微惑星.
      InitialOrbitalElements_Tracer(i,x_0,ele);  //初期軌道要素.
      InitialCondition(i,x_0,v_0,v2_0,r_dot_v,r_0,ele);  //初期位置、速度計算.
    }
#endif


#if FRAGMENTATION
    para.alpha = (11.0 + 3.0*P_FRAG)/(6.0 + 3.0*P_FRAG);
    para.s_1 = s_1_FRAG(&para);
    para.s_2 = s_2_FRAG(&para);
    para.s_3 = s_3_FRAG(&para);
    para.h_0 = 0.061*17.3*pow(1.68E6*RHO,-2.0/3.0);  // g/cc = 1.68E6 M_0/AU^3, F(I) = 17.3 として.
    para.Q_D = Q_0_FRAG*1.13E-13*pow(RHO/3.0,0.55)*pow(M_MAX*1.989E12,P_FRAG);  //erg/g = 1.13E-13 AU^2/(yr/2pi)^2 として.

    fprintf(fplog,"alpha=%g\ts_1=%g\ts_2=%g\ts_3=%g\th_0=%g\tQ_D=%g\n",
	   para.alpha,
	   para.s_1,
	   para.s_2,
	   para.s_3,
	   para.h_0,
	   para.Q_D
	   );
#endif

#endif  /*N_tr != 0*/


    ////////////////////////////////////ここまでで初期条件//////////////////////////////////////


#if POSI_VELO_FILE
    //初期位置、速度をファイルへ書き出し.
    fpposivelo= fopen(posivelofile,"w");
    if(fpposivelo==NULL){
      fprintf(fplog,"posivelofile 0 error\n");
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
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	    ,ele[PLANETESIMAL_NO].name);
    fpposi_rot = fopen(posi_rot,"w");
    if(fpposi_rot==NULL){
      fprintf(fplog,"posi_rot error\n");
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

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
    gettimeofday(&realtime_start,NULL);
    getrusage(RUSAGE_SELF,&usage_start);
#endif
    //初期の軌道要素をファイルへ書き出し.
    for(i=1;i<=global_n;++i){
      sprintf(orbit,"%s%s.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	      ,ele[i].name);
      fporbit = fopen(orbit,"w");
      if(fporbit==NULL){
	fprintf(fplog,"orbit 0 error\n");
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


    Calculate_RMS(ele,&ecc_p_rms,&ecc_tr_rms,&inc_p_rms,&inc_tr_rms);  //ecc,incのRMSを計算.

    fprms = fopen(rmsfile,"w");
    if(fprms==NULL){
      fprintf(fplog,"rmsfile 0 error\n");
      exit(-1);
    }

    fprintf(fprms,"#t[yr]\t");
    for(i=1;i<=global_n_p;++i){
      fprintf(fprms,"e_%d\t",i);
    }
    fprintf(fprms,"e_p_rms\te_tr_rms\t");
    for(i=1;i<=global_n_p;++i){
      fprintf(fprms,"i_%d\t",i);
    }
    fprintf(fprms,"i_p_rms\ti_tr_rms\n");

    fprintf(fprms,"%.15e\t",0.0);
    for(i=1;i<=global_n_p;++i){
      fprintf(fprms,"%.15e\t",ele[i].ecc);
    }
    fprintf(fprms,"%.15e\t%.15e\t",ecc_p_rms,ecc_tr_rms);
    for(i=1;i<=global_n_p;++i){
      fprintf(fprms,"%.15e\t",ele[i].inc);
    }
    fprintf(fprms,"%.15e\t%.15e\n",inc_p_rms,inc_tr_rms);

    fclose(fprms);

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
    gettimeofday(&realtime_end,NULL);
    getrusage(RUSAGE_SELF,&usage_end);
    exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
    exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
    exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif  /*ORBITALELEMENTS_FILE*/


#if ENERGY_FILE

#if INDIRECT_TERM
    CenterOfGravity(x_0,v_0,x_G,v_G,ele);  //重心計算.
#endif

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
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
      fprintf(fplog,"Ene 0 error\n");
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
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
    gettimeofday(&realtime_end,NULL);
    getrusage(RUSAGE_SELF,&usage_end);
    exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
    exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
    exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif  /*ENERGY_FILE*/


#if N_tr != 0

#if FRAGMENTATION

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
    gettimeofday(&realtime_start,NULL);
    getrusage(RUSAGE_SELF,&usage_start);
#endif

    n_fragcheck = 0;

    orbital_r_min = PLANET_AXIS / MutualHillRadius_to_SemimajorAxis(0.5*DELTA_HILL);
    orbital_r_max = PLANET_AXIS * MutualHillRadius_to_SemimajorAxis(0.5*DELTA_HILL);

    mass_tot_all = 0.0;
    mass_tot_center = 0.0;
    n_center = 0;
    for(i=global_n_p+1;i<=global_n;++i){

      frag[i].fragtimes = 0;
      NeighborSearch(i,ele,frag,x_0);  //近傍(扇形領域に入った)粒子探索.
      MassFlux(i,ele,frag,&para);  //質量フラックス計算.
      frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール.
      frag[i].t_frag = frag[i].dt_frag;

      if(r_0[i]>orbital_r_min && r_0[i]<orbital_r_max){
	mass_tot_center += ele[i].mass;
	n_center++;
      }
      mass_tot_all += ele[i].mass;
    }

    //統計的計算で破壊タイムスケールの見積もり.
    sigma_center = mass_tot_center / (M_PI * (orbital_r_max*orbital_r_max - orbital_r_min*orbital_r_min));
#if !defined(G) && !defined(M_0)
    v_ave = sqrt(2.0*(ECC_RMS*ECC_RMS + INC_RMS*INC_RMS) / PLANET_AXIS);
    flux_center = - (2.0 - para.alpha)*(2.0 - para.alpha) / cbrt(M_MAX) * sigma_center*sigma_center * sqrt(1.0/PLANET_AXIS/PLANET_AXIS/PLANET_AXIS) * para.h_0 * pow(v_ave*v_ave*0.5/para.Q_D,para.alpha-1.0) * ((- log(EPSILON_FRAG) + 1.0/(2.0-B_FRAG))*para.s_1 + para.s_2 + para.s_3);
#else
    v_ave = sqrt(2.0*(ECC_RMS*ECC_RMS + INC_RMS*INC_RMS) * G*M_0/PLANET_AXIS);
    flux_center = - (2.0 - para.alpha)*(2.0 - para.alpha) / cbrt(M_MAX) * sigma_center*sigma_center * sqrt(G*M_0/PLANET_AXIS/PLANET_AXIS/PLANET_AXIS) * para.h_0 * pow(v_ave*v_ave*0.5/para.Q_D,para.alpha-1.0) * ((- log(EPSILON_FRAG) + 1.0/(2.0-B_FRAG))*para.s_1 + para.s_2 + para.s_3);
#endif
    tau_dep_center = - sigma_center / flux_center;
    fprintf(fplog,"initial mass depletion timescale =%e [yr] (center)\n",tau_dep_center/2.0/M_PI);


    fpfrag = fopen(fragfile,"w");
    if(fpfrag==NULL){
      fprintf(fplog,"fragfile 0 error\n");
      return -1;
    }
    fprintf(fpfrag,"#initial mass depletion timescale = %e [yr] (center)\n",tau_dep_center/2.0/M_PI);
    fprintf(fpfrag,"#mass_tot_all_0 = %.15e\tmass_tot_center_0 = %.15e\tsigma_center_0 = %.15e\tn_center_0 = %d\n",mass_tot_all,mass_tot_center,sigma_center,n_center);
    fprintf(fpfrag,"#t[yr]\tmass_tot_all\tmass_tot_center\tsigma_center\tn_center\n");
    fprintf(fpfrag,"%.15e\t%.15e\t%.15e\t%.15e\t%d\n",
	    0.0,
	    mass_tot_all,
	    mass_tot_center,
	    sigma_center,
	    n_center
	    );
    fclose(fpfrag);


    sprintf(posimassfile,"%sPosi_Mass_%02d.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	    ,n_fragcheck
	    );
    fpposimass= fopen(posimassfile,"w");
    if(fpposimass==NULL){
      fprintf(fplog,"posimassfile 0 error\n");
      return -1;
    }
    fprintf(fpposimass,"#t[yr]\ti\tx\ty\tz\tr_0(3D)\tr_0(2D)\tmass\tdelta_r_out\tdelta_r_in\tsigma\tn_s\tneighbornumber\tdt_frag[yr]\n");
    for(i=1;i<=global_n;i++){
      fprintf(fpposimass,"%.15e\t%4d\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%4d\t%.15e\n",
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
	      frag[i].neighbornumber,
	      frag[i].dt_frag/2.0/M_PI
	      );
    }
    fclose(fpposimass);


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
    gettimeofday(&realtime_end,NULL);
    getrusage(RUSAGE_SELF,&usage_end);
    exetime.Fragmentation[0] += Cal_time(realtime_start,realtime_end);
    exetime.Fragmentation[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
    exetime.Fragmentation[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif  /*FRAGMENTATION*/

#endif  /*N_tr != 0 */



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
	//fprintf(fplog,"a_0[%d][%d]=%f\tadot_0[%d][%d]=%f\n",i,k,a_0[i][k],i,k,adot_0[i][k]);
      }
    }


    for(i=1;i<=global_n;++i){
      //初期のタイムステップ計算.
      dt_[i] = Timestep_i_0(i,a_0,adot_0);
      //fprintf(fplog,"initial dt_[%d]=%e\n",i,dt_[i]);
    }

    /////////////////////////////ここまでで加速度，タイムステップ計算//////////////////////////////


    fpinitial = fopen(initialfile,"w");
    if(fpinitial==NULL){
      fprintf(fplog,"initialfile error\n");
      return -1;
    }
    fprintf(fpinitial,"#t_tmp\tt_sys\tt_ene\tglobal_n_p\tglobal_n\ti_sys\tn_col\tstep\tE_tot_0\tabs_L_0\tdE_correct\n");
    fprintf(fpinitial,"%.15e\t%.15e\t%.15e\t%6d\t%6d\t%6d\t%d\t%8e\t%.15e\t%.15e\t%.15e\n",
	    t_tmp,
	    t_sys,
	    t_ene,
	    global_n_p,
	    global_n,
	    i_sys,
	    n_col,
	    step,
	    E_tot_0,
	    abs_L_0,
	    dE_correct
	    );
    fprintf(fpinitial,"\n\n");
    fprintf(fpinitial,"#name\tx[AU]\ty[AU]\tz[AU]\t|r|[AU]\tvx[AU(2pi/yr)]\tvy[AU(2pi/yr)]\tvz[AU(2pi/yr)]\t|v|[AU(2pi/yr)]\tax[AU(2pi/yr)^2]\tay[AU(2pi/yr)^2]\taz[AU(2pi/yr)^2]\tadotx[AU(2pi/yr)^3]\tadoty[AU(2pi/yr)^3]\tadotz[AU(2pi/yr)^3]\tt_i[yr]\tdt_i[yr]\tmass[Msun]\n");

    for(i=1;i<=global_n;++i){
      fprintf(fpinitial,"%s\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
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
    fclose(fpinitial);

  }


  ////////////////////////////ここまでですべてのファイルを上書きオープン/////////////////////////

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
  gettimeofday(&realtime_start,NULL);
  getrusage(RUSAGE_SELF,&usage_start);
#endif
  for(i=global_n_p+1;i<=global_n;++i){
    Calculate_OrbitalElements(i,x_0,v_0,ele,r_0,v2_0,r_dot_v);
  }
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
  gettimeofday(&realtime_end,NULL);
  getrusage(RUSAGE_SELF,&usage_end);
  exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
  exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
  exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif



  fprintf(fplog,"-----\n");
  fprintf(fplog,"#step\t\tNp\tNtr\ti_sys\tdt[i_sys]\t\tt_tmp[yr]\t\tt_sys[yr]\n");
  fprintf(fplog,"%e\t%3d\t%6d\t%6d\t%.15e\t%.15e\t%.15e\n",
	 step,
	 global_n_p,
	 global_n-global_n_p,
	 i_sys,
	 dt_[i_sys]/2.0/M_PI,
	 t_tmp/2.0/M_PI,
	 t_sys/2.0/M_PI
	 );


  fclose(fplog);  //一旦ファイルを閉じてログを書き出し.
  fplog = fopen(logfile,"a");  //すぐに開く.

  ////////////////////////////////////////////////////////////////////////////////////


  while(t_sys + t_tmp <= T_MAX){

    step+=1.0;

    t_sys = t_[1] + dt_[1];
    i_sys = 1;
    for(i=2;i<=global_n;++i){
      if((t_[i] + dt_[i]) < t_sys){
	t_sys = t_[i] + dt_[i];  //dt_[i]が最小のものを選ぶ.
	i_sys = i;  //i_sysを選ぶ.
      }
    }


    if(t_sys + t_tmp < t_ene){

      //individual timestep

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      //#pragma omp parallel for schedule(runtime)
      for(i=1;i<=global_n;++i){
	Dt[i] = t_sys - t_[i];
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,r_dot_v,Dt);  //予測子 t_sysにおけるすべての粒子を計算.
      }
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
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

	n_col++;

	fprintf(fplog,"collision No.%d\t%e[yr]\ti=%d, j=%d\tr_ij=%.15e\tradius[%d]+radius[%d]=%.15e\n",
	       n_col,
	       (t_sys+t_tmp)/2.0/M_PI,
	       i_col,
	       j_col,
	       abs_r[j_col],
	       i_col,
	       j_col,
	       ele[i_col].radius + ele[j_col].radius
	       );


	//t_sysで揃えるためDt[i]を使う.
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(i=1;i<=global_n;++i){
	  Corrector_sys(i,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,Dt);  //修正子 すべての粒子.
	}
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Corrector[0] += Cal_time(realtime_start,realtime_end);
	exetime.Corrector[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Corrector[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(ite=1;ite<=ITE_MAX;++ite){  //iteration.
	  for(i=1;i<=global_n;++i){
	    Iteration_sys(i,ele,x_p,v_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,Dt);  //すべての粒子.
	  }
	}
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
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


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	//衝突合体する際のエネルギーの補正量を計算
	Energy_Correction(i_col,j_col,x_0,v_0,ele,&dE_heat,&dE_grav,&dE_c,&v_imp);
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
	exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif
#endif  /*COALESCENCE*/


#if COLLISION_FILE
	//衝突時の位置速度をファイルへ書き出し.
	sprintf(collisionfile,"%sCollision_%03d.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
		,n_col
		);
	fpcollision= fopen(collisionfile,"w");
	if(fpcollision==NULL){
	  fprintf(fplog,"collisionfile error\n");
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
#endif  /*COLLISION_FILE*/


#if COALESCENCE
	Coalescence(i_col,j_col,x_0,v_0,ele
#if FRAGMENTATION
		    ,frag
#endif
		    );  //合体後の操作.
#endif


#if RELOCATE_PARTICLE
	if(j_col>global_n_p){  //惑星i_colに衝突後に，その周りに粒子を再配置.
	  //InitialOrbitalElements_Tracer(j_col,x_0,ele);
          ele[j_col].u = rand_func()*2.0*M_PI;
          ele[j_col].omega = rand_func()*2.0*M_PI;
          ele[j_col].Omega = rand_func()*2.0*M_PI;
          InitialCondition(j_col,x_0,v_0,v2_0,r_dot_v,r_0,ele);
	}
#endif


	//以下、すべての粒子の加速度などを再計算.
	for(i=1;i<=global_n;++i){
	  r_0[i] = RadiusFromCenter(i,x_0);  //中心星からの距離.
	  v2_0[i] = SquareOfVelocity(i,v_0);  //速度の2乗.
	  r_dot_v[i] = InnerProduct(i,x_0,v_0);  //r_i,v_iの内積.
	}

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(i=1;i<=global_n;++i){
	  Calculate_OrbitalElements(i,x_0,v_0,ele,r_0,v2_0,r_dot_v);
	}
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
	exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if ENERGY_FILE

#if INDIRECT_TERM
	CenterOfGravity(x_0,v_0,x_G,v_G,ele);  //重心計算.
	//fprintf(fplog,"x_G=%.15e\ty_G=%.15e\tz_G=%.15e\tvx_G=%.15e\tvy_G=%.15e\tvz_G=%.15e\n",x_G[1],x_G[2],x_G[3],v_G[1],v_G[2],v_G[3]);
#endif

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
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
	  fprintf(fplog,"Ene error\n");
	  return -1;
	}
	fprintf(fpEne,"#collision No.%d occur\t%e[yr]\n",
		n_col,
		(t_sys+t_tmp)/2.0/M_PI
		);
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

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
	exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif  /*ENERGY_FILE*/


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
	    //fprintf(fplog,"a_0[%d][%d]=%f\tadot_0[%d][%d]=%f\n",i,k,a_0[i][k],i,k,adot_0[i][k]);
	  }
	}
	//////////////////////////////////////////////////////////////
#endif  /*COLLISION*/

      }else{

	/////////////////////////衝突しない場合/////////////////////////
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
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
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Corrector[0] += Cal_time(realtime_start,realtime_end);
	exetime.Corrector[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Corrector[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_start,NULL);
	getrusage(RUSAGE_SELF,&usage_start);
#endif
	for(ite=1;ite<=ITE_MAX;++ite){  //iteration.
	  Iteration_sys(i_sys,ele,x_p,v_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,dt_);  //i_sysのみ.
	}
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_end,NULL);
	getrusage(RUSAGE_SELF,&usage_end);
	exetime.Iteration[0] += Cal_time(realtime_start,realtime_end);
	exetime.Iteration[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
	exetime.Iteration[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

	////////////////////////////////////////////////////////////////
      }


    }else{
      //t_ene ですべての粒子をそろえ、エネルギー、軌道要素等計算.

      for(i=1;i<=global_n;++i){

	Dt[i] = t_ene - t_[i] - t_tmp;
	t_[i] = 0.0;

	dt_[i] = Dt[i];
      }


      t_tmp = t_ene;
      t_sys = 0.0;


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(i=1;i<=global_n;++i){
	Predictor(i,x_0,v_0,a_0,adot_0,x_p,v_p,r_p,v2_p,r_dot_v,Dt);  //予測子. t_eneにおけるすべての粒子を計算.
      }
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Predictor[0] += Cal_time(realtime_start,realtime_end);
      exetime.Predictor[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Predictor[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(i=1;i<=global_n;++i){
	Corrector_sys(i,ele,x_p,v_p,r_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,dt_);
      }
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Corrector[0] += Cal_time(realtime_start,realtime_end);
      exetime.Corrector[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Corrector[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(ite=1;ite<=ITE_MAX;++ite){  //iteration.
	for(i=1;i<=global_n;++i){
	  Iteration_sys(i,ele,x_p,v_p,x_c,v_c,r_c,v2_c,r_dot_v,a_0,adot_0,a,adot,adot2_dt2,adot3_dt3,dt_);
	}
      }
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Iteration[0] += Cal_time(realtime_start,realtime_end);
      exetime.Iteration[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Iteration[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif


#if POSI_VELO_FILE
      fpposivelo = fopen(posivelofile,"a");  //位置、速度をファイルへ書き出し.
      if(fpposivelo==NULL){
	fprintf(fplog,"posivelofile error\n");
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

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
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
	fprintf(fplog,"Ene error\n");
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
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Energy[0] += Cal_time(realtime_start,realtime_end);
      exetime.Energy[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Energy[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif


#if ORBITALELEMENTS_FILE

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_start,NULL);
      getrusage(RUSAGE_SELF,&usage_start);
#endif
      for(i=1;i<=global_n;++i){
	Calculate_OrbitalElements(i,x_c,v_c,ele,r_c,v2_c,r_dot_v);  //軌道要素計算. ファイルへ書き出し.
	sprintf(orbit,"%s%s.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
		,ele[i].name);
	fporbit = fopen(orbit,"a");
	if(fporbit==NULL){
	  fprintf(fplog,"orbit error\n");
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


      Calculate_RMS(ele,&ecc_p_rms,&ecc_tr_rms,&inc_p_rms,&inc_tr_rms);  //ecc,incのRMSを計算.

      fprms = fopen(rmsfile,"a");
      if(fprms==NULL){
	fprintf(fplog,"rmsfile error\n");
	exit(-1);
      }

      fprintf(fprms,"%.15e\t",(t_sys+t_tmp)/2.0/M_PI);
      for(i=1;i<=global_n_p;++i){
	fprintf(fprms,"%.15e\t",ele[i].ecc);
      }
      fprintf(fprms,"%.15e\t%.15e\t",ecc_p_rms,ecc_tr_rms);
      for(i=1;i<=global_n_p;++i){
	fprintf(fprms,"%.15e\t",ele[i].inc);
      }
      fprintf(fprms,"%.15e\t%.15e\n",inc_p_rms,inc_tr_rms);

      fclose(fprms);

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
      gettimeofday(&realtime_end,NULL);
      getrusage(RUSAGE_SELF,&usage_end);
      exetime.Orbital_Elements[0] += Cal_time(realtime_start,realtime_end);
      exetime.Orbital_Elements[1] += Cal_time(usage_start.ru_utime,usage_end.ru_utime);
      exetime.Orbital_Elements[2] += Cal_time(usage_start.ru_stime,usage_end.ru_stime);
#endif

#endif  /*ORBITALELEMENTS_FILE*/


#if DT_LOG
      fptempread = fopen(tempreadfile,"w");
      if(fptempread==NULL){
	fprintf(fplog,"tempreadfile error\n");
	return -1;
      }
      fprintf(fptempread,"#t_tmp\tt_sys\tt_ene\tglobal_n_p\tglobal_n\ti_sys\tn_col\tstep\tE_tot_0\tabs_L_0\tdE_correct\n");
      fprintf(fptempread,"%.15e\t%.15e\t%.15e\t%6d\t%6d\t%6d\t%d\t%8e\t%.15e\t%.15e\t%.15e\n",
	      t_tmp,
	      t_sys,
	      t_ene,
	      global_n_p,
	      global_n,
	      i_sys,
	      n_col,
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
		x_c[i][1],
		x_c[i][2],
		x_c[i][3],
		r_c[i],
		v_c[i][1],
		v_c[i][2],
		v_c[i][3],
		sqrt(v2_c[i]),
		a[i][1],
		a[i][2],
		a[i][3],
		adot[i][1],
		adot[i][2],
		adot[i][3],
		t_[i]/2.0/M_PI,
		dt_[i]/2.0/M_PI,
		ele[i].mass
		);
      }
      fclose(fptempread);


#if FRAGMENTATION
      fptempfragread = fopen(tempfragreadfile,"w");
      if(fptempfragread==NULL){
	fprintf(fplog,"tempfragreadfile error\n");
	return -1;
      }
      fprintf(fptempfragread,"#t_tmp[yr]\tt_sys[yr]\tn_fragcheck\tt_fragcheck\ts_1\ts_2\ts_3\talpha\th_0\tQ_D\n");
      fprintf(fptempfragread,"%e\t%e\t%.15e\t%d\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
	      t_tmp/2.0/M_PI,
	      t_sys/2.0/M_PI,
	      t_fragcheck,
	      n_fragcheck,
	      para.s_1,
	      para.s_2,
	      para.s_3,
	      para.alpha,
	      para.h_0,
	      para.Q_D
	      );
      fprintf(fptempfragread,"\n\n");
      fprintf(fptempfragread,"#i\tfragtimes\tneighbornumber\tdelta_r_out\tdelta_r_in\tsigma\tn_s\tv_ave\tflux\tt_frag[yr]\tdt_frag[yr]\n");

      for(i=global_n_p+1;i<=global_n;++i){
	fprintf(fptempfragread,"%d\t%d\t%d\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
		i,
		frag[i].fragtimes,
		frag[i].neighbornumber,
		frag[i].delta_r_out,
		frag[i].delta_r_in,
		frag[i].sigma,
		frag[i].n_s,
		frag[i].v_ave,
		frag[i].flux,
		frag[i].t_frag/2.0/M_PI,
		frag[i].dt_frag/2.0/M_PI
		);
      }
      fclose(fptempfragread);
#endif  /*FRAGMENTATION*/

#endif  /*DT_LOG*/


#if DT_LOG
      t_ene *= GEOMETRIC_RATIO;
#else
      t_ene += DT_ENE;
#endif

    }


#if FRAGMENTATION

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
    gettimeofday(&realtime_start,NULL);
    getrusage(RUSAGE_SELF,&usage_start);
#endif

    for(i=global_n_p+1;i<=global_n;++i){

      //if(t_sys + t_tmp > frag[i].t_frag){
      if(t_[i] + t_tmp > frag[i].t_frag){
	frag[i].t_frag += frag[i].dt_frag;
	frag[i].fragtimes++;


#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_start_2,NULL);
	getrusage(RUSAGE_SELF,&usage_start_2);
#endif
	Calculate_OrbitalElements(i,x_c,v_c,ele,r_c,v2_c,r_dot_v);  //軌道要素計算.
#if EXECUTION_TIME && EXECUTION_TIME_FUNC
	gettimeofday(&realtime_end_2,NULL);
	getrusage(RUSAGE_SELF,&usage_end_2);
	exetime.Energy[0] += Cal_time(realtime_start_2,realtime_end_2);
	exetime.Energy[1] += Cal_time(usage_start_2.ru_utime,usage_end_2.ru_utime);
	exetime.Energy[2] += Cal_time(usage_start_2.ru_stime,usage_end_2.ru_stime);
#endif


	NeighborSearch(i,ele,frag,x_c);  //近傍(扇形領域に入った)粒子探索.

	MassFlux(i,ele,frag,&para);  //質量フラックス計算.
	frag[i].dt_frag = Depletion_Time(i,frag);  //統計的計算のタイムスケール.

	if(isnan(frag[i].dt_frag)){
	  fprintf(fplog,"time=%.15e[yr]\tfrag[%d].neighbornumber=%d\n",
		 (t_sys+t_tmp)/2.0/M_PI,
		 i,
		 frag[i].neighbornumber
		 );
	  fprintf(fplog,"i=%d\tv_ave=%f\tsigma=%f\tecc=%f\tr_c=%f\tdelta_r_out=%f\tdelta_r_in=%f\n",
		 i,
		 frag[i].v_ave,
		 frag[i].sigma,
		 ele[i].ecc,
		 r_c[i],
		 frag[i].delta_r_out,
		 frag[i].delta_r_in
		 );
	  fprintf(fplog,"axis=%e\tecc=%e\tinc=%e\tu=%e\tOmega=%e\tomega=%e\n",
		 ele[i].axis,
		 ele[i].ecc,
		 ele[i].inc,
		 ele[i].u,
		 ele[i].Omega,
		 ele[i].omega
		 );
	  fprintf(fplog,"x=%f\ty=%f\tz=%f\n",
		 x_c[i][1],
		 x_c[i][2],
		 x_c[i][3]
		 );
	  return -1;
	}


	ele[i].mass = MassDepletion(i,ele);  //トレーサー質量の減少を計算.
      }
    }


    if(t_sys + t_tmp > t_fragcheck){
      n_fragcheck++;

      orbital_r_min = PLANET_AXIS / MutualHillRadius_to_SemimajorAxis(0.5*DELTA_HILL);
      orbital_r_max = PLANET_AXIS * MutualHillRadius_to_SemimajorAxis(0.5*DELTA_HILL);

      mass_tot_all = 0.0;
      mass_tot_center = 0.0;
      n_center = 0;
      for(i=global_n_p+1;i<=global_n;++i){
	if(r_c[i]>orbital_r_min && r_c[i]<orbital_r_max){
	  mass_tot_center += ele[i].mass;
	  n_center++;
	}
	mass_tot_all += ele[i].mass;
      }

      sigma_center = mass_tot_center / (M_PI * (orbital_r_max*orbital_r_max - orbital_r_min*orbital_r_min));

      fpfrag = fopen(fragfile,"a");  //総質量をファイルへ書き出し.
      if(fpfrag==NULL){
	fprintf(fplog,"fragfile error\n");
	return -1;
      }
      fprintf(fpfrag,"%.15e\t%.15e\t%.15e\t%.15e\t%d\n",
	      (t_sys+t_tmp)/2.0/M_PI,
	      mass_tot_all,
	      mass_tot_center,
	      sigma_center,
	      n_center
	      );
      fclose(fpfrag);


      sprintf(posimassfile,"%sPosi_Mass_%02d.dat",
#ifdef SUBDIRECTORY
	  dirname
#else
	  STR(DIRECTORY)
#endif
	      ,n_fragcheck
	      );
      fpposimass = fopen(posimassfile,"w");  //位置、質量などをファイルへ書き出し.
      if(fpposimass==NULL){
	fprintf(fplog,"posimassfile error\n");
	return -1;
      }
      fprintf(fpposimass,"#t[yr]\ti\tx\ty\tz\tr_0(3D)\tr_0(2D)\tmass\tdelta_r_out\tdelta_r_in\tsigma\tn_s\tneighbornumber\tdt_frag[yr]\n");
      for(i=1;i<=global_n;i++){
	fprintf(fpposimass,"%.15e\t%4d\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%4d\t%.15e\n",
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
		frag[i].neighbornumber,
		frag[i].dt_frag/2.0/M_PI
		);
      }
      fclose(fpposimass);


      t_fragcheck *= sqrt(sqrt(sqrt(10.0)));  //logでは10を8分割.
    }

#if EXECUTION_TIME && EXECUTION_TIME_FUNC
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
	fprintf(fplog,"posi error\n");
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

	fprintf(fplog,"i=%d is eliminated\tr[%d]=%e\tt_sys+t_tmp=%.15e[yr]\n",
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

	//fprintf(fplog,"t_sys=%.16e\tt_[%d]=%.16e\n",t_sys,i,t_[i]);

	dt_[i] = Timestep_i_0(i,a_0,adot_0);  //すべての粒子のタイムステップ計算.
	//fprintf(fplog,"initial dt_[%d]=%e\n",i,dt_[i]);
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
      fprintf(fplog,"Collision Judgement error\ti_col=%d\tj_col=%d\n",
	     i_col,
	     j_col
	     );
      exit(-1);
    }


    if(fmod(step,STEP_INTERVAL)==0.0){
      if(fmod(step,STEP_INTERVAL*50.0)==0.0){
	fprintf(fplog,"#step\t\tNp\tNtr\ti_sys\tdt[i_sys]\t\tt_tmp[yr]\t\tt_sys[yr]\n");
      }
      fprintf(fplog,"%e\t%3d\t%6d\t%6d\t%.15e\t%.15e\t%.15e\n",
	     step,
	     global_n_p,
	     global_n-global_n_p,
	     i_sys,
	     dt_[i_sys]/2.0/M_PI,
	     t_tmp/2.0/M_PI,
	     t_sys/2.0/M_PI
	     );

      fclose(fplog);  //一旦ファイルを閉じてログを書き出し.
      fplog = fopen(logfile,"a");  //すぐに開く.

#if EXECUTION_TIME
      gettimeofday(&realtime_end_main,NULL);
      if(Cal_time(realtime_start_main,realtime_end_main)>BREAK_TIME){
	fprintf(fplog,"-----\nreal time > %.f [s]\nTimer expired. Ending this program.\n",BREAK_TIME);

	break;  //time loopから抜ける.
      }
#endif
    }


  }  //t loop


  /////////////終了前に位置速度などを記録/////////////
  fptempread = fopen(tempreadfile,"w");
  if(fptempread==NULL){
    fprintf(fplog,"tempreadfile error\n");
    return -1;
  }
  fprintf(fptempread,"#t_tmp\tt_sys\tt_ene\tglobal_n_p\tglobal_n\ti_sys\tn_col\tstep\tE_tot_0\tabs_L_0\tdE_correct\n");
  fprintf(fptempread,"%.15e\t%.15e\t%.15e\t%6d\t%6d\t%6d\t%6d\t%8e\t%.15e\t%.15e\t%.15e\n",
	  t_tmp,
	  t_sys,
	  t_ene,
	  global_n_p,
	  global_n,
	  i_sys,
	  n_col,
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
	    x_c[i][1],
	    x_c[i][2],
	    x_c[i][3],
	    r_c[i],
	    v_c[i][1],
	    v_c[i][2],
	    v_c[i][3],
	    sqrt(v2_c[i]),
	    a[i][1],
	    a[i][2],
	    a[i][3],
	    adot[i][1],
	    adot[i][2],
	    adot[i][3],
	    t_[i]/2.0/M_PI,
	    dt_[i]/2.0/M_PI,
	    ele[i].mass
	    );
  }
  fclose(fptempread);


#if FRAGMENTATION
  fptempfragread = fopen(tempfragreadfile,"w");
  if(fptempfragread==NULL){
    fprintf(fplog,"tempfragreadfile error\n");
    return -1;
  }
  fprintf(fptempfragread,"#t_tmp[yr]\tt_sys[yr]\tt_fragcheck\tn_fragcheck\ts_1\ts_2\ts_3\talpha\th_0\tQ_D\n");
  fprintf(fptempfragread,"%e\t%e\t%.15e\t%d\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
	  t_tmp/2.0/M_PI,
	  t_sys/2.0/M_PI,
	  t_fragcheck,
	  n_fragcheck,
	  para.s_1,
	  para.s_2,
	  para.s_3,
	  para.alpha,
	  para.h_0,
	  para.Q_D
	  );
  fprintf(fptempfragread,"\n\n");
  fprintf(fptempfragread,"#i\tfragtimes\tneighbornumber\tdelta_r_out\tdelta_r_in\tsigma\tn_s\tv_ave\tflux\tt_frag[yr]\tdt_frag[yr]\n");

  for(i=global_n_p+1;i<=global_n;++i){
    fprintf(fptempfragread,"%d\t%d\t%d\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",
	    i,
	    frag[i].fragtimes,
	    frag[i].neighbornumber,
	    frag[i].delta_r_out,
	    frag[i].delta_r_in,
	    frag[i].sigma,
	    frag[i].n_s,
	    frag[i].v_ave,
	    frag[i].flux,
	    frag[i].t_frag/2.0/M_PI,
	    frag[i].dt_frag/2.0/M_PI
	    );
  }
  fclose(fptempfragread);
#endif /*FRAGMENTATION*/
  ////////////////////////////////////////////////


#if ENERGY_FILE
  fprintf(fplog,"-----\n");
  fprintf(fplog,"dt_[%d]\t= %e\nE_error\t= %.15e\nL_error\t= %.15e\ndE_correct\t= %.15e\n",
	 i_sys,
	 dt_[i_sys],
	 (E_tot-E_tot_0)/fabs(E_tot_0),
	 (abs_L-abs_L_0)/abs_L_0,
	 dE_correct/fabs(E_tot_0)
	 );
#endif

  fprintf(fplog,"step\t= %.15e\n",step);


#if DT_LOG
  fprintf(fplog,"dt_ene\t= %e[yr]\ngeometric ratio\t= %s\n",DT_ENE/2.0/M_PI,STR(GEOMETRIC_RATIO));
#else
  fprintf(fplog,"dt_ene\t= %e[yr]\n",DT_ENE/2.0/M_PI);
#endif


#if EXECUTION_TIME
  fprintf(fplog,"-----\n");
  gettimeofday(&realtime_end_main,NULL);
  getrusage(RUSAGE_SELF,&usage_end_main);

  fprintf(fplog,"real time\t= %.6f[s]\n",Cal_time(realtime_start_main,realtime_end_main));
  fprintf(fplog,"user time\t= %.6f[s]\n",Cal_time(usage_start_main.ru_utime,usage_end_main.ru_utime));
  fprintf(fplog,"system time\t= %.6f[s]\n",Cal_time(usage_start_main.ru_stime,usage_end_main.ru_stime));

  Sort_Exetime(realtime_start_main,realtime_end_main);
#endif
  fprintf(fplog,"-----\n");

  fclose(fplog);

  MPI_Finalize();  //MPI並列の終わり.

  return 0;
}


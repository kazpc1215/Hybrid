#ifndef INCLUDED_hybrid_H  //include-guard
#define INCLUDED_hybrid_H  //include-guard


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>


#define DIRECTORY ../data/test/  //ファイル保存用のディレクトリ
#define _STR(str) #str
#define STR(str) _STR(str)


#ifndef EXTERN
#define EXTERN extern
#endif


//////////////////////////////////////////////////
#define N_tr 0  //初期のトレーサーの数
#define N_p 10  //初期の原始惑星の数

EXTERN int global_n;  //グローバル変数
EXTERN int global_n_p;  //グローバル変数
//////////////////////////////////////////////////


/*0以外のときファイル作成*/
//////////////////////////////////////////////////
#define ENERGY_FILE 1
#define ORBITALELEMENTS_FILE 1
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define INTERACTION_ALL 0  //全粒子同士の重力相互作用  //どちらかひとつ
#define INTERACTION_ONLY_PLANET_TRACER 1  //惑星とトレーサー間の重力相互作用のみ  //どちらかひとつ
#define FRAGMENTATION 0  //近傍粒子探索と質量フラックス計算
//////////////////////////////////////////////////




//////////////////////////////////////////////////
#define PLANET_MASS 3.0E-7  //5.9723E27 [g] / 1.989E33 [g] /10
#define PLANET_ECC 0.01
#define PLANET_INC 0.005
#define PLANET_DENSITY 3.0  //[g/cc]
#define PLANET_RADIUS cbrt(3.0/4.0/M_PI*PLANET_MASS*1.989E33/PLANET_DENSITY)/1.496E13
#define PLANET_NO 1

/*
Earth Mean Orbital Elements (J2000)

Semimajor axis (AU)                  1.00000011  
Orbital eccentricity                 0.01671022   
Orbital inclination (deg)            0.00005  
Longitude of ascending node (deg)  -11.26064  
Longitude of perihelion (deg)      102.94719  
Mean Longitude (deg)               100.46435
*/
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define M_TOT 3.0E-7  //0.1M_E  //破片の総質量
#define EJECTION_VELOCITY 1.0*sqrt(2.0*G*PLANET_MASS/PLANET_RADIUS)  //脱出速度の1.0倍
#define EJECTION_CONE_ANGLE M_PI/180.0*30.0  //30度
//////////////////////////////////////////////////






//////////////////////////////////////////////////
#define RAND_SEED 1  //乱数の種
//////////////////////////////////////////////////

//////////////////////////////////////////////////
#define DELTA_R 0.010  //近傍粒子探索用
#define DELTA_THETA 0.5*M_PI  //近傍粒子探索用
//#define DELTA_THETA M_PI  //近傍粒子探索用
//////////////////////////////////////////////////



//////////////////////////////////////////////////
#define T_MAX (2.0*M_PI*1.0E4)  //1E8yr  全計算時間
//#define TIME_INTERVAL 2.0*M_PI*1.0E0,2.0*M_PI*1.0E1,2.0*M_PI*1.0E2,2.0*M_PI*1.0E3,2.0*M_PI*1.0E4,2.0*M_PI*1.0E5,2.0*M_PI*1.0E6,2.0*M_PI*1.0E7,T_MAX  //t_ene配列の中身
#define TIME_INTERVAL 2.0*M_PI*1.0E0,2.0*M_PI*1.0E1,2.0*M_PI*1.0E2,2.0*M_PI*1.0E3,T_MAX  //t_ene配列の中身
#define TIME_INTERVAL_MAX 5 //t_ene配列の要素数
//////////////////////////////////////////////////



//////////////////////////////////////////////////
#define G 1.0  //重力定数
#define M_0 1.0  //主星の質量
#define EPSILON 0.0  //ソフトニングパラメーター
#define ETA 0.05  //刻み幅調整
#define ITE_MAX 3  //イテレーション回数
//////////////////////////////////////////////////



//////////////////////////////////////////////////
//#define INNER_AXIS 0.95  //トレーサーの長軸半径　下限
//#define OUTER_AXIS 1.05  //トレーサーの長軸半径　上限
//#define ECC_RMS 0.01  //トレーサーの離心率の二乗平均平方根  //Rayleigh分布
//#define ECC_RMS 0.001  //トレーサーの離心率の二乗平均平方根  //Rayleigh分布
//#define INC_RMS 0.005  //トレーサーの軌道傾斜角の二乗平均平方根  //Rayleigh分布
//#define INC_RMS 0.0005  //トレーサーの軌道傾斜角の二乗平均平方根  //Rayleigh分布
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define NEIGHBOR_MAX N_tr  //近傍粒子リスト配列の最大値
//////////////////////////////////////////////////



/*破壊用*/
//////////////////////////////////////////////////
#define DEPLETION_TIME_EXPLICIT 0  //1のとき、質量減少タイムスケールの計算でexplicit *(1-XI)を使う 0のときはimplicit /(1+XI)を使う
#define RHO 3.0  // [g/cc]  微惑星の物質密度
#define EPSILON_FRAG 0.2
#define B_FRAG (5.0/3.0)
#define Q_0_FRAG 9.5E8 // [erg/g]  Q_D = Q_0*(rho/3[g/cc])^0.55*(m/10^21[g])^p
#define P_FRAG 0.453
#define XI 0.01 //統計的計算のタイムステップがタイムスケールの"XI"倍
#define M_MAX 5.00E-15  //微惑星質量　1E19 g
//#define M_MAX 5.028E-16  //微惑星質量　1E18 g
//////////////////////////////////////////////////




struct orbital_elements{
  char name[30];  //名前（番号）
  double ecc;  //離心率
  double axis;  //軌道長半径
  double u;  //離心近点離角
  double inc;  //軌道傾斜角
  double Omega;  //昇交点経度
  double omega;  //近点引数
  double r_h;  //ヒル半径
  double radius;  //物理半径
  double mass;  //質量
  int orinum;  //初期の番号
};



struct fragmentation{
  int neighborlist[NEIGHBOR_MAX+1];  //近傍粒子リスト
  int neighbornumber;
  //double delta_r;
  double delta_r_out;  //外側
  double delta_r_in;  //内側
  double sigma;  //表面密度
  double n_s;  //表面数密度
  double v_ave;  //領域内での平均速度
  double flux;  //質量フラックス
  double dt_frag;  //統計的計算の粒子ごとのタイムステップ
  double t_frag;  //統計的計算の粒子ごとの時間
  int fragtimes;  //何回統計的計算をしているか
};


  
struct parameter{
  double s_1;
  double s_2;
  double s_3;
  double alpha;
  double h_0;
  double Q_D;
};

double AngularMomentum(int i,struct orbital_elements ele[],double x_0[][4],double v_0[][4]);

double InnerProduct(int i,double x_0[][4],double v_0[][4]);

double RadiusFromCenter(int i,double x_0[][4]);

double SquareOfVelocity(int i,double v_0[][4]);

double Timestep_i_0(int i,double a_0[][4],double adot[][4],double abs_a[],double abs_adot[]);

double Timestep_i_sys(int i_sys,double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_a[],double abs_adot[],double abs_adot2[],double abs_adot3[],double dt_[]);

double SquareOfRelativeDistance(int i,int j,double x_0[][4]);

double SquareOfRelativeVelocity(int i,int j,double v_0[][4]);

double RelativeInnerProduct(int i,int j,double x_0[][4],double v_0[][4]);

double Acceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double abs_r2[]);

double dAcceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v_ij[],double abs_r2[]);

double External_Acceleration(int i,int k,double x_0[][4],double r_0[]);

double External_dAcceleration(int i,int k,double x_0[][4],double v_0[][4],double r_0[],double r_dot_v[]);

double All_Acceleration(int i,int k,struct orbital_elements ele[],double x_0[][4],double r_0[],double abs_r2[]);

double All_dAcceleration(int i,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v[],double r_dot_v_ij[],double r_0[],double abs_r2[]);

double RotatingCoordinate_X(struct orbital_elements ele[],double x_0[][4],double t_sys);

double RotatingCoordinate_Y(struct orbital_elements ele[],double x_0[][4],double t_sys);

int Calculate_OrbitalElements(int i,double x_c[][4],double v_c[][4],struct orbital_elements ele[],double P[][4],double Q[][4],double r_c[],double v2_c[],double r_dot_v[]);

double Calculate_P(int i,int k,struct orbital_elements ele[]);

double Calculate_Q(int i,int k,struct orbital_elements ele[]);

double Calculate_Energy(struct orbital_elements ele[],double x_c[][4],double v2_c[],double r_c[],double abs_r[],double abs_r2[]);

void InitialCondition(int i,double P[][4],double Q[][4],double x_0[][4],double v_0[][4],double v2_0[],double r_dot_v[],double r_0[],struct orbital_elements ele[]);

void Predictor(int i,double x_0[][4],double v_0[][4],double a_0[][4],double adot_0[][4],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double Dt[]);

void Corrector_sys(int i_sys,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double r_p[],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_r[],double abs_r2[],double abs_v[],double abs_v2[],double r_dot_v_ij[],double r_dot_v[],double dt_[]);

void Iteration_sys(int i_sys,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_r[],double abs_r2[],double abs_v[],double abs_v2[],double r_dot_v_ij[],double r_dot_v[],double dt_[]);

int Collision_Judgement(struct orbital_elements ele[],double x_p[][4],double abs_r[],double abs_r2[],int *i_col, int *j_col);

void NeighborSearch(int i,struct orbital_elements ele[],struct fragmentation frag[],double x_0[][4]);

double RandomVelocity(int i,int j,struct orbital_elements ele[]);

void MassFlux(int i,struct orbital_elements ele[],struct fragmentation frag[],struct parameter para);

double Depletion_Time(int i,struct fragmentation frag[]);

double MassDepletion(int i,struct orbital_elements ele[]);

double s_1_FRAG_trapezoid(int n,double dx,double ini,struct parameter para);

double s_2_FRAG_trapezoid(int n,double dx,double ini,struct parameter para);

double s_3_FRAG_trapezoid(int n,double dx,double ini,struct parameter para);

double s_1_FRAG_integrand(double x,struct parameter para);

double s_2_FRAG_integrand(double x,struct parameter para);

double s_3_FRAG_integrand(double x,struct parameter para);

double s_1_FRAG(struct parameter para);

double s_2_FRAG(struct parameter para);

double s_3_FRAG(struct parameter para);

void Rotation_3D_xaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_yaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_zaxis(int i,double x_eject[][4],double theta);

void swap(double *a, double *b);

#endif //include-guard

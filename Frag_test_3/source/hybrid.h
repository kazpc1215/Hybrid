// 円盤を4分割、軌道長半径は等間隔

#ifndef INCLUDED_hybrid_H  //include-guard
#define INCLUDED_hybrid_H  //include-guard


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>

#define DIRECTORY ../data/deltar_0010au_1000_EccAnomaly0/  //ファイル保存用のディレクトリ
#define _STR(str) #str
#define STR(str) _STR(str)

//#define N 10000  //粒子の数
#define N_tr 1000  //トレーサーの数

#define RAND_SEED 1  //乱数の種

#define DELTA_R 0.010  //近傍粒子探索用  //定義しないときは初期の質量で計算した10Hill半径
#define DELTA_THETA 0.5*M_PI  //近傍粒子探索用

#define T_MAX (2.0*M_PI*1.0E4)  //10kyr  全計算時間

#define TIME_INTERVAL 2.0*M_PI*1.0E1,2.0*M_PI*1.0E2,2.0*M_PI*1.0E3,T_MAX  //t_ene配列の中身
#define TIME_INTERVAL_MAX 4  //t_ene配列の要素数

#define G 1.0  //重力定数
#define M_0 1.0  //主星の質量
#define EPSILON 0.0  //ソフトニングパラメーター
#define ETA 0.05  //刻み幅調整
#define ITE_MAX 3  //イテレーション回数

#define INNER_AXIS 0.95  //トレーサーの長軸半径　下限
#define OUTER_AXIS 1.05  //トレーサーの長軸半径　上限
#define ECC_RMS 0.01  //トレーサーの離心率の二乗平均平方根  //Rayleigh分布
//#define ECC_RMS 0.001  //トレーサーの離心率の二乗平均平方根  //Rayleigh分布
#define INC_RMS 0.005  //トレーサーの軌道傾斜角の二乗平均平方根  //Rayleigh分布
//#define INC_RMS 0.0005  //トレーサーの軌道傾斜角の二乗平均平方根  //Rayleigh分布


#define NEIGHBOR_MAX N_tr  //近傍粒子リスト配列の最大値


/*破壊用*/
#define DEPLETION_TIME_EXPLICIT 0  //1のとき、質量減少タイムスケールの計算でexplicit *(1-XI)を使う 0のときはimplicit /(1+XI)を使う
#define RHO 3.0  // [g/cc]  微惑星の物質密度
#define EPSILON_FRAG 0.2
#define B_FRAG (5.0/3.0)
#define Q_0_FRAG 9.5E8 // [erg/g]  Q_D = Q_0*(rho/3[g/cc])^0.55*(m/10^21[g])^p
#define P_FRAG 0.453
#define XI 0.01 //統計的計算のタイムステップがタイムスケールの"XI"倍
#define M_MAX 5.00E-15  //微惑星質量　1E19 g
#define M_TOT 4.994E-4  //9.933E29 g
//#define M_TOT 1.141E-2  //2.270E31 g e=0.001,i=0.0005


/*0以外のときファイル作成*/
#define ENERGY_FILE 1
#define ORBITALELEMENTS_FILE 1

#define INTERACTION 0  //トレーサー間の相互作用
#define FRAGMENTATION 1  //近傍粒子探索と質量フラックス計算



struct orbital_elements{
  char name[30];  //名前（番号）
  double mass;  //質量
  double ecc;  //離心率
  double axis;  //軌道長半径
  double u;  //離心近点離角
  double inc;  //軌道傾斜角
  double Omega;  //昇交点経度
  double omega;  //近点引数
  double r_h;  //ヒル半径
  int orinum;  //初期の番号
};



struct fragmentation{
  int neighborlist[NEIGHBOR_MAX+1];  //近傍粒子リスト
  int neighbornumber;
  double delta_r;
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

double AngularMomentum(int i,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double abs_L_0);

double InnerProduct(int i,double x_0[][4],double v_0[][4],double r_dot_v[]);

double RadiusFromCenter(int i,double x_0[][4],double r_0[]);

double SquareOfVelocity(int i,double v_0[][4],double v2_0[]);

double Timestep_i_0(int i,double a_0[][4],double adot[][4],double abs_a[],double abs_adot[],double dt_[]);

double Timestep_i_sys(int i_sys,double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_a[],double abs_adot[],double abs_adot2[],double abs_adot3[],double dt_[]);

double SquareOfRelativeDistance(int i,int j,double x_0[][4]);

double SquareOfRelativeVelocity(int i,int j,double v_0[][4]);

double RelativeInnerProduct(int i,int j,double x_0[][4],double v_0[][4]);

double Acceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double abs_r2[]);

double dAcceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v_ij[],double abs_r2[]);

double External_Acceleration(int i,int k,double x_0[][4],double r_0[]);

double External_dAcceleration(int i,int k,double x_0[][4],double v_0[][4],double r_0[],double r_dot_v[]);

double All_Acceleration(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double r_0[],double abs_r2[],double a_0[][4]);

double All_dAcceleration(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v[],double r_dot_v_ij[],double r_0[],double abs_r2[],double adot_0[][4]);

double RotatingCoordinate_X(struct orbital_elements ele[],double x_0[][4],double t_sys);

double RotatingCoordinate_Y(struct orbital_elements ele[],double x_0[][4],double t_sys);

int Calculate_OrbitalElements(int i,double x_c[][4],double v_c[][4],struct orbital_elements ele[],double P[][4],double Q[][4],double r_c[],double v2_c[],double r_dot_v[]);

double Calculate_P(int i,int k,struct orbital_elements ele[]);

double Calculate_Q(int i,int k,struct orbital_elements ele[]);

double Calculate_Energy(int i,int j,struct orbital_elements ele[],double x_c[][4],double v_c[][4],double v2_c[],double r_c[],double abs_r[],double abs_r2[],double abs_v[],double abs_v2[],double r_dot_v_ij[],double E[],double E_tot);

void InitialCondition(int i,double P[][4],double Q[][4],double x_0[][4],double v_0[][4],double r_0[],struct orbital_elements ele[]);

void Predictor(int i,double x_0[][4],double v_0[][4],double a_0[][4],double adot_0[][4],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double Dt[]);

void Corrector_sys(int i_sys,int j,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_r[],double abs_r2[],double abs_v[],double abs_v2[],double r_dot_v_ij[],double r_dot_v[],double t_sys,double dt_[]);

void Iteration_sys(int i_sys,int j,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double abs_r[],double abs_r2[],double abs_v[],double abs_v2[],double r_dot_v_ij[],double r_dot_v[],double dt_[]);

void NeighborSearch(int i,struct orbital_elements ele[],struct fragmentation frag[],double x_0[][4],double r_0[]);

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

#endif //include-guard

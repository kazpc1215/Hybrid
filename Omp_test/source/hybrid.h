#ifndef INCLUDED_hybrid_H  //include-guard
#define INCLUDED_hybrid_H  //include-guard


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <mach/mach_time.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#define DIRECTORY ../data/N100_t1E1_dt1yr_eta1E-2_10Hill_e0001i00005/  //ファイル保存用のディレクトリ.

//#define DIRECTORY /Volumes/HDCL-UT/isoya/Collision_Coalescence_3/data/N10_t1E6_dt1yr_eta1E-2_10Hill/  //Ta Mac Pro用

//#define DIRECTORY_FILE dt1E-2yr_eta1E-3  //連番のディレクトリを作りたいとき. "b****_dt1E-*yr_eta*E-*"

#define _STR(str) #str
#define STR(str) _STR(str)
#define SWAP(_a, _b) do { typeof(_a) _tmp = _a; _a = _b; _b = _tmp; } while(0)


#ifndef EXTERN
#define EXTERN extern
#endif


//////////////////////////////////////////////////
#define N_tr 0  //初期のトレーサーの数.
#define N_p 100  //初期の原始惑星の数.
static const int RAND_SEED = 1;  //乱数の種.

EXTERN int global_n;  //グローバル変数.
EXTERN int global_n_p;  //グローバル変数.
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define ENERGY_FILE TRUE  //エネルギー計算&ファイル作成.
#define ORBITALELEMENTS_FILE TRUE  //軌道要素計算&ファイル作成.
#define POSI_VELO_FILE FALSE  //位置速度ファイル作成.
#define POSI_VELO_ROT_FILE FALSE  //回転座標系の位置速度ファイル作成.
#define COLLISION_FILE TRUE  //衝突時の位置速度ファイル作成.
#define EXECUTION_TIME TRUE  //実行時間測定.
#define INDIRECT_TERM TRUE  //中心星が動く.
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define INTERACTION_ALL TRUE  //全粒子同士の重力相互作用.
#if INTERACTION_ALL
#define INTERACTION_ONLY_PLANET_TRACER FALSE
#else
#define INTERACTION_ONLY_PLANET_TRACER TRUE  //惑星とトレーサー間の重力相互作用のみ.
#endif
#define FRAGMENTATION FALSE  //破壊 近傍粒子探索と質量フラックス計算.
#define ELIMINATE_PARTICLE TRUE  //太陽に飲みこまれるか系外へ出て行くかで粒子を消す.
//////////////////////////////////////////////////


//////////////////////////////////////////////////
//#define G 1.0  //重力定数.
//#define M_0 1.0  //主星の質量.
//#define EPSILON 0.0  //ソフトニングパラメーター.
static const double ETA = 1.0E-2;  //刻み幅調整.
static const int ITE_MAX = 3;  //イテレーション回数.
//////////////////////////////////////////////////


#if ELIMINATE_PARTICLE
//////////////////////////////////////////////////
static const double SOLAR_RADIUS = 6.957E10/1.496E13;
static const double SOLAR_SYSTEM_LIMIT = 100.0;
//////////////////////////////////////////////////
#endif


//////////////////////////////////////////////////
static const double PLANET_MASS = 3.0E-7;  //火星サイズ.
static const double PLANET_ECC = 0.001;
static const double PLANET_INC = 0.0005;
static const double PLANET_DENSITY = 3.0;  //[g/cc]
static const double DELTA_AXIS = 10.0;
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


#if N_tr != 0
//////////////////////////////////////////////////
static const int PLANET_NO = 1;
static const double M_TOT = 3.0E-7;  //0.1M_E  //破片の総質量.
static const double EJECTION_CONE_ANGLE = M_PI/180.0*30.0;  //30度
static const double DELTA_R = 0.010;  //Hill 近傍粒子探索用.
static const double DELTA_THETA = 0.5*M_PI;  //近傍粒子探索用.
//////////////////////////////////////////////////
#endif


//////////////////////////////////////////////////
static const double T_MAX = 2.0*M_PI*1.0E1;  //10yr 全計算時間.
#define DT_LOG FALSE  //TRUE: t_eneをlogでとる. FALSE: t_eneをlinearでとる.

#if DT_LOG
/*  log 用 */
//#define TIME_INTERVAL 2.0*M_PI*1.0E0,2.0*M_PI*1.0E1,2.0*M_PI*1.0E2,2.0*M_PI*1.0E3,2.0*M_PI*1.0E4,2.0*M_PI*1.0E5,2.0*M_PI*1.0E6,2.0*M_PI*1.0E7,T_MAX  //t_ene配列の中身.
#define TIME_INTERVAL 2.0*M_PI*1.0E0,2.0*M_PI*1.0E1,2.0*M_PI*1.0E2,2.0*M_PI*1.0E3,T_MAX  //t_ene配列の中身.
static const int TIME_INTERVAL_MAX = 5; //t_ene配列の要素数.
#else
/*  linear 用 */    
static const double DT_ENE = 2.0*M_PI*1.0E0;  //dt_ene = 1yr
#endif
//////////////////////////////////////////////////


#if FRAGMENTATION
//////////////////////////////////////////////////
static const double INNER_AXIS = 0.95;  //トレーサーの長軸半径　下限.
static const double OUTER_AXIS = 1.05;  //トレーサーの長軸半径　上限.
static const double ECC_RMS = 0.01;  //トレーサーの離心率の二乗平均平方根. //Rayleigh分布
static const double INC_RMS = 0.005;  //トレーサーの軌道傾斜角の二乗平均平方根.  //Rayleigh分布
#define NEIGHBOR_MAX N_tr  //近傍粒子リスト配列の最大値.
#define DEPLETION_TIME_EXPLICIT FALSE  //TRUE: 質量減少タイムスケールの計算でexplicit *(1-XI)を使う. FALSE: implicit /(1+XI)を使う.

static const double RHO = 3.0;  // [g/cc]  微惑星の物質密度.
static const double EPSILON_FRAG = 0.2;
static const double B_FRAG = 5.0/3.0;
static const double Q_0_FRAG = 9.5E8; // [erg/g]  Q_D = Q_0*(rho/3[g/cc])^0.55*(m/10^21[g])^p
static const double P_FRAG = 0.453;
static const double XI = 0.01; //統計的計算のタイムステップがタイムスケールの"XI"倍.
static const double M_MAX = 5.00E-15;  //最大微惑星質量. 1E19 g
//////////////////////////////////////////////////
#endif


struct orbital_elements{
  char name[30];  //名前（番号.
  double ecc;  //離心率.
  double axis;  //軌道長半径.
  double u;  //離心近点離角.
  double inc;  //軌道傾斜角.
  double Omega;  //昇交点経度.
  double omega;  //近点引数.
  double r_h;  //ヒル半径.
  double radius;  //物理半径.
  double mass;  //質量.
  int orinum;  //初期の番号.
};


#if FRAGMENTATION
struct fragmentation{
  int neighborlist[NEIGHBOR_MAX+1];  //近傍粒子リスト.
  int neighbornumber;  //近傍粒子の個数
  double delta_r_out;  //扇型外側.
  double delta_r_in;  //扇型内側.
  double sigma;  //表面密度.
  double n_s;  //表面数密度.
  double v_ave;  //領域内での平均速度.
  double flux;  //質量フラックス.
  double dt_frag;  //統計的計算の粒子ごとのタイムステップ.
  double t_frag;  //統計的計算の粒子ごとの時間.
  int fragtimes;  //何回統計的計算をしているか.
};

  
struct parameter{
  double s_1;
  double s_2;
  double s_3;
  double alpha;
  double h_0;
  double Q_D;
};
#endif


#if EXECUTION_TIME
struct execution_time{
  double Energy;
  double Orbital_Elements;
  double Predictor;
  double Corrector;
  double Iteration;
  double Collision_Judgement;
  double Fragmentation;
};
EXTERN struct execution_time exetime;  //グローバル変数
EXTERN mach_timebase_info_data_t sTimebaseInfo;
#endif


#endif //include-guard

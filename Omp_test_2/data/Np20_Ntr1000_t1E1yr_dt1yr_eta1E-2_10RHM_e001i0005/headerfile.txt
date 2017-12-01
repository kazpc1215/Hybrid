#ifndef INCLUDED_hybrid_H  //include-guard
#define INCLUDED_hybrid_H  //include-guard


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>


#define TRUE 1
#define FALSE 0

#ifdef _OPENMP
#include <omp.h>
#define OMP_THREADS 2  //OpenMP並列数
#endif

//constでエラーが出るため
#if __GNUC__ == 7
#define CONST const
#elif __GNUC__ == 4
#define CONST
#endif

#define DIRECTORY ../data/Np20_Ntr1000_t1E1yr_dt1yr_eta1E-2_10RHM_e001i0005/  //ファイル保存用のディレクトリ.

//#define DIRECTORY /Volumes/HDCL-UT/isoya/Collision_Coalescence_3/data/N10_t1E6_dt1yr_eta1E-2_10Hill/  //Ta Mac Pro用

//#define DIRECTORY_FILE dt1E-2yr_eta1E-3  //連番のディレクトリを作りたいとき. "b****_dt1E-*yr_eta*E-*"

#define STR_(str) #str
#define STR(str) STR_(str)


#ifndef EXTERN
#define EXTERN extern
#endif


//////////////////////////////////////////////////
#define N_tr 1000  //初期のトレーサーの数.
#define N_p 20  //初期の原始惑星の数.
#define RAND_SEED 1  //乱数の種.
#define STEP_INTERVAL 1.0E4  //何ステップごとに出力するか

EXTERN int global_n;  //グローバル変数.
EXTERN int global_n_p;  //グローバル変数.
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define ENERGY_FILE TRUE  //エネルギー計算&ファイル作成.
#define ORBITALELEMENTS_FILE TRUE  //軌道要素計算&ファイル作成.
#define POSI_VELO_FILE FALSE  //位置速度ファイル作成.
#define POSI_VELO_ROT_FILE FALSE  //回転座標系の位置速度ファイル作成.
#define COLLISION_FILE TRUE  //衝突時の位置速度ファイル作成.
#define EXECUTION_TIME FALSE  //実行時間測定.
#if EXECUTION_TIME
#include <mach/mach_time.h>
#endif
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define INTERACTION_ALL TRUE  //全粒子同士の重力相互作用.
#define INTERACTION_ONLY_PLANET_TRACER (!INTERACTION_ALL)  //惑星とトレーサー間の重力相互作用のみ.
#define INDIRECT_TERM TRUE  //中心星が動く.
#define FRAGMENTATION FALSE  //破壊 近傍粒子探索と質量フラックス計算.
#define COLLISION TRUE  //衝突
#define EJECTION FALSE  //衝突後に破片をコーン状に放出する.
#define ORBITING_SMALL_PARTICLE TRUE  //微惑星を初期にケプラー運動させておく.
#define ELIMINATE_PARTICLE FALSE  //太陽に飲みこまれるか系外へ出て行くかで粒子を消す.
//////////////////////////////////////////////////


//////////////////////////////////////////////////
//#define G 1.0  //重力定数.
//#define M_0 1.0  //主星の質量.
//#define EPSILON 0.0  //ソフトニングパラメーター.
#define ETA 1.0E-2  //刻み幅調整.
#define ITE_MAX 2  //イテレーション回数.
//////////////////////////////////////////////////


#if ELIMINATE_PARTICLE
//////////////////////////////////////////////////
#define SOLAR_RADIUS (6.957E10/1.496E13)
#define SOLAR_SYSTEM_LIMIT 100.0
//////////////////////////////////////////////////
#endif


//////////////////////////////////////////////////
#define PLANET_MASS 3.0E-7  //火星サイズ.
#define PLANET_ECC 0.01
#define PLANET_INC 0.005
#define PLANET_DENSITY 3.0  //[g/cc]
#define PLANET_INNER_AXIS 0.5
#define DELTA_AXIS 10.0
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
#if EJECTION
#define PLANET_NO 1
#define EJECTION_CONE_ANGLE M_PI/180.0*30.0  //30度
#endif

#if ORBITING_SMALL_PARTICLE
#define INNER_AXIS 0.5  //トレーサーの長軸半径 下限.
#define OUTER_AXIS 1.5  //トレーサーの長軸半径 上限.
#define ECC_RMS 0.01  //トレーサーの離心率の二乗平均平方根. //Rayleigh分布
#define INC_RMS 0.005  //トレーサーの軌道傾斜角の二乗平均平方根.  //Rayleigh分布
#endif

#if FRAGMENTATION
#define M_TOT 3.0E-7  //0.1M_E  //破片の総質量.
#define DELTA_R 0.010  //Hill 近傍粒子探索用.
#define DELTA_THETA 0.5*M_PI  //近傍粒子探索用.
#endif
//////////////////////////////////////////////////
#endif


//////////////////////////////////////////////////
#define T_MAX (2.0*M_PI*1.0E1)  //10yr 全計算時間.
#define DT_LOG FALSE  //TRUE: t_eneをlogでとる. FALSE: t_eneをlinearでとる.

#if DT_LOG
/*  log 用 */
//#define TIME_INTERVAL 2.0*M_PI*1.0E0,2.0*M_PI*1.0E1,2.0*M_PI*1.0E2,2.0*M_PI*1.0E3,2.0*M_PI*1.0E4,2.0*M_PI*1.0E5,2.0*M_PI*1.0E6,2.0*M_PI*1.0E7,T_MAX  //t_ene配列の中身.
#define TIME_INTERVAL 2.0*M_PI*1.0E0,2.0*M_PI*1.0E1,2.0*M_PI*1.0E2,2.0*M_PI*1.0E3,T_MAX  //t_ene配列の中身.
#define TIME_INTERVAL_MAX 5 //t_ene配列の要素数.
#else
/*  linear 用 */
#define DT_ENE (2.0*M_PI*1.0E0)  //dt_ene = 1yr
#endif
//////////////////////////////////////////////////


#if FRAGMENTATION
//////////////////////////////////////////////////
#define NEIGHBOR_MAX N_tr  //近傍粒子リスト配列の最大値.
#define DEPLETION_TIME_EXPLICIT FALSE  //TRUE: 質量減少タイムスケールの計算でexplicit *(1-XI)を使う. FALSE: implicit /(1+XI)を使う.

#define RHO 3.0  // [g/cc]  微惑星の物質密度.
#define EPSILON_FRAG 0.2
#define B_FRAG (5.0/3.0)
#define Q_0_FRAG 9.5E8 // [erg/g]  Q_D = Q_0*(rho/3[g/cc])^0.55*(m/10^21[g])^p
#define P_FRAG 0.453
#define XI 0.01 //統計的計算のタイムステップがタイムスケールの"XI"倍.
#define M_MAX 5.00E-15  //最大微惑星質量. 1E19 g
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

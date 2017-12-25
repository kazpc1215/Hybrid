#ifndef INCLUDED_hybrid_H  //include-guard
#define INCLUDED_hybrid_H  //include-guard


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>


#ifdef _OPENMP
#include <omp.h>
#define OMP_SCHEDULE static
//#define GOMP_CPU_AFFINITY 0 2
#endif


//#define CONST const
//constでエラーが出るため
#if __GNUC__ == 7
#define CONST const
#elif __GNUC__ == 4
#define CONST
#endif


#define DIRECTORY ../data/Ntr1E3_t2E0yr_dt1yr_eta1E-2_e1E-2_i5E-3_rand1/  //ファイル保存用のディレクトリ.


//#define DIRECTORY_FILE dt1E-2yr_eta1E-3  //連番のディレクトリを作りたいとき. "b****_dt1E-*yr_eta*E-*"

#define STR_(str) #str
#define STR(str) STR_(str)

#define INV_3 0.33333333333333333333

#ifndef EXTERN
#define EXTERN extern
#endif


//////////////////////////////////////////////////
#define N_tr 1000  //初期のトレーサーの数.
#define N_p 1  //初期の原始惑星の数.
#define RAND_SEED 1  //乱数の種.
#define STEP_INTERVAL 1.0E5  //何ステップごとに標準出力するか
#define BREAK_TIME 10.0  //4h = 14400sec

EXTERN int global_n;  //グローバル変数.
EXTERN int global_n_p;  //グローバル変数.
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define ENERGY_FILE true  //エネルギー計算&ファイル作成.
#define ORBITALELEMENTS_FILE true  //軌道要素計算&ファイル作成.
#define POSI_VELO_FILE false  //位置速度ファイル作成.
#define POSI_VELO_ROT_FILE false  //回転座標系の位置速度ファイル作成.
#define COLLISION_FILE false  //衝突時の位置速度ファイル作成.
#define EXECUTION_TIME true  //実行時間測定.
#if EXECUTION_TIME
#include <sys/time.h>
#include <sys/resource.h>
#endif
//////////////////////////////////////////////////


//////////////////////////////////////////////////
#define INTERACTION_ALL false  //全粒子同士の重力相互作用.
#define INTERACTION_PLANET_TRACER true  //惑星とトレーサー間の相互作用（惑星に影響を与え，かつ惑星から影響を受ける）.
#define INTERACTION_TEST_PARTICLE false  //トレーサーをテスト粒子として扱う（惑星に影響を与えないが惑星から影響を受ける）.
#define INDIRECT_TERM true  //中心星が動く.
#define FRAGMENTATION false  //破壊 近傍粒子探索と質量フラックス計算.
#define COLLISION false  //衝突
#define EJECTION false  //衝突後に破片をコーン状に放出する.
#define ORBITING_SMALL_PARTICLE true  //微惑星を初期にケプラー運動させておく.
#define ELIMINATE_PARTICLE false  //太陽に飲みこまれるか系外へ出て行くかで粒子を消す.
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
#define PLANET_NO 1
#define PLANET_MASS 3.0E-6  //地球サイズ.
#define PLANET_ECC 0.01
#define PLANET_INC 0.005
#define PLANET_DENSITY 3.0  //[g/cc]
#define PLANET_AXIS 1.0
//#define PLANET_INNER_AXIS 0.5
//#define DELTA_AXIS 10.0
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
#define EJECTION_CONE_ANGLE M_PI/180.0*30.0  //30度.
#endif

#if ORBITING_SMALL_PARTICLE
//#define INNER_AXIS 0.5  //トレーサーの長軸半径 下限.
//#define OUTER_AXIS 1.5  //トレーサーの長軸半径 上限.
#define ECC_RMS 0.01  //トレーサーの離心率の二乗平均平方根.  //Rayleigh分布.
#define INC_RMS 0.005  //トレーサーの軌道傾斜角の二乗平均平方根.  //Rayleigh分布.
#endif

#if FRAGMENTATION
#define M_TOT 3.0E-7  //0.1M_E  //破片の総質量.
#define DELTA_R 0.010  //Hill 近傍粒子探索用.
#define DELTA_THETA 0.5*M_PI  //近傍粒子探索用.
#endif
//////////////////////////////////////////////////
#endif


//////////////////////////////////////////////////
#define T_MAX (2.0*M_PI*2.0E0)  //2yr 全計算時間.
#define DT_LOG false  //true: t_eneをlogでとる. false: t_eneをlinearでとる.

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
#define DEPLETION_TIME_EXPLICIT false  //true: 質量減少タイムスケールの計算でexplicit *(1-XI)を使う. false: implicit /(1+XI)を使う.

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
  double Energy[3];  //[0]: real time, [1]: user(cpu) time, [2]: system time
  double Orbital_Elements[3];
  double Predictor[3];
  double Corrector[3];
  double Iteration[3];
  double Collision_Judgement[3];
  double Fragmentation[3];
};
EXTERN struct execution_time exetime;  //グローバル変数
#endif


#endif //include-guard

#ifndef INCLUDED_FUNC_H  //include-guard
#define INCLUDED_FUNC_H  //include-guard


#include "hybrid.h"

double AngularMomentum(int i,CONST struct orbital_elements *ele_p,CONST double x_0[][4],CONST double v_0[][4]);

double Timestep_i_0(int i,CONST double a_0[][4],CONST double adot_0[][4]);

double Timestep_i_sys(int i_sys,CONST double a[][4],CONST double adot[][4],CONST double adot2_dt2[][4],CONST double adot3_dt3[][4],CONST double dt_[]);

double Acceleration_ij(int i,int j,int k,CONST struct orbital_elements *ele_p,CONST double x_0[][4],CONST double abs_r[]);

double dAcceleration_ij(int i,int j,int k,CONST struct orbital_elements *ele_p,CONST double x_0[][4],CONST double v_0[][4],CONST double r_dot_v_ij[],CONST double abs_r[]);

double Acceleration_indirect(int i,int k,CONST struct orbital_elements *ele_p,CONST double x_0[][4],CONST double r_0[]);

double dAcceleration_indirect(int i,int k,CONST struct orbital_elements *ele_p,CONST double x_0[][4],CONST double v_0[][4],CONST double r_0[],CONST double r_dot_v[]);

double External_Acceleration(int i,int k,CONST double x_0[][4],CONST double r_0[]);

double External_dAcceleration(int i,int k,CONST double x_0[][4],CONST double v_0[][4],CONST double r_0[],CONST double r_dot_v[]);

double All_Acceleration(int i,int k,CONST struct orbital_elements *ele_p,CONST double x_0[][4],CONST double r_0[],CONST double abs_r[]);

double All_dAcceleration(int i,int k,CONST struct orbital_elements *ele_p,CONST double x_0[][4],CONST double v_0[][4],CONST double r_dot_v[],CONST double r_dot_v_ij[],CONST double r_0[],CONST double abs_r[]);

void Calculate_OrbitalElements(int i,CONST double x_c[][4],CONST double v_c[][4],struct orbital_elements *ele_p,double P[][4],double Q[][4],CONST double r_c[],CONST double v2_c[],CONST double r_dot_v[]);

double Calculate_P(int i,int k,CONST struct orbital_elements *ele_p);

double Calculate_Q(int i,int k,CONST struct orbital_elements *ele_p);

double Calculate_Energy(CONST struct orbital_elements *ele_p,CONST double x_c[][4],
#if INDIRECT_TERM
			CONST double v_c[][4],CONST double v_G[],
#else
			CONST double v2_c[],
#endif
			CONST double r_c[]);

void InitialCondition(int i,double P[][4],double Q[][4],double x_0[][4],double v_0[][4],double v2_0[],double r_dot_v[],double r_0[],CONST struct orbital_elements *ele_p);

void Predictor(int i,CONST double x_0[][4],CONST double v_0[][4],CONST double a_0[][4],CONST double adot_0[][4],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double r_dot_v[],CONST double Dt[]);

void Corrector_sys(int i_sys,CONST struct orbital_elements *ele_p,CONST double x_p[][4],CONST double v_p[][4],CONST double r_p[],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double r_dot_v[],CONST double a_0[][4],CONST double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],CONST double dt_[]);

void Iteration_sys(int i_sys,CONST struct orbital_elements *ele_p,CONST double x_p[][4],CONST double v_p[][4],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double r_dot_v[],CONST double a_0[][4],CONST double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],CONST double dt_[]);

#if COLLISION
bool Collision_Judgement(int i_sys,CONST struct orbital_elements *ele_p,CONST double x_p[][4],double abs_r[],int *i_col, int *j_col);

void Energy_Correction(int i_col,int j_col,CONST double x_0[][4],CONST double v_0[][4],CONST struct orbital_elements *ele_p,double *dE_heat,double *dE_grav,double *dE_c,double *v_imp);

void Coalescence(int i_col,int j_col,double x_0[][4],double v_0[][4],struct orbital_elements *ele_p);
#endif

#if FRAGMENTATION
void NeighborSearch(int i,CONST struct orbital_elements *ele_p,struct fragmentation *frag_p,CONST double x_0[][4]);

double RandomVelocity(int i,int j,CONST struct orbital_elements *ele_p);

void MassFlux(int i,CONST struct orbital_elements *ele_p,struct fragmentation *frag_p,CONST struct parameter *para_p);

double Depletion_Time(int i,CONST struct fragmentation *frag_p);

double MassDepletion(int i,CONST struct orbital_elements *ele_p);

double s_1_FRAG_trapezoid(int n,double dx,double ini,CONST struct parameter *para_p);

double s_2_FRAG_trapezoid(int n,double dx,double ini,CONST struct parameter *para_p);

double s_3_FRAG_trapezoid(int n,double dx,double ini,CONST struct parameter *para_p);

double s_1_FRAG_integrand(double x,CONST struct parameter *para_p);

double s_2_FRAG_integrand(double x,CONST struct parameter *para_p);

double s_3_FRAG_integrand(double x,CONST struct parameter *para_p);

double s_1_FRAG(struct parameter *para_p);

double s_2_FRAG(struct parameter *para_p);

double s_3_FRAG(struct parameter *para_p);
#endif

void Rotation_3D_xaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_yaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_zaxis(int i,double x_eject[][4],double theta);

#if INDIRECT_TERM
void CenterOfGravity(CONST double x_0[][4],CONST double v_0[][4],double x_G[],double v_G[],CONST struct orbital_elements *ele_p);
#endif

#if EXECUTION_TIME
void Calculate_Exetime(uint64_t start_main,uint64_t end_main);
#endif

#endif //include-guard


//わざとインクルードガードから外し、static付きで定義
//inline関数

/*x_i,v_iの内積*/
static inline double InnerProduct(int i,CONST double x[][4],CONST double v[][4]){
  return x[i][1]*v[i][1] + x[i][2]*v[i][2] + x[i][3]*v[i][3];
}

/*中心星からの距離*/
static inline double RadiusFromCenter(int i,CONST double x[][4]){
  return sqrt(x[i][1]*x[i][1] + x[i][2]*x[i][2] + x[i][3]*x[i][3]);
}

/*速度の2乗*/
static inline double SquareOfVelocity(int i,CONST double v[][4]){
  return v[i][1]*v[i][1] + v[i][2]*v[i][2] + v[i][3]*v[i][3];
}

/*相対距離*/
static inline double RelativeDistance(int i,int j,CONST double x[][4]){
  return sqrt((x[j][1] - x[i][1])*(x[j][1] - x[i][1]) + (x[j][2] - x[i][2])*(x[j][2] - x[i][2]) + (x[j][3] - x[i][3])*(x[j][3] - x[i][3]));
}

/*相対速度の2乗*/
static inline double SquareOfRelativeVelocity(int i,int j,CONST double v[][4]){
  return (v[j][1] - v[i][1])*(v[j][1] - v[i][1]) + (v[j][2] - v[i][2])*(v[j][2] - v[i][2]) + (v[j][3] - v[i][3])*(v[j][3] - v[i][3]);
}

/*x_ij, v_ijの内積*/
static inline double RelativeInnerProduct(int i,int j,CONST double x[][4],CONST double v[][4]){
  return (x[j][1] - x[i][1])*(v[j][1] - v[i][1]) + (x[j][2] - x[i][2])*(v[j][2] - v[i][2]) + (x[j][3] - x[i][3])*(v[j][3] - v[i][3]);
}

/*Swap*/
static inline void Swap_double(double *a, double *b){
  double tmp;
  tmp = (*a);
  (*a) = (*b);
  (*b) = tmp;
}


static inline void Swap_int(int *a, int *b){
  int tmp;
  tmp = (*a);
  (*a) = (*b);
  (*b) = tmp;
}


static inline int Min_int(int a, int b){
  if(a < b){
    return a;
  }else{
    return b;
  }
}


static inline int Max_int(int a, int b){
  if(a > b){
    return a;
  }else{
    return b;
  }
}

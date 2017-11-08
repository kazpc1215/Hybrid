#ifndef INCLUDED_FUNC_H  //include-guard
#define INCLUDED_FUNC_H  //include-guard


#include "hybrid.h"

double AngularMomentum(int i,const struct orbital_elements *ele_p,const double x_0[][4],const double v_0[][4]);

double Timestep_i_0(int i,const double a_0[][4],const double adot_0[][4]);

double Timestep_i_sys(int i_sys,const double a[][4],const double adot[][4],const double adot2_dt2[][4],const double adot3_dt3[][4],const double dt_[]);

double Acceleration_ij(int i,int j,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double abs_r[]);

double dAcceleration_ij(int i,int j,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double v_0[][4],const double r_dot_v_ij[],const double abs_r[]);

double Acceleration_indirect(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double r_0[]);

double dAcceleration_indirect(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double v_0[][4],const double r_0[],const double r_dot_v[]);

double External_Acceleration(int i,int k,const double x_0[][4],const double r_0[]);

double External_dAcceleration(int i,int k,const double x_0[][4],const double v_0[][4],const double r_0[],const double r_dot_v[]);

double All_Acceleration(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double r_0[],const double abs_r[]);

double All_dAcceleration(int i,int k,const struct orbital_elements *ele_p,const double x_0[][4],const double v_0[][4],const double r_dot_v[],const double r_dot_v_ij[],const double r_0[],const double abs_r[]);

void Calculate_OrbitalElements(int i,const double x_c[][4],const double v_c[][4],struct orbital_elements *ele_p,double P[][4],double Q[][4],const double r_c[],const double v2_c[],const double r_dot_v[]);

double Calculate_P(int i,int k,const struct orbital_elements *ele_p);

double Calculate_Q(int i,int k,const struct orbital_elements *ele_p);

double Calculate_Energy(const struct orbital_elements *ele_p,const double x_c[][4],
#if INDIRECT_TERM
			const double v_c[][4],const double v_G[],
#else
			const double v2_c[],
#endif
			const double r_c[]);

void InitialCondition(int i,double P[][4],double Q[][4],double x_0[][4],double v_0[][4],double v2_0[],double r_dot_v[],double r_0[],const struct orbital_elements *ele_p);

void Predictor(int i,const double x_0[][4],const double v_0[][4],const double a_0[][4],const double adot_0[][4],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double r_dot_v[],const double Dt[]);

void Corrector_sys(int i_sys,const struct orbital_elements *ele_p,const double x_p[][4],const double v_p[][4],const double r_p[],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double r_dot_v[],const double a_0[][4],const double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],const double dt_[]);

void Iteration_sys(int i_sys,const struct orbital_elements *ele_p,const double x_p[][4],const double v_p[][4],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double r_dot_v[],const double a_0[][4],const double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],const double dt_[]);

#if COLLISION
bool Collision_Judgement(const struct orbital_elements *ele_p,const double x_p[][4],double abs_r[],int *i_col, int *j_col);

void Energy_Correction(int i_col,int j_col,const double x_0[][4],const double v_0[][4],const struct orbital_elements *ele_p,double *dE_heat,double *dE_grav,double *dE_c,double *v_imp);

void Coalescence(int i_col,int j_col,double x_0[][4],double v_0[][4],struct orbital_elements *ele_p);
#endif

#if FRAGMENTATION
void NeighborSearch(int i,const struct orbital_elements *ele_p,struct fragmentation *frag_p,const double x_0[][4]);

double RandomVelocity(int i,int j,const struct orbital_elements *ele_p);

void MassFlux(int i,const struct orbital_elements *ele_p,struct fragmentation *frag_p,const struct parameter *para_p);

double Depletion_Time(int i,const struct fragmentation *frag_p);

double MassDepletion(int i,const struct orbital_elements *ele_p);

double s_1_FRAG_trapezoid(int n,double dx,double ini,const struct parameter *para_p);

double s_2_FRAG_trapezoid(int n,double dx,double ini,const struct parameter *para_p);

double s_3_FRAG_trapezoid(int n,double dx,double ini,const struct parameter *para_p);

double s_1_FRAG_integrand(double x,const struct parameter *para_p);

double s_2_FRAG_integrand(double x,const struct parameter *para_p);

double s_3_FRAG_integrand(double x,const struct parameter *para_p);

double s_1_FRAG(struct parameter *para_p);

double s_2_FRAG(struct parameter *para_p);

double s_3_FRAG(struct parameter *para_p);
#endif

void Rotation_3D_xaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_yaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_zaxis(int i,double x_eject[][4],double theta);

#if INDIRECT_TERM
void CenterOfGravity(const double x_0[][4],const double v_0[][4],double x_G[],double v_G[],const struct orbital_elements *ele_p);
#endif

#if EXECUTION_TIME
void Calculate_Exetime(uint64_t start_main,uint64_t end_main);
#endif


//inline関数

/*x_i,v_iの内積*/
inline double InnerProduct(int i,const double x[][4],const double v[][4]){
  return x[i][1]*v[i][1] + x[i][2]*v[i][2] + x[i][3]*v[i][3];
}

/*中心星からの距離*/
inline double RadiusFromCenter(int i,const double x[][4]){
  return sqrt(x[i][1]*x[i][1] + x[i][2]*x[i][2] + x[i][3]*x[i][3]);
}

/*速度の2乗*/
inline double SquareOfVelocity(int i,const double v[][4]){
  return v[i][1]*v[i][1] + v[i][2]*v[i][2] + v[i][3]*v[i][3];
}

/*相対距離*/
inline double RelativeDistance(int i,int j,const double x[][4]){
  return sqrt((x[j][1] - x[i][1])*(x[j][1] - x[i][1]) + (x[j][2] - x[i][2])*(x[j][2] - x[i][2]) + (x[j][3] - x[i][3])*(x[j][3] - x[i][3]));
}

/*相対速度の2乗*/
inline double SquareOfRelativeVelocity(int i,int j,const double v[][4]){
  return (v[j][1] - v[i][1])*(v[j][1] - v[i][1]) + (v[j][2] - v[i][2])*(v[j][2] - v[i][2]) + (v[j][3] - v[i][3])*(v[j][3] - v[i][3]);
}

/*x_ij, v_ijの内積*/
inline double RelativeInnerProduct(int i,int j,const double x[][4],const double v[][4]){
  return (x[j][1] - x[i][1])*(v[j][1] - v[i][1]) + (x[j][2] - x[i][2])*(v[j][2] - v[i][2]) + (x[j][3] - x[i][3])*(v[j][3] - v[i][3]);
}

/*Swap*/
inline void Swap_double(double *a, double *b){
  double tmp;
  tmp = (*a);
  (*a) = (*b);
  (*b) = tmp;
}


inline void Swap_int(int *a, int *b){
  int tmp;
  tmp = (*a);
  (*a) = (*b);
  (*b) = tmp;
}

#endif //include-guard

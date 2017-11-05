#ifndef INCLUDED_FUNC_H  //include-guard
#define INCLUDED_FUNC_H  //include-guard


#include "hybrid.h"

double AngularMomentum(int i,struct orbital_elements ele[],double x_0[][4],double v_0[][4]);

double Timestep_i_0(int i,double a_0[][4],double adot_0[][4]);

double Timestep_i_sys(int i_sys,double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double dt_[]);

double Acceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double abs_r[]);

double dAcceleration_ij(int i,int j,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v_ij[],double abs_r[]);

double Acceleration_indirect(int i,int k,struct orbital_elements ele[],double x_0[][4],double r_0[]);

double dAcceleration_indirect(int i,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_0[],double r_dot_v[]);

double External_Acceleration(int i,int k,double x_0[][4],double r_0[]);

double External_dAcceleration(int i,int k,double x_0[][4],double v_0[][4],double r_0[],double r_dot_v[]);

double All_Acceleration(int i,int k,struct orbital_elements ele[],double x_0[][4],double r_0[],double abs_r[]);

double All_dAcceleration(int i,int k,struct orbital_elements ele[],double x_0[][4],double v_0[][4],double r_dot_v[],double r_dot_v_ij[],double r_0[],double abs_r[]);

void Calculate_OrbitalElements(int i,double x_c[][4],double v_c[][4],struct orbital_elements ele[],double P[][4],double Q[][4],double r_c[],double v2_c[],double r_dot_v[]);

double Calculate_P(int i,int k,struct orbital_elements ele[]);

double Calculate_Q(int i,int k,struct orbital_elements ele[]);

double Calculate_Energy(struct orbital_elements ele[],double x_c[][4],
#if INDIRECT_TERM
			double v_c[][4],double v_G[],
#else
			double v2_c[],
#endif
			double r_c[]);

void InitialCondition(int i,double P[][4],double Q[][4],double x_0[][4],double v_0[][4],double v2_0[],double r_dot_v[],double r_0[],struct orbital_elements ele[]);

void Predictor(int i,double x_0[][4],double v_0[][4],double a_0[][4],double adot_0[][4],double x_p[][4],double v_p[][4],double r_p[],double v2_p[],double r_dot_v[],double Dt[]);

void Corrector_sys(int i_sys,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double r_p[],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double r_dot_v[],double dt_[]);

void Iteration_sys(int i_sys,struct orbital_elements ele[],double x_p[][4],double v_p[][4],double x_c[][4],double v_c[][4],double r_c[],double v2_c[],double a_0[][4],double adot_0[][4],double a[][4],double adot[][4],double adot2_dt2[][4],double adot3_dt3[][4],double r_dot_v[],double dt_[]);

int Collision_Judgement(struct orbital_elements ele[],double x_p[][4],double abs_r[],int *i_col, int *j_col);

void Energy_Correction(int i_col,int j_col,double x_0[][4],double v_0[][4],struct orbital_elements ele[],double *dE_heat,double *dE_grav,double *dE_c,double *v_imp);

void Coalescence(int i_col,int j_col,double x_0[][4],double v_0[][4],struct orbital_elements ele[]);

#if FRAGMENTATION
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
#endif

void Rotation_3D_xaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_yaxis(int i,double x_eject[][4],double theta);

void Rotation_3D_zaxis(int i,double x_eject[][4],double theta);

void CenterOfGravity(double x_0[][4],double v_0[][4],double x_G[],double v_G[],struct orbital_elements ele[]);

void Calculate_Exetime(uint64_t start_main,uint64_t end_main);

//inline関数

/*r_i,v_iの内積*/
static inline double InnerProduct(int i,double x_0[][4],double v_0[][4]){
  return x_0[i][1]*v_0[i][1] + x_0[i][2]*v_0[i][2] + x_0[i][3]*v_0[i][3];
}


/*中心星からの距離*/
static inline double RadiusFromCenter(int i,double x_0[][4]){
  return sqrt(x_0[i][1]*x_0[i][1] + x_0[i][2]*x_0[i][2] + x_0[i][3]*x_0[i][3]);
}

/*速度の2乗*/
static inline double SquareOfVelocity(int i,double v_0[][4]){
  return v_0[i][1]*v_0[i][1] + v_0[i][2]*v_0[i][2] + v_0[i][3]*v_0[i][3];
}

/*相対距離*/
static inline double RelativeDistance(int i,int j,double x_0[][4]){
  return sqrt((x_0[j][1] - x_0[i][1])*(x_0[j][1] - x_0[i][1]) + (x_0[j][2] - x_0[i][2])*(x_0[j][2] - x_0[i][2]) + (x_0[j][3] - x_0[i][3])*(x_0[j][3] - x_0[i][3]));
}

/*相対速度の2乗*/
static inline double SquareOfRelativeVelocity(int i,int j,double v_0[][4]){
  return (v_0[j][1] - v_0[i][1])*(v_0[j][1] - v_0[i][1]) + (v_0[j][2] - v_0[i][2])*(v_0[j][2] - v_0[i][2]) + (v_0[j][3] - v_0[i][3])*(v_0[j][3] - v_0[i][3]);
}

/*r_ij, v_ijの内積*/
static inline double RelativeInnerProduct(int i,int j,double x_0[][4],double v_0[][4]){
  return (x_0[j][1] - x_0[i][1])*(v_0[j][1] - v_0[i][1]) + (x_0[j][2] - x_0[i][2])*(v_0[j][2] - v_0[i][2]) + (x_0[j][3] - x_0[i][3])*(v_0[j][3] - v_0[i][3]);
}

#endif //include-guard

#include "hybrid.h"

void MassFlux(int i,struct orbital_elements ele[],struct fragmentation frag[],struct parameter para){
  clock_t start = clock();
  
  double F;
  double a_inv=1.0/ele[i].axis;
  double alpha=para.alpha;
  double v=frag[i].v_ave;
  double sigma=frag[i].sigma;
  double s_1=para.s_1;
  double s_2=para.s_2;
  double s_3=para.s_3;
  double Q_D=para.Q_D;
  double h_0=para.h_0;

#if !defined(G) && !defined(M_0)
  F = - (2.0 - alpha)*(2.0 - alpha)/cbrt(M_MAX)*sigma*sigma*sqrt(a_inv*a_inv*a_inv)*h_0;
#else
  F = - (2.0 - alpha)*(2.0 - alpha)/cbrt(M_MAX)*sigma*sigma*sqrt(G*M_0*a_inv*a_inv*a_inv)*h_0;
#endif
  
  F *= pow(v*v*0.5/Q_D,alpha-1.0);
  F *= ((- log(EPSILON_FRAG) + 1.0/(2.0-B_FRAG))*s_1 + s_2 + s_3);

  frag[i].flux = F;

  clock_t end = clock();
  exetime.MassFlux += (double)(end-start)/CLOCKS_PER_SEC;
}


double Depletion_Time(int i,struct fragmentation frag[]){
  clock_t start = clock();
  
  return -XI*frag[i].sigma/frag[i].flux;

  clock_t end = clock();
  exetime.Depletion_Time += (double)(end-start)/CLOCKS_PER_SEC;
}

double MassDepletion(int i,struct orbital_elements ele[]){
  clock_t start = clock();
  
#if DEPLETION_TIME_EXPLICIT
  return (1.0 - XI)*ele[i].mass;
#else
  return ele[i].mass/(1.0 + XI);
#endif

  clock_t end = clock();
  exetime.MassDepletion += (double)(end-start)/CLOCKS_PER_SEC;
}




double s_1_FRAG_trapezoid(int n,double dx,double ini,struct parameter para){
  clock_t start = clock();
  
  return 0.5*dx*(s_1_FRAG_integrand(ini+n*dx,para)+s_1_FRAG_integrand(ini+(n+1)*dx,para));

  clock_t end = clock();
  exetime.s_1_FRAG_trapezoid += (double)(end-start)/CLOCKS_PER_SEC;
}

double s_2_FRAG_trapezoid(int n,double dx,double ini,struct parameter para){
  clock_t start = clock();
  
  return 0.5*dx*(s_2_FRAG_integrand(ini+n*dx,para)+s_2_FRAG_integrand(ini+(n+1)*dx,para));

  clock_t end = clock();
  exetime.s_2_FRAG_trapezoid += (double)(end-start)/CLOCKS_PER_SEC;
}

double s_3_FRAG_trapezoid(int n,double dx,double ini,struct parameter para){
  clock_t start = clock();

  return 0.5*dx*(s_3_FRAG_integrand(ini+n*dx,para)+s_3_FRAG_integrand(ini+(n+1)*dx,para));

  clock_t end = clock();
  exetime.s_3_FRAG_trapezoid += (double)(end-start)/CLOCKS_PER_SEC;
}






double s_1_FRAG_integrand(double x,struct parameter para){
  clock_t start = clock();
  
  return exp((2.0 - para.alpha)*x)/(1.0 + exp(x)); 

  clock_t end = clock();
  exetime.s_1_FRAG_integrand += (double)(end-start)/CLOCKS_PER_SEC;
}

double s_2_FRAG_integrand(double x,struct parameter para){
  clock_t start = clock();
  
  return - exp((2.0 - para.alpha)*x)/(1.0 + exp(x))*(x - 2.0*log(1 + exp(x))); 

  clock_t end = clock();
  exetime.s_2_FRAG_integrand += (double)(end-start)/CLOCKS_PER_SEC;
}

double s_3_FRAG_integrand(double x,struct parameter para){
  clock_t start = clock();
  
  return exp((1.0 - para.alpha)*x)/(1.0 + exp(x))*log(1.0 + exp(x));

  clock_t end = clock();
  exetime.s_2_FRAG_integrand += (double)(end-start)/CLOCKS_PER_SEC;
}





double s_1_FRAG(struct parameter para){
  clock_t start = clock();
  
  int n,n_max;
  double dx,sum=0.0,sum_pre=0.0;
  double ini=-36.0,fin=36.0;
  double eps=1.0E-7;

  n_max = 1;
  do{
    dx = (fin-ini)/(double)n_max;
    sum_pre = sum;
    sum=0;
    for(n=0;n<n_max;n++){
      sum += s_1_FRAG_trapezoid(n, dx, ini, para);
    }
    //printf("n_max=%d\n",n_max);
    n_max *= 2;
  }while(fabs(sum_pre-sum)>eps);

  return sum;

  clock_t end = clock();
  exetime.s_1_FRAG += (double)(end-start)/CLOCKS_PER_SEC;
}

double s_2_FRAG(struct parameter para){
  clock_t start = clock();
  
  int n,n_max;
  double dx,sum=0.0,sum_pre=0.0;
  double ini=-36.0,fin=36.0;
  double eps=1.0E-7;

  n_max = 1;
  do{
    dx = (fin-ini)/(double)n_max;
    sum_pre = sum;
    sum=0;
    for(n=0;n<n_max;n++){
      sum += s_2_FRAG_trapezoid(n, dx, ini, para);
    }
    //printf("n_max=%d\n",n_max);
    n_max *= 2;
  }while(fabs(sum_pre-sum)>eps);

  return sum;

  clock_t end = clock();
  exetime.s_2_FRAG += (double)(end-start)/CLOCKS_PER_SEC;
}

double s_3_FRAG(struct parameter para){
  clock_t start = clock();
  
  int n,n_max;
  double dx,sum=0.0,sum_pre=0.0;
  double ini=-36.0,fin=36.0;
  double eps=1.0E-7;

  n_max = 1;
  do{
    dx = (fin-ini)/(double)n_max;
    sum_pre = sum;
    sum=0;
    for(n=0;n<n_max;n++){
      sum += s_3_FRAG_trapezoid(n, dx, ini, para);
    }
    //printf("n_max=%d\n",n_max);
    n_max *= 2;
  }while(fabs(sum_pre-sum)>eps);

  return sum;

  clock_t end = clock();
  exetime.s_3_FRAG += (double)(end-start)/CLOCKS_PER_SEC;
}

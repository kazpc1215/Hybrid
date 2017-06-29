#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define GYOU 3

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


int main(void){
  int i;
  double time[1001];
  struct orbital_elements ele[1001];
  
  char buf[300];
  FILE *fp;
  char filename[100];
    


  for(i=1;i<=1000;i++){
    sprintf(filename,"./readdata/deltar_0010au_1000_relaxation/tracer%04d.dat",i);
    if((fp = fopen(filename,"r")) == NULL){
      fprintf(stderr,"Can't open %s.\n",filename);
      exit(-1);
    }
    
    fgets(buf,sizeof(buf),fp);  //読み飛ばし
    fgets(buf,sizeof(buf),fp);  //0yr
    fgets(buf,sizeof(buf),fp);  //10yr
    fgets(buf,sizeof(buf),fp);  //100yr
    fgets(buf,sizeof(buf),fp);  //1000yr 読む行
    sscanf(buf,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf",&time[i],&ele[i].ecc,&ele[i].axis,&ele[i].u,&ele[i].inc,&ele[i].Omega,&ele[i].omega,&ele[i].r_h,&ele[i].mass);

    //printf("i=%d\t%e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",i,time[i],ele[i].ecc,ele[i].axis,ele[i].u,ele[i].inc,ele[i].Omega,ele[i].omega,ele[i].r_h,ele[i].mass);
    fclose(fp);
  }


  //int number[1001]={};
  double r[1001]={};
  double mass[1001]={};
  double mass_tot=0.0;
  double sigma[1001]={};
  double sigma_ave=0.0;
  sprintf(filename,"./readdata/Posi_Mass_Frag3data.dat");
  if((fp = fopen(filename,"r")) == NULL){
    fprintf(stderr,"Can't open %s.\n",filename);
    exit(-1);
  }
  fgets(buf,sizeof(buf),fp);  //読み飛ばし
  for(i=1;i<=1000;i++){
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%*f\t%*d\t%*f\t%*f\t%*f\t%*f\t%lf\t%lf\t%*f\t%lf\t%*f\t%*d",&r[i],&mass[i],&sigma[i]);

    printf("i=%d\tr=%e\tmass=%e\tsigma=%e\n",i,r[i],mass[i],sigma[i]);
    sigma_ave += sigma[i];
  }
  fclose(fp);

  sigma_ave = sigma_ave/1000.0;

  printf("sigma_ave=%e\n",sigma_ave);

  
  for(i=1;i<=1000;i++){
    sigma[i] = sigma[i]*sigma_ave/sigma[i];
    mass[i] = mass[i]*sigma_ave/sigma[i];
    mass_tot += mass[i];
    printf("i=%d\tsigma=%e\tmass=%e\n",i,sigma[i],mass[i]);
  }
  printf("mass_tot=%e\n",mass_tot);

  for(i=1;i<=1000;i++){
    mass[i] = mass[i]*4.994E-4/mass_tot;
  }
  
  mass_tot=0.0;
  for(i=1;i<=1000;i++){
    mass_tot += mass[i];
    printf("i=%d\tmass=%e\n",i,mass[i]);
  }
  printf("mass_tot=%e\n",mass_tot);
  

}

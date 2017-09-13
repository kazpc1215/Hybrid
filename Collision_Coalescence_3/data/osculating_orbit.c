#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GYOU 10000
#define RH 10

/*
  struct orbital_elements{
  double t;
  double e;
  double axis;
  double u;
  double I;
  double OMEGA;
  double omega;
  double R_H;
  };
*/

int main(void){

  double t;
  double e;
  double axis;
  double u;
  double I;
  double OMEGA;
  double omega;
  
  double x,y,z;
  int i,j,n;
  double delta=M_PI/100.0;
  //struct orbital_elements ele;
  char buf[300];
  
  FILE *fp;
  char readfile[200];

  FILE *forbit;
  char datafile[200];


  
  for(n=1;n<=10;n++){  //惑星番号.

  
    
    sprintf(datafile,"./N10_t1E4_dt1yr_eta1E-2_%dHill/Planet%02d_osculating_orbit.dat",RH,n);  //書き出しファイル.
    if((forbit = fopen(datafile,"w")) == NULL){
      fprintf(stderr,"Can't open %s.\n",datafile);
      exit(-1);
    }
    fprintf(forbit,"#t\tx\ty\tz\n");
    fclose(forbit);
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    
    sprintf(readfile,"./N10_t1E4_dt1yr_eta1E-2_%dHill/Planet%02d.dat",RH,n);  //読み込みファイル.
    if((fp = fopen(readfile,"r")) == NULL){
      fprintf(stderr,"Can't open %s.\n",readfile);
      exit(-1);
    }

    
    fgets(buf,sizeof(buf),fp);  //読み飛ばし  1行目のコメント

    /*
    for(j=1;j<=9;j++){
      fgets(buf,sizeof(buf),fp);  //読み飛ばし
    }
    */


    if((forbit = fopen(datafile,"a")) == NULL){
      fprintf(stderr,"Can't open %s.\n",datafile);
      exit(-1);
    }
    
    i = 0;
    while(fgets(buf,sizeof(buf),fp) != NULL){
      sscanf(buf,"%lf\t%lf\t%lf\t%*lf\t%lf\t%lf\t%lf\t%*%lf\t%*lf\t%*lf",&t,&e,&axis,&I,&OMEGA,&omega);
      
      if(i>GYOU) break;
      
      
      fprintf(forbit,"0.0\t0.0\t0.0\t0.0\n");
      
      for(u=0.0;u<=2.0*M_PI;u+=delta){
	x = (cos(OMEGA)*cos(omega)-sin(OMEGA)*sin(omega)*cos(I))*axis*(cos(u)-e)+(-cos(OMEGA)*sin(omega)-sin(OMEGA)*cos(omega)*cos(I))*axis*sqrt(1.0-e*e)*sin(u);
	y = (sin(OMEGA)*cos(omega)+cos(OMEGA)*sin(omega)*cos(I))*axis*(cos(u)-e)+(-sin(OMEGA)*sin(omega)+cos(OMEGA)*cos(omega)*cos(I))*axis*sqrt(1.0-e*e)*sin(u);
	z = sin(omega)*sin(I)*axis*(cos(u)-e)+cos(omega)*sin(I)*axis*sqrt(1.0-e*e)*sin(u);
	
	fprintf(forbit,"%e\t%e\t%e\t%e\n",t,x,y,z);
      }
      

      /*
      for(j=1;j<=9;j++){
	fgets(buf,sizeof(buf),fp);  //読み飛ばし
      }
      */
    
      //printf("i=%d\tn=%d\tt=%e\te=%e\ta=%e\tI=%e\n",i,n,t,e,axis,I);

      fprintf(forbit,"\n\n");
      
      i++;
    }

    
    fclose(forbit);
    
    fclose(fp);

  }
}


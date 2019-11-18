#include <stdio.h>
#include <math.h>
#define PI 3.1415926
int main()
{
  int n,opt;
  float l=0.5;
  double N2, P2, S2,r2,R2,r3,R3;
  double rn, Rn,rn1,Rn1;
  double  inf, sup,deltaInf,deltaSup;
  N2 = 1/(2*tan(3.14/4));
  r2 = l*N2;
  P2 = l*4;
  S2 = P2*r2/2;
  R2 = sqrt(r2*r2 +l*l/4);
  printf(" N = %f, r = %f, P =%f, S=%f,R=%f \n", N2,r2,P2,S2,R2);
  n=2;
  rn=1./4.;
  Rn=sqrt(2.)/4;
  //for(int i=0; i< 50; i++){
  do{
    inf = 1./Rn1;
    sup = 1./rn1;
    deltaInf=fabs(inf-PI);
    deltaSup=fabs(sup-PI);
    printf("%d %f %f %f  %f %f %f \n",n, rn1,Rn1,inf, sup,deltaInf,deltaSup);
    rn1=(rn+Rn)/2;
    Rn1 = sqrt(rn1*Rn);
    rn=rn1;
    Rn=Rn1;
    n++;
  }while(deltaInf>0.0000001 || deltaSup>0.0000001);
  //   }
  return 0;
}


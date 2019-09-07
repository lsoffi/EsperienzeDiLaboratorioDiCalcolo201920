#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char** argv)
{
  int i, Np=100;
  double fx, x, dx, sum=0.0, xmin=-15.0, xmax=15.0;
  x=xmin;
  fprintf(stderr,"0/0=%.15G\n", sin(0.0)/0.0);
  fprintf(stderr,"1/0=%.15G\n", 1.0/0.0);
  dx = (xmax-xmin)/(Np-1);// poiché ho 3 punti e due intervalli
  for (i=0; i < Np; i++)
    {
      if (x==0.0)
        fx=1.0;
      else
        fx=sin(x)/x;
      printf("%.7f %.7f\n", x, fx);
      x+=dx;
    }
  return 0;
}

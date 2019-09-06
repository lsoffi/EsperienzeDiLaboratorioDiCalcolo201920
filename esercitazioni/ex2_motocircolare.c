#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char **argv)
{
  double R, w, t, x, y;
  R=6.2; /* m */
  w=0.1; /* rad/s */
  t = 0.0; /* s */
  x = R*cos(w*t);
  y = R*sin(w*t);
  printf("t=%.4f x=%.5f y=%.5f\n", t, x, y);
  t = 0.5; /* s */
  x = R*cos(w*t);
  y = R*sin(w*t);
  printf("t=%.4f x=%.5f y=%.5f\n", t, x, y);
  t = 10; /* s */
  x = R*cos(w*t);
  y = R*sin(w*t);
  printf("t=%.4f x=%.5f y=%.5f\n", t, x, y);
  t = 10; /* s */
  x = R*cos(w*t);
  y = R*sin(w*t);
  printf("t=%.4f x=%.5f y=%.5f\n", t, x, y);
  /* blocco interattivo */
  printf("Immetti il tempo t: ");
  scanf("%lf", &t);
  x = R*cos(w*t);
  y = R*sin(w*t);
  //printf("(x,y)= %.5f,%.5f\n", x, y);
  printf("%.5f %.5f %.5f\n", t, x, y);
  return 0;// dice al sistema operativo che non ci sono errori
}


#include<stdio.h>  // scanf, printf
#include<stdlib.h> // exit()
#include<math.h>    // exp, sin, cos, ...

int main(int argc, char** argv)
{
  double a;
  printf("Immetti un numero:");
  scanf("%lf",&a);
  printf("sin(%.7f)=%.7f\n", a, sin(a));
  printf("cos(%.7f)=%.7f\n", a, cos(a));
  printf("sqrt(%.7f)=%.7f\n", a, sqrt(a));       
}

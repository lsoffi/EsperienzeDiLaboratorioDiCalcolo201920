#include<stdio.h>
int main(int argc, char **argv)
{
  double a = 2/3, c=3000000000;
  float b = 1.0/3; // casting implicito
  int i=5, l=-5;
  printf("a=%f b=%f  c=%g\n", a, b, c); 
  printf("i=%d l=%d l=%ud\n", i, l, l); // casting implicito da int ad unsigned int

  printf("Immetti un double:");
  scanf("%lf", &a);
  printf("Hai immesso a=%f\n", a);
  printf("Immetti un intero:");
  scanf("%d", &i);
  printf("Hai immesso i=%d\n", i); 
  return 0;
}

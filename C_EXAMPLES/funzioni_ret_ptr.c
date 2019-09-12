#include<stdlib.h>
#include<stdio.h>
int* f(int *p);
int main()
{
  int a[2]={1,2};
  int *p;
  printf("Prima a[0]=%d a[1]=%d\n", a[0], a[1]);
  p = f(a); // passaggio di un vettore
  printf("*p=%d\n", *p);
  printf("Dopo a[0]=%d a[1]=%d\n", a[0], a[1]);
}
int* f(int *p) 
{
  p++;
  *p=3;
  return p;
}

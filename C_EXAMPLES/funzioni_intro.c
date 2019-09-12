#include<stdlib.h>
#include<stdio.h>
int f(int);//dichiarazione ovvero prototipo
int main()
{
  int a=1;
  printf("a=%d f(a)=%d\n", a, f(a));
}
int f(int a) // di default è int
{
  // corpo della funzione
  int b=2;
  return a+1+b;
}

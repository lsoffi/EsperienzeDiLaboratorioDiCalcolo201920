#include<stdlib.h>
#include<stdio.h>
void f(int a);//dichiarazioni di funzioni ovvero prototipi
void g(int *a);
int main()
{
  int a=1;
  printf("prima a=%d\n", a);
  f(a); // passaggio per valore
  printf("dopo chiamata a f() a=%d\n", a);
  g(&a);
  printf("dopo chiamata a g() a=%d\n", a);
}
void f(int a) // di default è int
{
  // corpo della funzione
  a = a+1;
}
void g(int *a)
{
  *a = 2;
}

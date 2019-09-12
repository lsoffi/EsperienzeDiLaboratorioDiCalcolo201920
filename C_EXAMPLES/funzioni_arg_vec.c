#include<stdlib.h>
#include<stdio.h>
void f(int *a);
int main()
{
  int i;
  int a[5]={1,2,3,4,5};

  printf("Prima della chiamata a f:"); 
  for (i=0; i < 5; i++)
    printf(" %d", a[i]);
  printf("\n");

  f(a); // passaggio di un vettore

  printf("Dopo la chiamata a f:"); 
  for (i=0; i < 5; i++)
    printf(" %d", a[i]);
  printf("\n");
}
void f(int *a) 
{
  int i;
  for (i=0; i < 5; i++)
    a[i]++;
}

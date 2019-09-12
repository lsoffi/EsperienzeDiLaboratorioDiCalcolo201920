#include<stdlib.h>
#include<stdio.h>
#define N 2
#define M 3
void f(int p[N][M]);
void g(int p[N][M], void (*f)(int p[N][M]));
int main()
{
  int i, j;
  int a[N][M]={{1,2,3},{4,5,6}};
  printf("Prima:\n");
  for (i=0; i < 2; i++)
    {
      for (j=0; j < N; j++)
	{
	  printf(" %5d", a[i][j]);
	}
      printf("\n");
    }
  g(a, f); // passaggio di un vettore
  printf("Dopo:\n");
  for (i=0; i < 2; i++)
    {
      for (j=0; j < N; j++)
	{
	  printf(" %5d", a[i][j]);
	}
      printf("\n");
    }
}
void f(int p[N][M]) 
{
  p[0][0] = 10;
}

void g(int p[N][M], void (*f)(int p[N][M]))
{
  f(p);
}

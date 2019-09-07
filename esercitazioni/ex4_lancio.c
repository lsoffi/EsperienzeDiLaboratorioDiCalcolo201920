#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char *argv[])
{
  const int nmax=36; 
  int nocc[36], i, n;
  srand(0);
  for (i=0; i < nmax; i++)
    nocc[i]=0;

  n=rand()%nmax + 1;
  printf("%2d ",n);
  if (n%2==0)
    {
      printf("E ");
    }
  else
    {
      printf("O ");
    }
  if (n <= 18)
    {
      printf("M\n");
    }
  else 
    {
      printf("P\n");
    }
  return 0;
}

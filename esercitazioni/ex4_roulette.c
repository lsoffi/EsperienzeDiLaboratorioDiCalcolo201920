#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char *argv[])
{
  const int nmax=36, N=100000000; 
  int nocc[36];
  int i, n, nE=0, nM=0;
  srand(0);

  for (int i = 0; i < 36; i++) {
    nocc[i]=0;
  }
  for (i = 0; i < N; ++i) {
    n=rand()%nmax + 1;
    nocc[n] += 1;
    if (n%2==0)
      {
        nE++;
      }
    if (n <= 18)
      {
        nM++;
      }
  } 
  printf("frequenza E=%.7f; frequenza M=%.7f\n", 
         ((double)nE)/N, ((double)nM)/N);
  printf("frequenza O=%.7f; frequenza P=%.7f\n", 
         ((double)(N-nE))/N, ((double)(N-nM))/N);

  for (int i = 0; i < 36; i++) {
    printf("%d %.7f\n", i, ((double)nocc[i])/N);
  }
  return 0;
}

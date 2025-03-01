#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define NMAX 1000
int lancioDado()
{
  return rand()%6+1;
}


int main()
{
  int k, nl, n=10, i, Nlanci=1000, successi[10]={0}, succ=0;
  FILE *f;
  double sum=0;
  srand(time(0));

  if (n >= NMAX)
    {
      printf("[main:ERRORE] n troppo grande incrementare NMAX nel codice!\n");
      exit(1);
    }
  printf("ok Nlanci=%d n=%d\n", Nlanci, n);

  for (nl=0; nl < Nlanci; nl++)
    {
      succ=0;
      for (i = 1; i <= n; ++i) {
        k = lancioDado();
        if (k==3)
          succ++;
      }
      successi[succ]+=1;
      printf("n = %d, successi[%d] = %d, nl=%d \n", n, succ, successi[succ], nl);
    }


  // scrivo su file l'istogramma
  f=fopen("frequenzeDadi.dat", "w+"); 
  for (i = 0; i <= n; ++i) {
    double num = (double)successi[i];
    num/=1000.;
    printf("%d %.7f\n", i, num);
    fprintf(f,"%d %.7f\n", i, num);
  }
  fclose(f);
  return 0;
}

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
unsigned long long int fattoriale(int n)
{
  // fattoriale
  unsigned long long int i;
  unsigned long long int p = 1;
  for (i = 1; i <= n; i++) {
    p *= i;
  }
  return p;
}
double binomiale(int k, int n, double p)
{
  double P;
  if (k > n)
    {
      printf("[ERRORE:binomiale] k (=%d) deve essere minore o uguale a n (=%d)!", k, n);
      exit(1);
    }
  P = pow(p,k)*pow(1.0-p,n-k)*fattoriale(n)/fattoriale(n-k)/fattoriale(k);
  return P;
}

int main()
{
  int k, n;
  double p;
  double bin, sum;
  FILE *f;
  char fn[256];

  do{
    printf("Inserisci n: \n");
    scanf("%d", &n);// per grandi n tende ad una gaussiana
  }while(n<2 || n> 50);
  do{
  printf("Inserisci p: \n");
  } while(p>1. || p<0.);
  scanf("%lf", &p);// per grandi n tende ad una gaussiana

  printf("ok n=%d p=%.7f\n", n, p);
  sprintf(fn,"output_%d.dat", n);
  f=fopen(fn,"w+");
  for (k = 0; k <= n; ++k) {
    bin = binomiale(k, n, p);
    sum+=bin;
    printf("%d %.7f\n", k, bin);
    fprintf(f, "%d %.7f\n", k, bin);
  }
  printf("La condizione di normalizzazione e' sum = %lf \n", sum);
  fclose(f);
  return 0;
}

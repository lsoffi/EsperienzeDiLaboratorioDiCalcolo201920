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
void inserimento(char *msg, char *fmt, void *v)
{
  int fine, res, c;
  fine=0;
  while (!fine)
    {
      printf("%s", msg);
      fine=1;
      res=scanf(fmt, v);
      if (ferror(stdin)||feof(stdin))
        {
          // qui ci arriva se si preme CTRL-D = EOF
          printf("\n");
          clearerr(stdin);
          fine=0;
          continue;
        }
          
      if (res < 1)
        {
          printf("Problema nella conversione\n");
          fine=0;
        }
      while ((c=getchar())!='\n'); // svuota il buffer di tutti i caratteri eccetto '\n'=newline
    }
}
int main(int argc, char *argv[])
{
  int k, n;
  double p;
  FILE *f;
  char fn[256];

  inserimento("Inserisci n: ", "%d", &n);// per grandi n tende ad una gaussiana
  inserimento("Inserisci p: ", "%lf", &p);  
  printf("ok n=%d p=%.7f\n", n, p);
  sprintf(fn,"bernoulli_%d.dat", n);
  f=fopen(fn,"w+");
  for (k = 0; k <= n; ++k) {
    fprintf(f, "%d %.7f\n", k, binomiale(k, n, p));
  }
  fclose(f);
  return 0;
}

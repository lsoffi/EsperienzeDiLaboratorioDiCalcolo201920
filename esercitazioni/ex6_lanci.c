#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
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
int lancio_dado()
{
  return rand()%6+1;
}
#define NMAX 1000
double isto[NMAX];
int main(int argc, char *argv[])
{
  int k, nl, n, i, Nlanci, successi=0;
  FILE *f;
  double sum=0;
  srand(time(0));
  for (i=0; i < NMAX; i++)
    {
      isto[i] = 0;
    }
  inserimento("Inserisci il numero di lanci di 6 dadi: ", "%d", &Nlanci); 
  inserimento("Inserisci n: ", "%d", &n);// per grandi n tende ad una gaussiana
  if (n >= NMAX)
    {
      printf("[main:ERRORE] n troppo grande incrementare NMAX nel codice!\n");
      exit(1);
    }
  printf("ok Nlanci=%d n=%d\n", Nlanci, n);

  for (nl=0; nl < Nlanci; nl++)
    {
      successi=0;
      for (i = 1; i <= n; ++i) {
        k = lancio_dado();
        if (k==3)
          successi++;
      }
      isto[successi] += 1.0;
    }

  // rinormalizzo l'istogramma
  for (i = 0; i <= n; ++i) {
    sum += isto[i];
  }
  for (i = 0; i <= n; ++i) {
    isto[i] /= sum;
  }

  // scrivo su file l'istogramma
  f=fopen("istogramma.dat", "w+"); 
  for (i = 0; i <= n; ++i) {
    fprintf(f,"%d %.7f\n", i, isto[i]);
  }
  fclose(f);
  return 0;
}

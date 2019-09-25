#include<stdio.h> // dichiarazioni di printf e scanf

// definizione nel codice della macro, ma possono
// anche essere definite dalla riga di comando in fase
// di compilazione

#define STAMPA_SEP 0 // oppure da riga di comando gcc -D STIMA_SEP=1 (o 0)
#define CHIEDI_INTERO 
// oppure #undef CHIEDI_INTERO oppure 
// da riga di comando: gcc -D CHIEDI_INTERO 

// definisco la macro K (valore da assegnare ad a, vedi sotto)
#define K 2/3

int main(int argc, char **argv)
{
  double a = K, c=3000000000;
  float b = 1.0/3; // casting implicito
  int i=5, l=-5;
  printf("a=%f b=%f  c=%g\n", a, b, c); 
  printf("i=%d l=%d l=%ud\n", i, l, l); // casting implicito da int ad unsigned int --> C è "weakly typed"!!

#if STAMPA_SEP==1
  printf("---------------------\n");
#endif
#if STAMPA_SEP>1
  printf("*********************\n");
#endif
  printf("Immetti un double:");
  scanf("%lf", &a);
  printf("Hai immesso a=%f\n", a);
#ifdef CHIEDI_INTERO // o anche #if defined(CHIEDI_INTERO)
  printf("Immetti un intero:");
  scanf("%d", &i);
  printf("Hai immesso i=%d\n", i); 
#endif

#if 1
  printf("fine1\n");
#else
  printf("fine2\n");
#endif

  return 0;
}

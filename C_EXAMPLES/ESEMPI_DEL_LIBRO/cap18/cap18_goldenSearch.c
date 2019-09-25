#include <stdio.h>
#include <math.h>

#define LEFT  0
#define RIGHT 1

#define W 0.38197

double F(double x);
double dF(double x);
double goldenSearch(double a, double b, double epsilon);

int main() {
  double a, b, epsilon, xmin;

  /* Questo programma cerca i minimi di una funziona F(x) in un intervallo
    (a, c) */

  printf("Inserisci l'intervallo di ricerca del minimo: ");
  scanf("%lf %lf", &a, &b);

  if ((F(a + W * (b-a)) > F(a))||(F(a + W * (b-a)) > F(b))) {
    printf("Impossibile trovare un minimo...\n");
    exit(-1);
  }

  printf("Inserisci la tolleranza: ");
  scanf("%lf", &epsilon);

  xmin = goldenSearch(a, b, epsilon);

  printf("Il minimo e' stato trovato in   : %f\n", xmin);
  printf("In questo punto la funzione vale: %f\n", F(xmin));
  printf("In questo punto la derivata vale: %f\n", dF(xmin));
}

double F(double x) {
  return x * cos(x);
}

double dF(double x) {
  return cos(x) - x * sin(x);
}

double goldenSearch(double a, double b, double epsilon) {
  double xnp1 = a + W * (b - a);
  double xn;
  char larger;

  do {
    xn = a + W * (b - a);
    if ((xn -a) > (b - xn)) {
      xnp1 = a + W * (xn - a);
    } else {
      xnp1 = xn + W * (b - xn);
    }
    printf("%f %f %f ", a, b, xn);
    if (F(xnp1) > F(xn)) {
      a = xn;
    } else {
      b = xnp1;
    }
    printf("%f\n", xn);
  } while (fabs(xnp1-xn) > epsilon);
  return 0.5 * (xn + xnp1);
}

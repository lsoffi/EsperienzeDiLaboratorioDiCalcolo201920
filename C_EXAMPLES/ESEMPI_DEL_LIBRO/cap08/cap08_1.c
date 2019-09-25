#include <stdio.h>
#include <math.h>

#define N 100

double chi2(double *x, double *y, double *sigma, double *pars, int n);

void fit(double *x, double *y, double *sigma, double *pars, int n);

void printErr(char *msg, double a, double delta);

main() {
  double x[N], y[N], sigma[N], p[4];
  int i, n = 0;

  while ((n <= 0) || (n >= N)) {
    printf("Quanti sono i dati? ");
    scanf("%d", &n);
  }
  for (i = 0; i < n; i++) {
    printf("Inserire x[%d], y[%d] e sigma[%d]: ", i, i, i);
    scanf("%lf %lf %lf", &x[i], &y[i], &sigma[i]);
  }
  fit(x, y, sigma, p, n);
  printErr("A = ", p[0], p[1]);
  printErr("B = ", p[2], p[3]);
  printf("X^2 = %f (%f/DoF)\n", chi2(x, y, sigma, p, n), 
	 chi2(x, y, sigma, p, n) / (n - 2));
}

double chi2(double *x, double *y, double *sigma, double *pars, int n) {
  double chi2 = 0.;
  int i;

  for (i = 0; i < n; i++) {
    chi2 += pow((y[i] - pars[0] - pars[2] * x[i]), 2.) / (sigma[i] * sigma[i]);
  }
  return chi2;
}


void fit(double *x, double *y, double *sigma, double *pars, int n) {
  double Sx = 0., Sy = 0., S = 0., Stt = 0., s2;
  double A = 0., B = 0., sigmaA, sigmaB, chi2 = 0.;
  double t[N];
  int i;
  for (i = 0; i < n; i++) {
    s2 = sigma[i] * sigma[i];
    Sx += x[i] / s2;
    Sy += y[i] / s2;
    S  += 1./ s2;
  }
  for (i = 0; i < n ; i++) {
    t[i] = (x[i] - Sx / S) / sigma[i];
    Stt += t[i] * t[i];
    B += t[i] * y[i] / sigma[i];
  }
  B /= Stt;
  A = (Sy - Sx * B) / S;
  sigmaA = sqrt((1. + Sx * Sx / (S * Stt)) / S);
  sigmaB = 1./ Stt;
  pars[0] = A;
  pars[1] = sigmaA;
  pars[2] = B;
  pars[3] = sigmaB;
}


void printErr(char *msg, double a, double delta) {
  /* determina l'ordine di grandezza dell'errore */
  int n = (int)rint(log(delta)/log(10));
  char fmt[255];
  sprintf(fmt, "%%s %%f +- %%f\n");
  /* conserva -(n+1) cifre significative */
  if (n < 0) {
    n--;
    sprintf(fmt, "%%s %%.%df +- %%.%df\n", -n, -n);
  }
  /* stampa il messaggio, a e il suo errore */
  printf(fmt, msg, a, delta);
}


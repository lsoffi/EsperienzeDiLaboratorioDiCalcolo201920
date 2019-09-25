#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void copy(double *src, double *dest, int n) {
  /* copia il vettore src nel vettore dest */
  int i;
  for (i = 0; i < n; i++) {
    dest[i] = src[i];
  }
}
 
void add(double *x, double lambda, double *u, int n) {
  /* aggiunge a x[i] il prodotto lambda*u[i] */
  int i;
  for (i = 0; i < n; i++) {
    x[i] += lambda*u[i];
  }
}

double input(double *x, int n) {
  int i;
  double epsilon;

  printf("Inserisci le coordinate del punto iniziale:\n");
  for (i = 0; i< n; i++) {
    printf("x[%2d] = ", i);
    scanf("%lf", &x[i]);
  }
  printf("Inserisci la precisione richiesta: ");
  scanf("%lf", &epsilon);
  return epsilon;
}

double derivative(double (*f)(double *, int), double *x, int n, int m,
                  double epsilon) {
  /* 
     restituisce la derivata prima della funzione f rispetto a x[m],
     calcolata in x.
     la derivata e' calcolata come rapporto incrementale
  */
  double der = -(*f)(x, n);
  double xold = x[m];
  x[m] += epsilon;
  der += (*f)(x, n);
  der /= epsilon;
  x[m] = xold;
  return der;
}

double dFdLambda(double (*f)(double *, int), double *x, double *u, int n, 
		 double epsilon) {
  /* calcola la derivata di f(x+lambda*u) rispetto a lambda nel punto x */
  double *xsave = (double *)calloc(n, sizeof(double));
  double der = 0.;
  /* salva la posizione corrente */
  copy(x, xsave, n);
  der -= (*f)(x, n);
  /* calcola x + epsilon*u */
  add(x, epsilon, u, n);
  /* calcola la derivata */
  der += (*f)(x, n);
  der /= epsilon;
  /* rimette a posto le coordinate */
  copy(xsave, x, n);
  free(xsave);
  return der;
}

double dF2dLambda2(double (*f)(double *, int), double *x, double *u,
		   int n, double epsilon) {
  /* calcola la derivata seconda di f(x+lambda*u) rispetto a lambda
     nel punto */
  double der1, der2, der;
  double *xsave = (double *)calloc(n, sizeof(double));
  /* salva la posizione corrente */
  copy(x, xsave, n);
  der1 = dFdLambda((*f), x, u, n, epsilon);
  /* calcola x + epsilon*u */
  add(x, epsilon, u, n);
  der2 = dFdLambda((*f), x, u, n, epsilon);
  der = (der2 - der1) / epsilon;
  /* rimette a posto le coordinate */
  copy(xsave, x, n);
  free(xsave);
  return der;
}

void gradient(double (*f)(double *, int), double *x, double *grad, int n,
              double epsilon) {
  /* calcola il gradiente di x e lo restituisce in grad */
  int i;
  for (i = 0; i < n; i++) {
    grad[i] = derivative((*f), x, n, i, epsilon);
  }
}

void opposite(double *x, int n) {
  /* cambia x in -x */
  int i;
  for (i = 0; i < n; i++) {
    x[i] = -x[i];
  }
}

double norm(double *a, double *b, int n) {
  /* restituisce sqrt(|b-a|^2) */
  double d = 0.;
  int i;
  for (i = 0; i < n; i++) {
    d += (a[i]-b[i])*(a[i]-b[i]);
  }
  return sqrt(d);
}

void linmin(double (*f)(double *, int), double *x, double *u, int n, 
	    double epsilon) {
  /*
    Minimizza la funzione f di n variabili lungo la direzione u.
    Restituisce il vettore delle coordinate x modificato
  */
  double derA, derB, derC;
  double lambda = epsilon, lambdamin, lambdamax;
  double *xsave = (double *)calloc(n, sizeof(double)); 
  /* salva la posizione corrente */
  copy(x, xsave, n); 
  /* trova due valori di lambda per cui le derivate sono discordi */
  derA = dFdLambda((*f), x, u, n, epsilon);
  derC = derA;
  while ((derA * derC) >= 0) { 
    copy(xsave, x, n);
    add(x, lambda, u, n);
    derC = dFdLambda((*f), x, u, n, epsilon);
    lambda *= 2.;
  }
  /* ora usa il metodo di bisezione per risolvere f'(x) = 0 */
  lambdamin = 0;
  lambdamax = lambda;
  lambda = 0.5 *(lambdamin + lambdamax);
  do {
    copy(xsave, x, n);
    add(x, lambdamin, u, n);
    derA = dFdLambda((*f), x, u, n, epsilon);
    copy(xsave, x, n);
    add(x, lambda, u, n);
    derB = dFdLambda((*f), x, u, n, epsilon);
    copy(xsave, x, n);
    add(x, lambdamax, u, n);
    derC = dFdLambda((*f), x, u, n, epsilon);
    if ((derA * derB) > 0) {
      lambdamin = lambda;
    } else if ((derA * derB) < 0) {
      lambdamax = lambda;
    } else {
      lambdamin = lambdamax = lambda;
    }
    lambda = 0.5 *(lambdamin + lambdamax);
  } while (fabs(lambdamin-lambdamax) > epsilon);
  /* calcola la posizione raggiunta */
  copy(xsave, x, n);
  add(x, lambda, u, n);
  free(xsave);
}

void dump(double *x, int n, int count, ...) {
  int i;
  va_list optionalParameters;

  for (i = 0; i < n; i++) {
    printf("%+f ", x[i]);
  }
  va_start(optionalParameters, count);
  for (i = 0; i < count; i++) {
    printf("%+f ", va_arg(optionalParameters, double));
  }
  va_end(optionalParameters);
}

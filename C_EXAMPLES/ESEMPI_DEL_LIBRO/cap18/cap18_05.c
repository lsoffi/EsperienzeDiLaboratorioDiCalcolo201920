#include <stdio.h>
#include <stdlib.h>
#include <minimizationLib.h>

double myFunction(double *x, int n) {
  return x[0]*x[0]+4*x[1]*x[1];
}

double scalar(double *a, double *b, int n) {
  double S = 0.;
  int i;
  for (i = 0; i < n; i++) {
    S += a[i]*b[i];
  }
  return S;
}

#define N 2

main() {
  double x[N] = {2., 1.}, grad[N], xold[N], gold[N], h[N] = {0.}, 
			    hold[N] = {0.};
  double gamma = 0., epsilon, g2;
  int i;

  epsilon = input(x, N);
  do {
    copy(x, xold, N);
    gradient(myFunction, x, grad, N, epsilon);
    opposite(grad, N);
    copy(grad, h, N);
    if (g2 = scalar(gold, gold, N)) {
      gamma = scalar(grad, grad, N) / g2;
    }
    add(h, gamma, hold, N);
    dump(h, N, 0);
    dump(x, N, 1, myFunction(x, N));
    printf("\n");
    linmin(myFunction, x, h, N, epsilon);
    copy(h, hold, N);
    copy(grad, gold, N);
  } while (norm(x, xold, N) > epsilon);
}

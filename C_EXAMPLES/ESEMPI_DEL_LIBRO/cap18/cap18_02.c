#include <stdio.h>
#include <math.h>
#include <minimizationLib.h>
#include <stdlib.h>

#define N 2

double myFunction(double *x, int n) {
  return x[0]*x[0]+4*x[1]*x[1];
}

main() {
  double x[N], grad[N], xold[N];
  double epsilon;
  int i;

  epsilon = input(x, N);
  do {
    copy(x, xold, N);
    gradient(myFunction, x, grad, N, epsilon);
    opposite(grad, N);
    dump(grad, N, 0);
    dump(x, N, 1, myFunction(x, N));
    printf("\n");
    linmin(myFunction, x, grad, N, epsilon);
  } while (norm(x, xold, N) > epsilon);
}

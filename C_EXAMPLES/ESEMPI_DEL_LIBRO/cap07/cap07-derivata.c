#include <stdio.h>
#include <math.h>
double func(double);
double derivative(double (*)(double), double, double);

main() {
  double epsilon = 1.;
  printf("epsilon      derivata\n\n");
  while (epsilon > 1.e-18) {
    printf("%e %f\n", epsilon, derivative(func, 1., epsilon));
    epsilon /= 10.;
  }
}
double func(double x) {
  return sqrt(x);
}

double derivative(double (*f)(double), double x, double epsilon) {
  return ( f(x + epsilon) - f(x) ) / epsilon;
}

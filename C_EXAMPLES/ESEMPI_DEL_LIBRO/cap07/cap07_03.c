#include <stdio.h>

double squareSum(double, double);

main() {
  double x, y, q;
  int k;
  x = 3.14;
  y = 2.;
  q = squareSum(x, y);
  printf(" prima somma dei quadrati = %f\n", q);
  q = squareSum(5, 2 * 2);
  printf(" seconda somma dei quadrati = %f\n", q);
  k = 2;
  q = squareSum(x, k);
  printf(" terza somma dei quadrati = %f\n", q);
}

double squareSum(double a, double b) {
  return (a * a + b * b);
}

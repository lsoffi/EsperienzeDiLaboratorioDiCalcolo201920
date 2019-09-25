#include <stdio.h>

void swap(double *, double *);

main() {
  double x, y;
  x = 3.14;
  y = 2.72;
  printf(" prima dello scambio, x = %f, y = %f\n", x, y);
  swap(&x, &y);
  printf(" dopo lo scambio, x = %f, y = %f\n", x, y);
}

void swap(double *a, double *b) {
  double temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

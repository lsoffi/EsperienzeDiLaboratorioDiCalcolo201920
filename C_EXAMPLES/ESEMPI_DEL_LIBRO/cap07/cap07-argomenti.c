#include <stdio.h>

double squareDiff(double, double);

main() {
  double a, b, q;
  a = 4.;
  b = 5.;
  q = squareDiff(b, a);
  printf(" differenza dei quadrati = %f\n", q);
  q = squareDiff(a, b);
  printf(" differenza dei quadrati scambiata = %f\n", q);
}

double squareDiff(double a, double b) {
  return (a * a - b * b);
} 

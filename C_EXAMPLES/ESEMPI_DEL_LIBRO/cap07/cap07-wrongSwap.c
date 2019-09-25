#include <stdio.h>

void wrongSwap(double, double);

main() {
  double x, y;
  x = 3.14;
  y = 2.72;  
  printf(" prima dello scambio, x = %f, y = %f\n", x, y);
  wrongSwap(x, y);
  printf(" dopo lo scambio, x = %f, y = %f\n", x, y);
}

void wrongSwap(double a, double b) {
  double temp;
  temp = a;
  a = b;
  b = temp;
} 

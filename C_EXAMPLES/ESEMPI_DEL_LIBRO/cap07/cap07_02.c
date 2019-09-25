#include <stdio.h>
main() {
  int a, b;
  a = 137;
  b = 2;
  {
    int x;
    double a;
    a = 3.14;
    x = 137;
    printf(" blocco interno a = %f, b = %d, x = %d\n", a, b, x);
  }
  printf(" blocco esterno a = %d, b = %d\n", a, b);
}

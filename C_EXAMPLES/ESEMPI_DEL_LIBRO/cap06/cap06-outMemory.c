#include <stdio.h>
#define MY_OUT_MEMORY 1
main() {
  double a, b, *pd;  
  a = 3.14;
  pd = &a;
  pd++;
  b = *(pd - MY_OUT_MEMORY);
  printf ("Otteniamo a = %f, b = %f, a, b);
}

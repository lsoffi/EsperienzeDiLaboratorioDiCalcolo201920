#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1000000
#define R 1.

#define V (4./3.*M_PI*R*R*R/8.)

main() {
  double x, y, z;
  int i = 0, k = 0;
  for (i = 0; i < N; i++) {
    x = 2 * (double)lrand48() / RAND_MAX;
    y = 2 * (double)lrand48() / RAND_MAX;
    z = 2 * (double)lrand48() / RAND_MAX;
    if ((x * x + y * y + z * z) < (R * R)) {
      k++;
    }
  }
  printf("%f %f %f\n", V, 8.*k/N, V-8.*k/N);
}

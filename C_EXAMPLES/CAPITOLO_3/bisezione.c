#include <math.h>
#include <stdio.h>

#define EPSILON 1.e-5

int main(int argc, char** argv) {
  double a = 0., b = M_PI, c;
  double delta = fabs(a - b);
  int i = 1;
  printf("Questo programma trova la soluzione "
         "dell'equazione cos(x)=0 in (0, PI)\n");
  while (delta > EPSILON) {
    double p;
    c = 0.5 * (a + b);
    p = cos(a) * cos(c);
    if (p > 0.) {
      a = c;
    } else if (p < 0.) {
      b = c;
    } else { 
      a = b = c; /* soluzione esatta */
    }
    printf("Iterazione n. %d: x = %f\n", i++, 
	   0.5 * (a + b));
    delta = fabs(a - b);
  }
  printf("La soluzione trovata vale: %f\n", c);
  printf("La soluzione vera vale   : %f\n", 0.5 * M_PI);
  printf("La differenza vale       : %e\n", 
         fabs(0.5 * M_PI - c));
  return 0;
}

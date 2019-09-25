#include <stdio.h>

main() {
   double tc, tf, offset, conv;
   
   offset = 32.;
   conv = 5./ 9.;
   printf("Valore in gradi Fahrenheit= ");
   scanf("%lf",&tf);
   tc = (tf - offset) * conv;
   printf("Valore in gradi celsius= %f",tc);
}

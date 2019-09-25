#include <stdio.h>

#define TF2TC 

main() {
   double tc, tf, offset, conv;
  
   offset = 32.;
#ifdef TF2TC   
   conv = 5. / 9.;
   printf("Valore in gradi Fahrenheit= ");
   scanf("%lf",&tf);
   tc = (tf - offset) * conv;
   printf("Valore in gradi celsius= %f\n",tc);
#endif
#ifndef TF2TC
   conv = 9. / 5.;
   printf("Valore in gradi celsius= ");
   scanf("%lf",&tc);
   tf = tc * conv + offset;
   printf("Valore in gradi Fahrenheit= %f\n",tf);
#endif
}

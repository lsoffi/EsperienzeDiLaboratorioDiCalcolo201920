
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Qui p(x) proporzionale a x*x fra 0 ed 1 e zero altrove */
/*     n(x) uniforme fra 0 ed 1 e zero altrove */

main(){
  long int i, norm = 0, tot = 10000000;
  double ave = 0.0, ave2 = 0.0;
  srand(874531);
  for(i = 0; i < tot; i++) {
    double x, y, z;
    x = (double)rand() / (double)RAND_MAX;
    z = (double)rand() / (double)RAND_MAX;
    y = x * x;
    if(z <= y){/* qui accettiamo il numero */
      norm++;
      ave += x;
      ave2 += y;
    }
  }
  /* stampiamo quattro momenti */
  printf("N = %d\n I(x*x dx) = %g\n I(x*x x dx) = %g\n"
	 " I(x*x x*x dx) = %g\n",
	 tot, (double)norm / (double)tot,
	 ave / (double)tot, ave2 / (double)tot);
}

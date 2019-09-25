#include <stdlib.h>
#include <time.h>
#define MAX 1000

main() {
   double x[MAX];
   int seed;
   
   seed = time(0);
   srand48(seed);

   for (i = 0; i < MAX; i++) {
      x[i] = (double) lrand48() / RAND_MAX;
   }
}

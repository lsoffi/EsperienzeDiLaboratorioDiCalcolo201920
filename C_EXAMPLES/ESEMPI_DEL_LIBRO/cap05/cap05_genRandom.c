#include <stdlib.h>
#define MAX 1000

main() {
   double x[MAX];

   for (i = 0; i < MAX; i++) {
      x[i] = (double) rand() / RAND_MAX;
   }
}

#include <stdio.h>
#define LEN 5

main() {
  float data[LEN], *pd;
  int i;
  pd = &data[0];
  for (i = 0; i < LEN; i++) {
    printf(" pd + %d = %p, &data[%d] = %p\n", 
    i, data + i, i, &data[i]);
  }
}

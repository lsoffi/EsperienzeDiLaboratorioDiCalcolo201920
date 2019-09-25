#include <stdio.h>
#include <stdlib.h>
#define LEN 1000
main () {
  FILE *fp;
  int num, bytes, i, n;
  double data[LEN];
  fp = fopen("random.bin", "wb");
  for (i = 0; i < LEN; i++) {
    *(data + i) = (double)random() / (double)RAND_MAX;
  }
  bytes = sizeof(double);
  num = 100;
  n = fwrite(data + 500, bytes, num, fp);
  fclose(fp);
}

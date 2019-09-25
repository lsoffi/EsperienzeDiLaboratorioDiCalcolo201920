#include <stdio.h>
#include <stdlib.h>
#define LEN 1000
main () {
  FILE *fp;
  int num, bytes, i, n;
  double data[LEN];
  fp = fopen("random.bin","rb");
  bytes = sizeof(double);
  num = 50;
  n = fread(data, bytes, num, fp);
  for (i = 0; i < n; i++) {
    printf("data[%d] = %f\n", i, data[i]);
  }
  fclose(fp);
}

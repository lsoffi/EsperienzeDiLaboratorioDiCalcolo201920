#include <stdio.h>
#include <stdlib.h>
#define LEN 100
main () {
  FILE *fp;
  int i, k;
  double x, data[LEN];
  if ((fp = fopen("random.dat", "w")) == NULL ) {
      printf("Errore nell'apertura del file random.dat\n");
      exit(EXIT_FAILURE);
  } 
  for (i = 1; i <= LEN; i++) {
    x = (double)rand() / (double)RAND_MAX;
    fprintf(fp, "%d %f\n", i, x);
  }
  fclose(fp);
  fp = fopen("random.dat", "r+");
  for (i = 1; i <= LEN; i++) {
    fscanf(fp, "%d %lf", &k, &x);
    *(data + LEN - k) = x;
  }
  fprintf(fp, "\n INVERSIONE \n");
  for (i = 1; i <= LEN; i++) {
    fprintf(fp, "%d %f\n", i, *(data + i - 1));
  }   
  fclose(fp);
}

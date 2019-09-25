#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 10000
#define MAX_FNAME 100
main() {
  char outputFile[MAX_FNAME + 1], c;
  FILE *fp;
  int i = 0, j, n;
  double data[MAX_NUM], temp, *lastpd, *pd, *qd;
  printf("Inserire nome del file di output: ");
  while ((c = getchar()) != '\n' && i < MAX_FNAME) {
    outputFile[i++] = c;
  }
  outputFile[i++] = '\0';
  if ((fp = fopen(outputFile, "w+") == NULL) {
    printf("Errore nell'apertura del file %s\n", outputFile);
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "**** SEQUENZA DEI DATI ORIGINALI ****\n");   
  for (i = 0; i < MAX_NUM; i++) {
    *(data + i) = (double)random() / (double)RAND_MAX;
    fprintf(fp, "%d %f\n", i, *(data + i));
  }
  fprintf(fp, "**** TERMINE DEI DATI ORIGINALI ****\n");
  lastpd = data + MAX_NUM - 1;
  for (pd = data; pd < lastpd; pd++) {
    for (qd = lastpd; qd > pd; qd--) {
      if (*(qd - 1) > *qd) {
        temp = *(qd - 1);
	*(qd - 1) = *qd;
	*qd = temp;
      }
    }
  }
  fprintf(fp, "**** SEQUENZA DEI DATI ORDINATI ****\n");  
  for (i = 0; i < MAX_NUM; i++) {
    fprintf(fp, "%d %f\n", i, *(data + i));    
  }
  fclose(fp);
}

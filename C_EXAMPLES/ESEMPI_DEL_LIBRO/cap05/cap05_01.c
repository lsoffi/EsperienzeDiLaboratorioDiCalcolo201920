#include <stdio.h>
#include <stdlib.h>
#define LEN 20

main(){
  int data[LEN], i, N = 0;
  int min, max;
  double average;
/* acquisiamo N dati, N <= LEN */
  do {
    printf("numero di dati = ");
    scanf("%d", &N);
  } while (N <= 0 || N > LEN);
  for (i = 0; i < N; i++) {
    printf("dato %d = ", i + 1);
    scanf("%d", &data[i]);
  }
/* analizziamo l'array data */
  min = max = average = data[0];
  for (i = 1; i < N; i++) {
    if (data[i] < min) {
      min = data[i];
    }
    else if (data[i] > max) {
      max = data[i];
    }
    average += data[i];
  }
  average /= N;
  printf(" Il minimo  vale %d\n", min);
  printf(" Il massimo vale %d\n", max);
  printf(" La media vale %lf\n", average);
  exit(0);
}

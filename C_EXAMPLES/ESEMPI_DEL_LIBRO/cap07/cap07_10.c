#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUM 10000
#define MAX_BINS 100
int defineInput(double *, int);
void fillDist(double *, int *, double, double, int, int);
void printHisto(int *, int);

main() {
  int k, bins, entries, content[MAX_BINS]={0};
  int seed;
  double xmin, xmax, width;
  double data[MAX_NUM];
  seed = time(0);
  srand48(seed);
  entries = defineInput(data, MAX_NUM);
  printf("Dare limiti dell'istogramma\n xmin = ");
  scanf("%lf",&xmin);
  printf(" xmax = ");
  scanf("%lf",&xmax);
  do {
    printf("Dare numero di intervalli bins = ");
    scanf("%d",&bins);
  } while (bins < 0 || bins > MAX_BINS);
  printf("Limiti xmin=%f, xmax=%f, %d intervalli\n", xmin, xmax, bins);
  fillDist(data, content, xmin, xmax, bins, entries);
  for(k=0; k < bins; k++) {
    printf("contenuto del bin %d = %d\n", k, *(content+k));
  } 
  printHisto(content, bins);
  exit(EXIT_SUCCESS);   
}

void fillDist(double *data, int *bin, double min, double max, int n, int nData) {
  int i, j;
  double invWidth = (double) n / (max - min);
  for (i = 0; i < nData; i++) {    
    j =  ( (*(data + i) - min) * invWidth);
    if(j < n && j >= 0) {
      (*(bin+j))++;
    }   
  }
}

void printHisto(int *bin, int n) {
  int i, j, max;
  int maxChar = 100;
  char c = '*', empty = ' ', hist[n+2][maxChar];
  for (i = 0; i < n + 2; i++) {
    for (j = 0; j < maxChar; j++) {
      hist[i][j] = empty;
    }
  } 
  max = bin[0];
  for (i = 1; i < n; i++) {
    if (bin[i] > max) {
      max = bin[i];
    }
  }
  if (max > maxChar) {
    max = maxChar;
  }   
  for (j = 0; j < max; j++) {
    hist[0][j] = '|';
  }
  hist[0][0] = hist[1][0] = '_';
  for (i = 2; i < n + 2; i++) {
    hist[i][0] = '_';
    for (j = 0; j < *(bin + i - 2); j++) {
      hist[i][j + 1] = c;
    }
  }
  for (j = max; j >= 0 ; j--) {
    for (i = 0; i < n + 2; i++) {
      printf("%c", hist[i][j]);
    }
    printf("\n");
  } 
}

int defineInput(double buf[], int max) {
  int k, N;
  do {
    printf("Numero di eventi nell'istogramma = ");
    scanf("%d", &N);
  } while (N < 0 || N > max);
  for(k=0; k < N; k++) {
    buf[k] = (double) lrand48() / (RAND_MAX + 1.);
  }
  return N;
}

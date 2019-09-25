#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_EXIT_SUCCESS       0
#define MY_EXIT_FAILURE      -9

typedef unsigned long long RANDOM_TYPE;

FILE *fDat;

/*********************************/
int main(void) {

  long i, numberOfSteps = 100000;
  long position;
  double doubleM, iDoubleM;
  RANDOM_TYPE a, seed, randomNumber;

  fDat = fopen("rw1d.dat","w");
  if(fDat == NULL){
    printf("Errore: non riesco ad aprire il file di scrittura\n");
    exit(MY_EXIT_FAILURE);
  }

  a = 1181783497276652981;
  seed = 131419;

  doubleM = pow(2.,64.);
  iDoubleM = 1.0 / doubleM;

  printf("# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  printf("# Numero di passi fatti dal viaggiatore: %d\n", numberOfSteps);
  fprintf(fDat, "# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  fprintf(fDat, "# Numero di passi fatti dal viaggiatore: %d\n", 
	  numberOfSteps);

  if(sizeof(RANDOM_TYPE)<8){
    printf("Errore: RANDOM_TYPE deve avere almeno 8 byte,"
	   " mentre ne ha  %d\n", sizeof(RANDOM_TYPE));
    exit(MY_EXIT_FAILURE);
  }

  randomNumber = seed;
  position = 0;

  for(i = 0; i < numberOfSteps; i++){
    double r;
    fprintf(fDat, "%d %d\n", i, position);
    randomNumber = a * randomNumber;
    r = (double)randomNumber * iDoubleM;
    if(r < 0.5){
      position += 1;
    }else{
      position -= 1;
    }
  }
  fprintf(fDat, "%d %d\n", i, position);
  fclose(fDat);
}

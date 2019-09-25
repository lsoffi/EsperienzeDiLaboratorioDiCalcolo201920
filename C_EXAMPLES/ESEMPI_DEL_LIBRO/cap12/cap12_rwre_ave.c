#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_EXIT_SUCCESS       0
#define MY_EXIT_FAILURE      -9

#define HALF_MAX_DISTANCE 10000
#define MAX_DISTANCE (2 * HALF_MAX_DISTANCE)

typedef unsigned long long RANDOM_TYPE;

FILE *fDat, *fConf;

/*********************************/
int main(void) {

  long i, j, numberOfSteps = 100000, numberOfSamples = 1000;
  long position;
  double doubleM, iDoubleM;
  double *x2Average, *x2Error;
  double localNoise[MAX_DISTANCE];

  RANDOM_TYPE a, seed, randomNumber;

  fDat = fopen("rwer_ave.dat","w");
  fConf = fopen("rwer_conf.dat","w");
  if(fDat == NULL){
    printf("Errore: non riesco ad aprire il file di scrittura dat\n");
    exit(MY_EXIT_FAILURE);
  }
  if(fConf == NULL){
    printf("Errore: non riesco ad aprire il file di scrittura conf\n");
    exit(MY_EXIT_FAILURE);
  }

  a = 1181783497276652981;
  seed = 131419;

  doubleM = pow(2.,64.);
  iDoubleM = 1.0 / doubleM;

  printf("# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  printf("# Numero di passi fatti dal viaggiatore: %d\n", numberOfSteps);
  printf("# Numero di campioni: %d\n", numberOfSamples);
  fprintf(fDat, "# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  fprintf(fDat, "# Numero di passi fatti dal viaggiatore: %d\n", 
	  numberOfSteps);
  fprintf(fDat, "# Numero di campioni: %d\n", numberOfSamples);

  if(sizeof(RANDOM_TYPE)<8){
    printf("Errore: RANDOM_TYPE deve avere almeno 8 byte,"
	   " mentre ne ha  %d\n", sizeof(RANDOM_TYPE));
    exit(MY_EXIT_FAILURE);
  }

  x2Average = calloc(numberOfSteps, sizeof(double));
  if(x2Average==NULL){
    printf("Errore: la calloc di x2Average e' fallita\n");
    exit(MY_EXIT_FAILURE);
  }
  x2Error = calloc(numberOfSteps, sizeof(double));
  if(x2Error==NULL){
    printf("Errore: la calloc di x2Error e' fallita\n");
    exit(MY_EXIT_FAILURE);
  }

  randomNumber = seed;

  for(j = 0; j < numberOfSamples; j++){
    position = 0;
    for(i = 0; i < MAX_DISTANCE; i++){
      randomNumber = a * randomNumber;
      localNoise[i] = (double)randomNumber * iDoubleM;
    }
    for(i = 0; i < numberOfSteps; i++){
      double r, x, x2, x4;
      long ip;
      randomNumber = a * randomNumber;
      r = (double)randomNumber * iDoubleM;
      ip = position + HALF_MAX_DISTANCE;
      if((ip < 0) || (ip >= MAX_DISTANCE)){
	printf("Errore: siamo andati troppo lontano\n");
	exit(-9);
      }
      if(r < localNoise[ip]){
	position += 1;
      }else{
	position -= 1;
      }
      if(j < 5){
	fprintf(fConf, "S %ld %ld %ld %lg\n", 
		j, i, position, localNoise[ip]);
      }
      x = (double)position; 
      x2 = x * x; 
      x4 = x2 * x2; 
      x2Average[i] += x2;
      x2Error[i] += x4;
    }
  }
  for(i = 0; i < numberOfSteps; i++){
    x2Average[i] /= (double) numberOfSamples;
    x2Error[i] /= (double) numberOfSamples;
    x2Error[i] -= (x2Average[i] *  x2Average[i]);
    if(numberOfSamples > 1){
      x2Error[i] /= (double) (numberOfSamples - 1);
    } else {
      x2Error[i] = 0.0;
    }
    if(x2Error[i] > 0.0){
      x2Error[i] = sqrt(x2Error[i]);
    } else {
      x2Error[i] = 0.0;
    }
    fprintf(fDat, "%ld %lg %lg\n", i+1, x2Average[i], x2Error[i]);
  }
  fclose(fDat);
}

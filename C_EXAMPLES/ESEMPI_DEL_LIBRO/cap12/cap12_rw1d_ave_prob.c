#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_EXIT_SUCCESS       0
#define MY_EXIT_FAILURE      -9

#define NOS 1000

typedef unsigned long long RANDOM_TYPE;

FILE *fDat;

/*********************************/
int main(void) {

  long i, j, numberOfSteps = NOS, numberOfSamples = 100000;
  long position;
  double doubleM, iDoubleM;
  long pX[2*NOS+1]={0}, pXMod[NOS+1]={0}, pXX[NOS*NOS+1]={0};
  RANDOM_TYPE a, seed, randomNumber;

  fDat = fopen("rw1d_ave_prob.dat","w");
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

  randomNumber = seed;

  for(j = 0; j < numberOfSamples; j++){
    long x, x2, xMod;
    position = 0;
    for(i = 0; i < numberOfSteps; i++){
      double r;
      randomNumber = a * randomNumber;
      r = (double)randomNumber * iDoubleM;
      if(r < 0.5){
	position += 1;
      }else{
	position -= 1;
      }
    }
    x = NOS + position; 
    x2 = position * position; 
    xMod = position;
    if (xMod < 0) xMod = -xMod;
    pX[x]++;
    pXMod[xMod]++;
    pXX[x2]++;
  }
  for(i = 0; i <= 2 * NOS; i++){
    if(pX[i]!=0)fprintf(fDat,"PX %ld %ld \n",i,pX[i]);}
  for(i = 0; i <= NOS; i++){
    if(pXMod[i]!=0)fprintf(fDat,"PXMOD %ld %ld \n",i,pXMod[i]);}
  for(i = 0; i <= NOS * NOS; i++){
    if(pXX[i]!=0)fprintf(fDat,"PXX %ld %ld \n",i,pXX[i]);}
  fclose(fDat);
}

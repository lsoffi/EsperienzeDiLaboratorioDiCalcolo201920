#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9

#define NUM_TOT 1000000
#define NUM_BIN  51
#define NUM_TEST 50

typedef unsigned long long RANDOM_TYPE;

/*********************************/
int main(void) {

  long i, j, bin, totNumber = NUM_TOT;
  long numBin = NUM_BIN, nDOF = NUM_BIN - 1;
  long numTest = NUM_TEST;
  long y[NUM_BIN];
  RANDOM_TYPE a, b, m, seed, randomNumber;
  double phi, avePhi, errPhi;

  a = 7 * 7 * 7 * 7 * 7;
  m = 2147483647;
  seed = 756431;

  seed = seed % m;
  printf("a = %Lu m = %Lu I0 = %Lu\n",
         a, m, seed);
  printf("Number of random values per test: %ld\n", totNumber);
  printf("Number of tests: %ld\n", numTest);
  printf("Number of degrees of freedom: %ld\n", numBin-1);

  if(sizeof(RANDOM_TYPE)<8){
    printf("Errore: RANDOM_TYPE deve avere almeno 8 byte,"
	   " mentre ne ha  %d\n", sizeof(RANDOM_TYPE));
    exit(-9);
  }

  randomNumber = seed;

  for(j = 0; j < numTest; j++){
    for(i = 0; i < numBin; i++){
      y[i] = 0;
    }
    for(i = 0; i < totNumber; i++){
      double r;
      randomNumber = (a * randomNumber) % m;
      r = (double)randomNumber/(double)m;
      bin = r * numBin;
      if(bin == numBin){
	bin--;
      } else if(bin > numBin){
	printf("Errore: bin troppo grande\n");
	exit(EXIT_FAILURE);
      }
      y[bin]++;
    }
    phi = (- (double) totNumber);
    for(i = 0; i < numBin; i++){
      phi += ( (double) y[i] * (double)y[i] * (double)numBin 
	       / (double) totNumber);  
    }
    printf("Test %ld Phi %lg \n", j, phi);
    avePhi += phi;
    errPhi += (phi * phi);
  }
  avePhi /= (double) numTest;
  errPhi /= (double) numTest;
  errPhi -= (avePhi * avePhi);
  if(numTest > 1){
    errPhi /= (double) (numTest-1);
  } else {
    errPhi = 0.0;
  }
  if(errPhi > 0.0){
    errPhi = sqrt(errPhi);
  } else {
    errPhi = 0.0;
  }
  printf("<Phi> = %lg +/- %lg\n",avePhi, errPhi);
}

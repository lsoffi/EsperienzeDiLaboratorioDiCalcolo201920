#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9

#define NUM_TOT 50
#define NUM_TEST 1000

typedef unsigned long long RANDOM_TYPE;

/*********************************/
int main(void) {

  long i, j, bin, totNumber = NUM_TOT;
  long numTest = NUM_TEST;
  RANDOM_TYPE a, b, m, seed, randomNumber;
  double vRandom[NUM_TOT];
  double phi, aveKMax, errKMax, iTotNumber = 1.0 / (double) totNumber;
  double kMax, kPlusMax, kMinusMax;

  a = 7 * 7 * 7 * 7 * 7;
  m = 2147483647;
  seed = 756431;

  seed = seed % m;
  printf("a = %Lu m = %Lu I0 = %Lu\n",
         a, m, seed);
  printf("Number of random values per test: %ld\n", totNumber);
  printf("Number of tests: %ld\n", numTest);

  if(sizeof(RANDOM_TYPE)<8){
    printf("Errore: RANDOM_TYPE deve avere almeno 8 byte,"
	   " mentre ne ha  %d\n", sizeof(RANDOM_TYPE));
    exit(-9);
  }

  aveKMax = 0.0;
  errKMax = 0.0;
  randomNumber = seed;

  for(j = 0; j < numTest; j++){
    for(i = 0; i < totNumber; i++){
      randomNumber = (a * randomNumber) % m;
      vRandom[i] = (double)randomNumber / (double)m; 
    }
    for(;;){
      long change = 0;
      for(i = 0; i < (totNumber - 1); i++){
	double scratch;
	if(vRandom[i] > vRandom[i + 1]){
	  scratch = vRandom[i];
	  vRandom[i] = vRandom[i + 1];
	  vRandom[i + 1] = scratch;
	  change++;
	}
      }
      if(change == 0)break;
    }

    kPlusMax = - 1.0;
    kMinusMax = - 1.0;
    for(i = 0; i < totNumber; i++){
      double kPlus, kMinus;
      kPlus = fabs((double)i * iTotNumber - vRandom[i]);
      kMinus = fabs((double)(i - 1) * iTotNumber - vRandom[i]);
      if(kPlus > kPlusMax){
	kPlusMax = kPlus;
      }
      if(kMinus > kMinusMax){
	kMinusMax = kMinus;
      }
    }
    if(kPlusMax >= kMinusMax){
      kMax = kPlusMax;
    }else{
      kMax = kMinusMax;
    }

    aveKMax += kMax;
    errKMax += (kMax * kMax);
  }
  aveKMax /= (double) numTest;
  errKMax /= (double) numTest;
  errKMax -= (aveKMax * aveKMax);
  if(numTest > 1){
    errKMax /= (double) (numTest - 1);
  } else {
    errKMax = 0.0;
  }
  if(errKMax > 0.0){
    errKMax = sqrt(errKMax);
  } else {
    errKMax = 0.0;
  }
  printf("<KMax> = %lg +/- %lg\n", aveKMax, errKMax);
}

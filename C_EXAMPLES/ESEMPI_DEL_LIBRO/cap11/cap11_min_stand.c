#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9

typedef unsigned long long RANDOM_TYPE;

/*********************************/
int main(void) {

  long i, totNumber = 1000000000;
  double ave = 0.0, err = 0.0;
  RANDOM_TYPE a, b, m, seed, randomNumber;

  a = 7 * 7 * 7 * 7 * 7;
  m = 2147483647;
  seed = 756431;

  seed = seed % m;
  printf("a = %Lu m = %Lu I0 = %Lu\n",
         a, m, seed);
  printf("Number of random values: ",totNumber);

  if(sizeof(RANDOM_TYPE)<8){
    printf("Errore: RANDOM_TYPE deve avere almeno 8 byte,"
	   " mentre ne ha  %d\n", sizeof(RANDOM_TYPE));
    exit(-9);
  }

  randomNumber = seed;

  for(i = 0; i < totNumber; i++){
    double r;
    randomNumber = (a * randomNumber) % m;
    r = (double)randomNumber/(double)m;
    ave += r;
    err += (r * r);
  }
  ave /= (double)totNumber;
  err /= (double)totNumber;
  err -= (ave * ave);
  if(totNumber > 1){
    err /= (double)(totNumber - 1);
  } else {
    err=0.0;
  }
  if(err > 0.0){
    err  = sqrt(err);
  } else {
    err = 0.0;
  }
  printf("Average: %lg +/- %lg\n", ave, err);
}

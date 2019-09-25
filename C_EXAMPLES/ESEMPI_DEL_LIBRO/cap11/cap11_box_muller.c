#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9

typedef unsigned long long RANDOM_TYPE;

/*********************************/
int main(void) {

  long i, totNumber = 100000000, totNumber2 = 2 * totNumber;
  double ave = 0.0, err = 0.0;
  double ave2 = 0.0, err2 = 0.0;
  double ave4 = 0.0, err4 = 0.0;
  double myPi;
  RANDOM_TYPE a, b, m, seed, randomNumber;

  myPi = acos(-1.);

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
    double r1, r2, g1, g2, s1, s2;
    randomNumber = (a * randomNumber) % m;
    r1 = (double)randomNumber/(double)m;
    randomNumber = (a * randomNumber) % m;
    r2 = (double)randomNumber/(double)m;
    g1 = sqrt(- 2.0 * log(r1)) * cos(2.0 * myPi * r2);
    g2 = sqrt(- 2.0 * log(r1)) * sin(2.0 * myPi * r2);
    ave += (g1 + g2);
    s1 = g1 * g1;
    s2 = g2 * g2;
    ave2 += (s1 + s2);
    s1 = s1 * s1;
    s2 = s2 * s2;
    ave4 += (s1 + s2);
    s1 = s1 * s1;
    s2 = s2 * s2;
    err4 += (s1 + s2);
  }
  ave /= (double)totNumber2;
  ave2 /= (double)totNumber2;
  ave4 /= (double)totNumber2;
  err4 /= (double)totNumber2;
  err = ave2;
  err2 = ave4;
  err -= (ave * ave);
  err2 -= (ave2 * ave2);
  err4 -= (ave4 * ave4);
  if(totNumber2 > 1){
    err /= (double)(totNumber2 - 1);
    err2 /= (double)(totNumber2 - 1);
    err4 /= (double)(totNumber2 - 1);
  } else {
    err  = 0.0;
    err2 = 0.0;
    err4 = 0.0;
  }
  if(err > 0.0){
    err   = sqrt(err);
    err2  = sqrt(err2);
    err4  = sqrt(err4);
  } else {
    err = 0.0;
    err2 = 0.0;
    err4 = 0.0;
  }
  printf("<x>: %lg +/- %lg\n", ave, err);
  printf("<x^2>: %lg +/- %lg\n", ave2, err2);
  printf("<x^4>: %lg +/- %lg\n", ave4, err4);
}

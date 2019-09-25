
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_EXIT_SUCCESS       0
#define MY_EXIT_FAILURE      -9
#define SHIFT_LENGTH      55

typedef unsigned long RANDOM_TYPE;

void shiftInit(unsigned int seed);
RANDOM_TYPE callShift(void);

RANDOM_TYPE shiftRegister[SHIFT_LENGTH];
unsigned long pointerB, pointerC;

/*********************************/
int main(void) {

  long i, numTot = 1000000;
  RANDOM_TYPE b, c, seed, randomNumber;
  double r, ave, ave2, err, err2;

  b = 24;
  c = 55;
  seed = 35971;

  printf("# Shift register: b = %lu c = %lu seed (for rand()) = %lu\n",
	 b, c, seed);
  printf("#   sizeof(RANDOM_TYPE) = %ld\n",sizeof(RANDOM_TYPE));

  shiftInit((unsigned int) seed);

  ave = 0.0;
  err = 0.0;
  for(i = 0; i < numTot; i++){
    double r2, r4;
    randomNumber = callShift();
    r = (double)randomNumber / (double)(0XFFFFFFFF);
    r2 = r * r;
    r4 = r2 * r2;
    ave += r;
    err += r2;
    err2 += r4;
  }
  ave  /= (double)numTot;
  err  /= (double)numTot;
  err2 /= (double)numTot;
  ave2 = err;
  err -= (ave * ave);
  err2 -= (ave2 * ave2);
  if(numTot>1){
    err /= (double)(numTot-1);
    err2 /= (double)(numTot-1);
  } else {
    err = 0.0;
    err2 = 0.0;
  }
  if(err > 0.0){
    err = sqrt(err);
  } else {
    err = 0.0;
  }
  if(err2 > 0.0){
    err2 = sqrt(err2);
  } else {
    err2 = 0.0;
  }
  for(i = 0; i < SHIFT_LENGTH; i++){
    if(sizeof(RANDOM_TYPE) == 4){
      double r = (double)shiftRegister[i]/
	(double)(0XFFFFFFFF);
      printf("Final: %2ld hex = %lX (0,1) = %lf\n", 
	     i, shiftRegister[i], r);
    } else {
      printf("Error: this RANDOM_TYPE not yet implemented (final)\n");
      exit(MY_EXIT_FAILURE);
    }
  }
  printf("Total   <r>: %lg +/- %lg\n", ave, err);
  printf("Total <r*r>: %lg +/- %lg\n", ave2, err2);
  exit(MY_EXIT_SUCCESS);
}

/*********************************/
RANDOM_TYPE callShift(void){  
  RANDOM_TYPE r;
  r = shiftRegister[pointerB] ^ shiftRegister[pointerC];
  shiftRegister[pointerC] = r;
  pointerB++;
  pointerC++;
  if(pointerB == SHIFT_LENGTH)pointerB = 0;
  if(pointerC == SHIFT_LENGTH)pointerC = 0;
  return r;
}

/*********************************/
void shiftInit(unsigned int seed){  
  unsigned long theBit;
  long i, j;
  double r;
  double ave = 0.0, err = 0.0;

  pointerB = 31;
  pointerC =  0;

  srand((unsigned int) seed);
  for(i = 0; i < 1000; i++){
    rand();
  }
  for(i = 0; i < SHIFT_LENGTH; i++){
    shiftRegister[i] = 0UL;    
  }
  for(i = 0; i < SHIFT_LENGTH; i++){
    for(j = 0; j < 8 * sizeof(RANDOM_TYPE); j++){
      r = (double)rand() / (double)RAND_MAX;
      if(r > 0.5){theBit = 0;} else {theBit = 1;}
      shiftRegister[i] = shiftRegister[i] 
	| (theBit << j);
    }
  }
  for(i = 0; i < SHIFT_LENGTH; i++){
    if(sizeof(RANDOM_TYPE) == 4){
      double r = (double)shiftRegister[i]/
	(double)(0XFFFFFFFF);
      ave += r;
      err += (r * r);
      printf("Init: %2ld hex = %lX (0,1) = %lf\n", 
	     i, shiftRegister[i], r);
    } else {
      printf("Error: this RANDOM_TYPE not yet implemented\n");
      exit(MY_EXIT_FAILURE);
    }
  }
  ave /= (double)SHIFT_LENGTH;
  err /= (double)SHIFT_LENGTH;
  err -= (ave * ave);
  err /= (double)(SHIFT_LENGTH-1);
  err = sqrt(err);
  printf("Init average: %lg +/- %lg\n", ave, err);
}

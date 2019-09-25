
#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9
#define MAX_M 1024

typedef long RANDOM_TYPE;

/*********************************/
int main(void) {

  long i, j;
  long successFlag;
  RANDOM_TYPE a, b, m, seed, randomNumber;
  RANDOM_TYPE randomStore[MAX_M+1];

  a = 7;
  b = 7;
  m = 10;
  seed = 7;

  seed = seed % m;
  printf("a = %ld b = %ld m = %ld I0 = %ld\n",
	 a, b, m, seed);

  randomNumber = seed;
  randomStore[0] = randomNumber;

  if (m > MAX_M) {
    printf("Errore: m troppo grande.\n");
    exit(EXIT_FAILURE);
  }

  i = 1;
  successFlag = 0;
  while ((i <= m) && (successFlag == 0)){
    randomNumber = (a * randomNumber + b) % m;
    randomStore[i] = randomNumber;
    j = 0;
    do {
      if (randomStore[j] == randomNumber){
	successFlag = 1;
	printf("Fatto: T = %ld\n", i - j);
      }
      j++;
    } while ((j < i) && 
	     (randomStore[j - 1] != randomNumber) );
    i++;
  }

  if (successFlag == 1){
    exit(EXIT_SUCCESS);
  }
  else if (successFlag == 0){
    printf("Errore (inconsistenza grave):"
	   " periodo non trovato.\n");
    exit(EXIT_FAILURE);
  }
}

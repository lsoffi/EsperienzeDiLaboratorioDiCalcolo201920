
#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9
#define MAX_M 1024

typedef long RANDOM_TYPE;

/*********************************/
int main(void) {

  long i, j;
  RANDOM_TYPE a, b, m, seed, randomNumber;
  RANDOM_TYPE randomSeen[MAX_M+1];

  a = 7;
  b = 7;
  m = 10;
  seed = 7;

  seed = seed % m;
  printf("a = %ld b = %ld m = %ld I0 = %ld\n",
	 a, b, m, seed);

  for(i = 1; i <= m; i++){
    randomSeen[i] = 0;
  }
  randomNumber = seed;
  randomSeen[randomNumber] = 1;

  if(m > MAX_M){
    printf("Errore: m troppo grande.\n");
    exit(EXIT_FAILURE);
  }

  for(i = 1; i <= m; i++){
    randomNumber = (a * randomNumber + b) % m;
    if(randomSeen[randomNumber]>0){
      printf("Fatto: T = %ld\n", i + 1 - randomSeen[randomNumber]);
      exit(EXIT_SUCCESS);
    }else{
      randomSeen[randomNumber] = i + 1;
    }
  }
  printf("Errore (inconsistenza grave): periodo non trovato.\n");
  exit(EXIT_FAILURE);
}

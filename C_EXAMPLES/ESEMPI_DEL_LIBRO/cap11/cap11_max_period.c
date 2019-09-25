
#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       1
#define EXIT_FAILURE      -9
#define MAX_M 1024

typedef long RANDOM_TYPE;

long findPrimes(long *m_prime, RANDOM_TYPE m_m);
long findPeriod(RANDOM_TYPE m_a, RANDOM_TYPE m_b,
		RANDOM_TYPE m_m, RANDOM_TYPE m_seed);
long maxPeriodTheorem(RANDOM_TYPE m_a, RANDOM_TYPE m_b,
		      RANDOM_TYPE m_m);

/*********************************/
int main(void) {

  long period, proof;
  RANDOM_TYPE a, b, m, seed;

  a = 106;
  b = 19;
  m = 400;
  seed = 7;

  seed = seed % m;
  printf("a = %ld b = %ld m = %ld I0 = %ld\n",
	 a, b, m, seed);

  if (m > MAX_M) {
    printf("Errore: m troppo grande.\n");
    exit(EXIT_FAILURE);
  }

  if (a >= m) {
    printf("Errore: a troppo grande.\n");
    exit(EXIT_FAILURE);
  }

  if (b >= m) {
    printf("Errore: b troppo grande.\n");
    exit(EXIT_FAILURE);
  }

  period = findPeriod(a, b, m, seed);
  printf("T = %ld\n", period);

  proof = maxPeriodTheorem(a, b, m);

  if ((period == m) && (proof == 1)) {
    printf("OK: Il sistema ha periodo massimo ed "
	   "il teorema e' verificato.\n");
  } else if ((period < m) && (proof > 1)) {
    printf("OK: Il sistema non ha periodo massimo ed "
	   " il teorema e' verificato.\n");
  } else {
    printf("Errore: contraddizione interna\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

/*********************************/
long findPeriod(RANDOM_TYPE a, RANDOM_TYPE b,
		RANDOM_TYPE m, RANDOM_TYPE seed) {

  long i, j;

  RANDOM_TYPE randomNumber;
  RANDOM_TYPE randomStore[MAX_M + 1];

  randomNumber = seed;
  randomStore[0] = randomNumber;
  for (i = 1; i <= m; i++) {
    randomNumber = (a * randomNumber + b) % m;
    randomStore[i] = randomNumber;
    for (j = 0; j < i; j++) {
      if (randomStore[j] == randomNumber) {
	return(i - j);
      }
    }
  }
  printf("Errore (inconsistenza grave): periodo non trovato.\n");
  exit(EXIT_FAILURE);
}

/*********************************/
long findPrimes(long *prime, RANDOM_TYPE m) {
  
  long numPrimes, i, j, flagPrime;

  prime[0] = 2;
  numPrimes = 1;
  for (i = 3; i <= m; i+=2) {
    flagPrime = 1;
    j = 0;
    while((j < numPrimes) && (flagPrime == 1)) {
      if ((i % prime[j]) == 0) {
	flagPrime = 0;
      }
      j++;
    }
    if (flagPrime == 1) {
      prime[numPrimes] = i;
      numPrimes++;
    }
  }
  return numPrimes;
}

/*********************************/
long maxPeriodTheorem(RANDOM_TYPE a, RANDOM_TYPE b,
		      RANDOM_TYPE m) {

  long i, j, returnFlag = 1;
  RANDOM_TYPE aTilde;
  long prime[MAX_M], numPrimes;
  long divM[MAX_M], divB[MAX_M], numDivM, numDivB;

  /* in primo luogo determiniamo i numeri primi sino ad m */

  numPrimes = findPrimes(prime, m);

  /* ora determiniamo i divisori primi di m e b */

  numDivM = 0;
  numDivB = 0;
  for (i = 0; i < numPrimes; i++) {
    if ((m % prime[i]) == 0) {
      divM[numDivM] = prime[i];
      numDivM++;
    }
    if ((b % prime[i]) == 0) {
      divB[numDivB] = prime[i];
      numDivB++;
    }
  }

  printf("I divisori primi di m sono:\n");
  for (i=0; i < numDivM; i++) {
    printf(" M %d\n", divM[i]);
  }
  printf("I divisori primi di b sono:\n");
  for (i=0; i < numDivB; i++) {
    printf(" B %d\n", divB[i]);
  }

  /* controlliamo se b ed m ammettono divisori primi 
     in comune */

  i = 0;
  while ((i < numDivM) && (returnFlag == 1)) {
    j = 0;
    while((j < numDivB) && (returnFlag == 1)) {
      if (divM[i] == divB[j]) {
	printf("1) KO: b ed m ammettono almeno un divisore "
	       "in comune: %d\n", divM[i]);
	returnFlag = 2;
      }
      j++;
    }
    i++;
  }
  if (returnFlag == 1) {
    printf("1) OK: b ed m non ammettono divisori primi in comune\n");
  }

  /* ora controlliamo se a-1 e` multiplo 
     di tutti i divisori primi di m */

  aTilde = a - 1;
  i = 0;
  while((i < numDivM) && (returnFlag < 3)){
    if ((aTilde % divM[i]) != 0) {
      printf("2) KO: a-1 non e' multiplo di un divisore"
	     " primo di m: %d\n",divM[i]);
      returnFlag *= 3;
    }
    i++;
  }
  if (((returnFlag / 3) * 3)!=returnFlag) {
    printf("2) OK: a-1 e' multiplo di tutti i divisori"
	   " primi di m\n");
  }
  if ((m % 4) !=0 ) {
    printf("3) OK: m non e' multiplo di 4\n");
  } else {
    if ((aTilde % 4) ==0 ) {
      printf("3) OK: m ed a-1 sono entrambi multipli di 4\n");
    } else{
      printf("3) KO: m e' multiplo di 4 ma a-1 non lo e'.\n");
      returnFlag *= 5;
    }
  }
  return returnFlag;
}

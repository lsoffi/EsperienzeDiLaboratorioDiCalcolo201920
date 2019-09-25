
#include <stdio.h>
#include <math.h>

#define NUM_ITER 200
#define L (2 * NUM_ITER)

typedef unsigned long long RANDOM_TYPE;
typedef char CELLULAR_AUTOMA;

/* I numeri random potrebbero servire per
   inizializzare */
#define MYR64  myr64 = (6364136223846793005ULL * myr64)
#define MAX_RAND64     0XFFFFFFFFFFFFFFFFULL
RANDOM_TYPE myr64;
double inverseMaxRand64 = 1.0L / (double)MAX_RAND64;

CELLULAR_AUTOMA C[L], CP[L];
int rule = 150;

#define MY_FAILURE -9
#define MY_SUCCESS 1

/**************************************************/
int main(void)
{
  long time, site;

  for(site = 0; site < L; site++){
    C[site] = 0;
    CP[site] = 0;
  }

  C[L / 2] = 1;
  printf("# la regola e' %d\n",rule);

  for(time = 0; time < NUM_ITER; time++){
    for(site = 0; site < L; site++){
      printf("X %ld T %ld CELLA %d\n", 
	     site - L / 2, time, C[site]);
    }
    /* l'update e' sincrono */
    for(site = 1; site < L - 1; site++){
      if(rule == 90){
	/* regola 90 che e' lo XOR dei vicini */
	CP[site] = C[site-1] ^ C[site+1];
      } else if(rule == 150){
	/* regola 150: XOR dei vicini, 
           XOR con se stesso */
	CP[site] = (C[site-1] ^ C[site+1]) ^ C[site];
      } else{
	printf("errore programma: regola non definita\n");
	exit(MY_FAILURE);
      }
    }
    /* rimetto CP in C */
    for(site = 0; site < L; site++){
      C[site] = CP[site];
    }
  }
  for(site = 0; site < L; site++){
    printf("X %ld T %ld CELLA %d\n",
	   site - L / 2, time, C[site]);
  }
  return MY_SUCCESS;
}

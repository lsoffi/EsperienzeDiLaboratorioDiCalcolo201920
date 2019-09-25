
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_SUCCESS 1
#define MY_FAILURE -9

#define MY_SEED 5467891

#define EXP_SPEED 0
#define EXP_JET 1
#define EXP_ERROR 2
#define EXP_RANDOM 3

union experimentData{
  double speed;
  int num;
  char *errorMessage;
};

char *experimentError[3] = {
  "Slow Trigger", "Boundary Detection", 
  "Memory Fault"
};

unsigned long int numExperimentOutput[3] = {0};

unsigned long int 
setExperiment(unsigned long int experimentNumber);

union experimentData 
experimentBody(unsigned long int experimentOutput);

void 
analyzeExperiment(unsigned long int experimentOutput,
		  union experimentData newData);

void
myEnd(unsigned long int experimentNumber);

double averageSpeed = 0.0;
unsigned long hystogramNumber[5] = {0};

/**************************************************/
int main(void)
{
  unsigned long int experimentOutput = 1;
  unsigned long int experimentNumber = 0;
  
  srand(MY_SEED);
  while (experimentOutput < 4) {
    union experimentData scratchData;
    experimentNumber++;
    experimentOutput = setExperiment(experimentNumber);
    scratchData = experimentBody(experimentOutput);
    analyzeExperiment(experimentOutput, scratchData);
  }
  myEnd(experimentNumber);
}

/**************************************************/
void 
analyzeExperiment(
		  unsigned long int experimentOutput, 
		  union experimentData newData){
  if (experimentOutput == EXP_SPEED){
    averageSpeed += newData.speed;
  }
  if (experimentOutput == EXP_JET){
    hystogramNumber[newData.num]++;
  }
  if (experimentOutput == EXP_ERROR){
    printf("ESPERIMENTO FALLITO: %s\n", newData.errorMessage);
  }
}

/**************************************************/
void myEnd(unsigned long int experimentNumber) { 

  int i;

  experimentNumber--;

  printf("  --------> Numero totale di esperimenti: %u\n",
	 experimentNumber);
  printf("  --------> Esperimenti con risultato con"
	 " una particella: %u\n", numExperimentOutput[EXP_SPEED]);
  if (numExperimentOutput[EXP_SPEED]>0) {
    printf("  ----------> averageSpeed = %g\n", 
	   averageSpeed /= numExperimentOutput[EXP_SPEED]);
  }
  printf("  --------> Esperimenti con risultato con"
	 " molte particelle: %u\n", numExperimentOutput[EXP_JET]);
  for (i = 0; i < 5; i++){
    printf("  Numero esperimenti con %d particelle = %d\n", 
	   i + 2, hystogramNumber[i]);
  }
  printf("  --------> Esperimenti con risultato in"
	 " errore: %u\n", numExperimentOutput[EXP_ERROR]);

}

/**************************************************/
union experimentData
experimentBody(unsigned long int experimentOutput) { 

  union experimentData myData;
  double oneThird = 1./3., twoThirds = 2./3.;

  if (experimentOutput == EXP_SPEED){
    double a = (double)rand()/(double)RAND_MAX;

    myData.speed = 10.0 * a;
    printf("Questo esperimento ha misurato"
	   " velocita' = %g\n", 
	   myData.speed);
  }
  else if (experimentOutput == EXP_JET){
    double a = (double)rand()/(double)RAND_MAX;

    myData.num = (int)(5.0 * a);
    if (myData.num > 4) {
      myData.num = 4;
    }
    printf("Questo esperimento ha misurato numero"
	   " di particelle = %d\n", 
	   myData.num + 2);
  }
  else if (experimentOutput == EXP_ERROR){
    double a = (double)rand()/(double)RAND_MAX;
    if (a < oneThird) {
      myData.errorMessage = experimentError[0];
    } else if (a < twoThirds) {
      myData.errorMessage = experimentError[1];
    } else {
      myData.errorMessage = experimentError[2];
    }
  }

  return myData;
}

/**************************************************/
unsigned long int 
setExperiment(unsigned long int experimentNumber) { 

  unsigned long int experimentOutput;

  double oneThird = 1./3., twoThirds = 2./3.;

  printf("  Scelta del tipo risultato di una"
	 " prova sperimentale\n");
  printf("  Per un risultato con una sola particella"
	 " si digiti 0\n");
  printf("  Per un risultato con molte particelle"
	 " si digiti 1\n");
  printf("  Per un risultato in cui il sistema ha dato"
	 " un errore si digiti 2\n");
  printf("  Per decidere con un numero random"
	 " si digiti 3\n");
  printf("  Per uscire si digiti 4\n");
  
  scanf("%d", &experimentOutput);
  
  printf("  ----> Per l'esperimento numero %u abbiamo"
	 " scelto un output di tipo %u\n", 
	 experimentNumber, experimentOutput);
  
  if (experimentOutput > 4) {
    printf("Errore: tipo di output non definito\n");
    exit(MY_FAILURE);
  }
  
  if (experimentOutput == EXP_RANDOM) {
    double a = (double)rand()/(double)RAND_MAX;
    if (a < oneThird) {
      experimentOutput = EXP_SPEED;
    } else if (a < twoThirds) {
      experimentOutput = EXP_JET;
    } else {
      experimentOutput = EXP_ERROR;
    }
  printf("  ----> Per l'esperimento numero %u rand()"
	 " ha scelto un output di tipo %u\n", 
	 experimentNumber, experimentOutput);
  }
  
  numExperimentOutput[experimentOutput]++;
  
  return experimentOutput;  
}

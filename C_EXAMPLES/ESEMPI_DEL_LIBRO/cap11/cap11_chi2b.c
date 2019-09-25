
#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9

double integrand(long nDOF, double x);

/* Usiamo la regola di Simpson */

/*********************************/
int main(void) {

  FILE *fTableTwo, *fTableThree;
  long numberDegreesOfFreedom, numDOF, numBins, i, j, k, factor, numProb;
  long maximumTrials = 1000;
  double chiSquared, integral, dx;
  double cSMin, cSMax; 
  double oldIntegral, newIntegral, acceptableTolerance = 1.e-6;
  double targetProbability, acceptableProbabilityTolerance = 1.e-6;
  double vTargetProbability[10] = {0.995, 0.99, 0.975, 0.95, 0.9, 0.1, 0.05, 0.025, 0.01, 0.005};

  fTableTwo = fopen("t_dueb.tex","w");
  fTableThree = fopen("t_treb.tex","w");

  oldIntegral = -9999.0;
  newIntegral = -9999.0;

  for(numDOF = 2; numDOF < 101; numDOF++){
    fprintf(fTableTwo,"%ld & ",numDOF);
    fprintf(fTableThree,"%ld & ",numDOF);
    fflush(fTableTwo);
    fflush(fTableThree);
    for(numProb = 9; numProb >= 0; numProb--){
      targetProbability = vTargetProbability[numProb];
      numberDegreesOfFreedom = numDOF;
      chiSquared = 1.0;
      cSMin = 0.0;
      cSMax = 500.0;

      fprintf(stderr, "%lg\n", targetProbability);
      for(k = 0; k < maximumTrials; k++){

	numBins = 100000;
	dx = 1.0 / (double)numBins;
  
	for(j=0;j<maximumTrials;j++){
	  integral = integrand(numberDegreesOfFreedom, 0.0);
	  factor = 4;
	  for(i = 0; i < numBins; i++){
	    double x = (double)i * chiSquared * dx ;
	    integral += ((double)factor * integrand(numberDegreesOfFreedom, x));
	    if(factor == 4){
	      factor = 2;
	    } else {
	      factor = 4;
	    }
	  }
	  integral += ((double)factor * 
		       integrand(numberDegreesOfFreedom, chiSquared));
	  integral /= exp(lgamma(0.5 * (double)numberDegreesOfFreedom));
	  integral /= pow(2.0, 0.5 * (double)numberDegreesOfFreedom) ;
	  integral *= (dx/3.0);
	  integral *= chiSquared;
	  oldIntegral = newIntegral;
	  newIntegral = integral;
	  //fprintf(stderr, "# %lg %lg %lg\n", dx, oldIntegral, newIntegral);
	  if(fabs(oldIntegral-newIntegral)<=acceptableTolerance)break;
	  numBins *= 2;
	  dx = 1.0 / (double)numBins;
	}
	if(j == maximumTrials){
	  fprintf(stderr,"Errore: l'integrale non converge\n");
	  exit(-9);
	}
	fprintf(stderr,"DOF %ld chi2 %lg dx %lg |P-P0| %lg\n", 
		numberDegreesOfFreedom, chiSquared, dx, 
		fabs(integral-targetProbability));
	if((integral-targetProbability)>acceptableProbabilityTolerance){
	  printf("A\n");
	  cSMax = chiSquared;
	  chiSquared = 0.5 * (chiSquared + cSMin);
	} else if((integral-targetProbability)<-acceptableProbabilityTolerance){
	  printf("B\n");
	  cSMin = chiSquared;
	  chiSquared = 0.5 * (chiSquared + cSMax);
	}else{
	  break;
	}
      }
      //      printf("DOF %ld chi2 %.3lf dx %.3le P %.3lf\n", 
      //     numberDegreesOfFreedom, chiSquared, dx, integral);
      fprintf(fTableThree," %.3lf & ", chiSquared);
      fprintf(fTableTwo," %.2lf & ", chiSquared);
      fflush(fTableTwo);
      fflush(fTableThree);
    }
    fprintf(fTableTwo,"\n"); 
    fprintf(fTableThree,"\n"); 
    fflush(fTableTwo);
    fflush(fTableThree);
  }
  fclose(fTableTwo);
  fclose(fTableThree);
}
/*************************************************************/
double integrand(long nDOF, double x) {
  return pow(x, (double)nDOF * 0.5 - 1.0) * exp(- 0.5 * x);
}

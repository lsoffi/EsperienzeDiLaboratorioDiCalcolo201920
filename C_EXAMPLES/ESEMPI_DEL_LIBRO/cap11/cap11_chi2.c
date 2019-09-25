
#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9

double integrand(long nDOF, double x);

/* Usiamo la regola di Simpson */

/*********************************/
int main(void) {

  FILE *fTableTwo, *fTableThree, *fTableFour;
  long numberDegreesOfFreedom, numDOF, numBins, i, j, k, factor, numProb;
  long flagUp, maximumTrials = 1000;
  double chiSquared, integral, dx;
  double cSMin, cSMax; 
  double oldIntegral, newIntegral, acceptableTolerance = 1.e-6;
  double targetProbability, acceptableProbabilityTolerance = 1.e-6;
  double vTargetProbability[10] = 
    {0.995, 0.99, 0.975, 0.95, 0.9, 0.1, 0.05, 0.025, 0.01, 0.005};

  fTableTwo = fopen("t_due.tex", "w");
  fTableThree = fopen("t_tre.tex", "w");
  fTableFour = fopen("t_qua.tex", "w");

  oldIntegral = - 9999.0;
  newIntegral = - 9999.0;

  for(numDOF = 25; numDOF < 101; numDOF += 5){
    fprintf(fTableTwo, "%ld & ", numDOF);
    fprintf(fTableThree, "%ld & ", numDOF);
    fprintf(fTableFour, "%ld & ", numDOF);
    fflush(fTableTwo);
    fflush(fTableThree);
    fflush(fTableFour);
    for(numProb = 9; numProb >= 0; numProb--){
      targetProbability = vTargetProbability[numProb];
      numberDegreesOfFreedom = numDOF;
      chiSquared = 1.0;
      cSMin = 0.0;
      cSMax = 2 * chiSquared;
      flagUp = 1;
      fprintf(stderr, "Target probability is %lg\n", targetProbability);
      for(k = 0; k < maximumTrials; k++){
	numBins = 100000;
	dx = 1.0 / (double)numBins;
	for(j = 0; j < maximumTrials; j++){
	  integral = integrand(numberDegreesOfFreedom, 0.0);
	  factor = 4;
	  for(i = 0; i < numBins; i++){
	    double x = (double)i * chiSquared * dx ;
	    integral += ((double)factor * 
			 integrand(numberDegreesOfFreedom, x));
	    if(factor == 4){
	      factor = 2;
	    } else {
	      factor = 4;
	    }
	  }
	  integral += integrand(numberDegreesOfFreedom, chiSquared);
	  integral /= exp(lgamma(0.5 * (double)numberDegreesOfFreedom));
	  integral /= pow(2.0, 0.5 * (double)numberDegreesOfFreedom) ;
	  integral *= (dx / 3.0);
	  integral *= chiSquared;
	  oldIntegral = newIntegral;
	  newIntegral = integral;
	  if(fabs(oldIntegral - newIntegral) <= acceptableTolerance)break;
	  numBins *= 2;
	  dx = 1.0 / (double)numBins;
	}
	if(j == maximumTrials){
	  fprintf(stderr,"Errore: l'integrale non converge\n");
	  exit(EXIT_FAILURE);
	}
	fprintf(stderr,"DOF %ld chi2 %lg dx %lg |P-P0| %lg\n", 
		numberDegreesOfFreedom, chiSquared, dx, 
		fabs(integral - targetProbability));
	if((integral - targetProbability)
	   > acceptableProbabilityTolerance){
	  cSMax = chiSquared;
	  flagUp = 0;
	  chiSquared = 0.5 * (chiSquared + cSMin);
	} else if((integral-targetProbability)
		  < -acceptableProbabilityTolerance){
	  cSMin = chiSquared;
	  chiSquared = 0.5 * (chiSquared + cSMax);
	  if(flagUp == 1){
	    cSMax *= 2;
	  }
	}else{
	  break;
	}
      }	
      if(k == maximumTrials){
	fprintf(stderr,"Errore: la probabilita' non converge\n");
	exit(EXIT_FAILURE);
      }
      fprintf(fTableTwo," %.2lf & ", chiSquared);
      fprintf(fTableThree," %.3lf & ", chiSquared);
      fprintf(fTableFour," %.4lf & ", chiSquared);
      fflush(fTableTwo);
      fflush(fTableThree);
      fflush(fTableFour);
    }
    fprintf(fTableTwo,"\n"); 
    fprintf(fTableThree,"\n"); 
    fprintf(fTableFour,"\n"); 
    fflush(fTableTwo);
    fflush(fTableThree);
    fflush(fTableFour);
  }
  fclose(fTableTwo);
  fclose(fTableThree);
  fclose(fTableFour);
}
/*************************************************************/
double integrand(long nDOF, double x) {
  return pow(x, (double)nDOF * 0.5 - 1.0) * exp(- 0.5 * x);
}


#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9

/*********************************/
int main(void) {

  long i,  j, p, k, flagPrecision, flagProbability;
  long numFMax = 10000, numPMax = 1000;
  double f, fOld, fNew, x, mySign, d, dTrue, dMin, dMax, n, e1;
  double precisionTolerance = 1.e-6, probabilityTolerance = 1.e-6;
  double vTargetProbability[7] = {0.3, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005};
  double targetProbability, probability;

  printf("\\begin{table} \n");
  printf("\\begin{center} \n");
  printf("\\begin{tabular}{rrrrrrrr} \n");
  printf("\\hline\n $n$ & $0.7$ & $0.8$ & $0.9$& $0.95$"
	 "&$0.98$&$0.99$&$0.995$\\\\\\hline \n");
  for(n=10.0; n<102.0; n += 5.0){
    printf("$ %lg $ ", n);

    for(p=0; p<7; p++){
      dMin = 0.0;
      dMax = 1.0;
      targetProbability = vTargetProbability[p];
      d = 0.5 * (dMin + dMax);
      dTrue = d;
      d *= sqrt(n);

      flagProbability = 0;
      for(j = 0; j < numPMax; j++){
	mySign = + 1.0;
	f = 0.0;
	fOld = f;
	fNew = f;
	x = (1.0 + 0.12/sqrt(n) + 0.11 / n) * d;
	e1 = - 2.0 * x * x;
	flagPrecision = 0;
	for(i = 1; i < numFMax; i++){
	  double di = (double)i, di2;
	  di2 = di * di;
	  f += (2.0 * mySign * exp(e1 * di2));
	  fOld = fNew;
	  fNew = f;
	  mySign *= (- 1.0);
	  // printf("%ld %lg\n", i, f);
	  if(fabs(fOld-fNew)<precisionTolerance){
	    flagPrecision = 1;
	    break;
	  }
	}
	if(flagPrecision == 0){
	  printf("Error: precision not reached\n");
	  exit(EXIT_FAILURE);
	}
	probability = f;
	if((probability - targetProbability) > probabilityTolerance){
	  // d cresce
	  dMin = dTrue;
	  dTrue = 0.5 * (dMin + dMax);
	  // printf("#  Growing: D = %lg\n", d);
	  d = dTrue *  sqrt(n);
	} else if((probability - targetProbability) < - probabilityTolerance) {
	  dMax = dTrue;
	  dTrue = 0.5 * (dMin + dMax);
	  // printf("#  Shrinking: D = %lg\n", d);
	  d = dTrue * sqrt(n);
	} else {
	  flagProbability = 1;
	  break;
	}
      }
      if(flagProbability == 0){
	printf("Error: probability did not converge\n");
	exit(EXIT_FAILURE);
      }
      printf(" & $ %.3lf $ ", dTrue);
    }
    printf("\\\\ \n");
  }
  printf("\\hline \n");
  printf("\\end{tabular} \n");
  printf("\\end{center} \n");
  printf("\\caption{Tavola delle probabilit\\`a per il test" 
	 " di Kolmogorov-Smirnov} \n");
  printf("\\end{table} \n");
}

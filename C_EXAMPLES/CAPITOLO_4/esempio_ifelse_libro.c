#include <stdio.h>

int main(int argc, char** argv) 
{
  double tIn, tOut, offset, conv;
  int option = 0;

  offset = 32.;
  printf("Premi\n'1' per trasformare da F a C\n"
         "'2' per trasformare da C a F\n\nScelta:");
  scanf("%d", &option);
  if (option == 1) 
    {
      conv = 5./ 9.;
      printf("Valore in gradi Fahrenheit= ");
      scanf("%lf",&tIn);
      tOut = (tIn - offset) * conv;
      printf("Valore in gradi Celsius= %f\n",tOut);
    }
  else
    {
      conv = 9./ 5.;
      printf("Valore in gradi Celsius= ");
      scanf("%lf", &tIn);
      tOut = tIn * conv + offset;
      printf("Valore in gradi Fahrenheit= %f\n",tOut);
    }
  return 0;
}

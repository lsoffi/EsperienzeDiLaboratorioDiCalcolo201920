#include <stdlib.h>
#include <stdio.h>
#define N 3
int main()
{
  int i;
  double data3[3] = {0.2};
  double data[N] = {1.0,2.2,3.3};
  double data2[] = {0.1,0.2,0.3};
  double data4[N];
  //inizializzazione di tutti gli elementi indicando dimensione 
  printf("  data[]=");
  for (i=0; i < N; i++)
    printf(" %f", data[i]);
  printf("\n");	
 
  //inizializzazione di tutti gli elementi senza indicare dimensione 
  printf("\n data2[]=");
  for (i=0; i < N; i++)
    printf(" %f", data2[i]);
  printf("\n");	

  // inizializzazione del primo elemento e gli altri a 0
  printf("\n data3[]=");
  for (i=0; i < N; i++)
    printf(" %f", data3[i]);
  printf("\n");	

  // inizializzazion con ciclo
  for (i=0; i < N; i++)
   data4[i] = 3.0; 
  printf("\n data4[]=");
  for (i=0; i < N; i++)
    printf(" %f", data4[i]);
  printf("\n");	
  return 0;
}

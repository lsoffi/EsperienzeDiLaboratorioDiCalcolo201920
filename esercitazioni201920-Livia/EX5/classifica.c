#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NC 24 

int main()
{
  int i,j;
  double dumb;
  int voti[NC],sortVoti[NC][2],temp0,temp1;
  FILE *fpr;

  for (i=0; i < NC; i++)
    {
      sortVoti[i][0] = sortVoti[i][1] = 0.0;
    }

  fpr=fopen("medie.txt","r");

  for (i=0;i<NC;i++)
    {
      fscanf(fpr,"%d %f %d",&sortVoti[i][0],&dumb,&sortVoti[i][1]);
      printf("%d %d\n",sortVoti[i][0],sortVoti[i][1]);
    }  

  printf("ordino\n");
  // BUBBLE SORT...
  
  int n1=0;  //Contatore 1
  int n2=0;  //Contatore 2
  int temp=0;  //Variabile di supporto
  
  for(n1=0; n1<NC; n1++){
    for(n2=0; n2<NC-n1-1; n2++){
      if(sortVoti[n2][1]<sortVoti[n2+1][1]){  //Scambio valori
                temp0=sortVoti[n2][0];
		temp1=sortVoti[n2][1];
                sortVoti[n2][0]=sortVoti[n2+1][0];
		sortVoti[n2][1]=sortVoti[n2+1][1];
                sortVoti[n2+1][0] = temp0;
		sortVoti[n2+1][1] = temp1;
      }
    }
  }

  for (i=0;i<NC;i++) printf("%d %d\n", sortVoti[i][0],sortVoti[i][1]);
  return 0;
  
}

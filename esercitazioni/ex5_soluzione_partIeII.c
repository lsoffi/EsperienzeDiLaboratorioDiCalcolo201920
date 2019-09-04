#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NC 10 

int main()
{
  int i,j,dumb,voto[NC],vendite[NC],ore[NC];
  double media[NC],sortmedia[NC][2],temp1,temp2;
  FILE *fpr;

  for (i=0; i < NC; i++)
    {
      media[i] = 0.0;
      sortmedia[0][i] = sortmedia[1][i] = 0.0;
      voto[i] = 0.0;
    }

  fpr=fopen("tri1.dat","r");
  for (i=0;i<NC;i++)
    {
      fscanf(fpr,"%i %i %i",&dumb,&vendite[i],&ore[i]);
      media[i]=((double)vendite[i])/ore[i];
      sortmedia[i][1]=media[i];
      sortmedia[i][0]=(double)(i+1); // voglio che i commessi vadano da 1 a 10 quindi sommo 1       
    }  

  /* Ordino i commessi in ordine di produttivita' */

  printf("ordino\n");
  /* BUBBLE SORT...
   * dopo ogni ciclo in i ho nella posizione i-esima l'elemento più grande di tutti
   * Il numero di confronti dunque è N-2 + N-1 + ... 1 = N*(N-1)/2 = O(N^2/2)  */
  for (i=0;i<NC-1;i++) // mi fermo a NC-2 poiché j parte da NC - 1 quindi se i=NC-1 il ciclo in j
                       // non verrebbe effettuato
    {
      for (j=NC-1; j > 0; j--)//j=NC-1 è l'elemento più in "basso" 0 quello più in "alto"
	// arrivo fino a i, infatti 
	// 1) dopo il primo ciclo in 0 ho sicuramente l'elemento 
       	//    più grande quindi è inutile fari confronti con l'elemento in 0
       	// 2) dopo il secondo ciclo in 0 e 1 ho i due elementi più grandi 
       	//    e quindi è inutile confrontarsi con loro
	{
	  if(sortmedia[j][1]>=sortmedia[j-1][1])
	    {
	      temp1=sortmedia[j-1][0];
	      temp2=sortmedia[j-1][1];
	      sortmedia[j-1][0]=sortmedia[j][0];
	      sortmedia[j-1][1]=sortmedia[j][1];
	      sortmedia[j][0]=temp1;
	      sortmedia[j][1]=temp2;
	    }
	}
    }

  for (i=0;i<NC;i++)
    {
      temp1=sortmedia[i][0];
      j=(int)(temp1-1); // i commessi vanno da 1 a 10 quindi devo sottrarre 1
      voto[j]=NC-i;
    }

  // stampo i commessi con i voti
  for (j=0;j<NC;j++)
    {
      printf("commesso n. %f Media= %f\n",sortmedia[j][0],sortmedia[j][1]);
      //printf("commesso n. %3i Ore %3i Vendite %5i Media= %7.2f voto= %3i\n",j+1,ore[j],vendite[j],media[j],voto[j]);
    }

}

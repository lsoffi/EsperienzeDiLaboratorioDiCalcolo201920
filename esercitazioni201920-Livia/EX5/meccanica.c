#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NC 24 

int main()
{
  int i,j,dumb,voto1[NC],voto2[NC],votoFinale[NC],indice[NC];
  double media[NC],sortmedia[NC][2],temp1,temp2;
  FILE *fpr, *fout;

  for (i=0; i < NC; i++)
    {
      indice[i] = 0.0;
      media[i] = 0.0;
      voto1[i] = 0.0;
      voto2[i] = 0.0;
      votoFinale[i] = 0.0;
      sortmedia[0][i] = sortmedia[1][i] = 0.0;
    }

  fpr=fopen("voti.txt","r");

  for (i=0;i<NC;i++)
    {
      fscanf(fpr,"%d %d %d %d",&dumb,&voto1[i],&voto2[i], &votoFinale[i]);
      media[i]=(double)(voto1[i]+voto2[i])/2.;
    }  

  int votiAlti = 0;
  int votiMedi = 0;
  int votiBassi = 0;
  int votiInsuff = 0;
  int bocciati =0;
  int oraleBuono=0;
  
  for (i=0;i<NC;i++){
    if (media[i]>=26.) votiAlti++;
    if (media[i]>=22. && media[i]<26.) votiMedi++;
    if (media[i]>=18. && media[i]<22.) votiBassi++;
    if (media[i]<18.){
      votiInsuff++;
    }
    if(votoFinale[i]>media[i])oraleBuono++;
    if(votoFinale[i]==0)bocciati++;
  }

  printf("Voti alti %d, Voti medi %d, Voti bassi %d, Voti Insufficienti %d \n", votiAlti,votiMedi,votiBassi,votiInsuff);
  printf("Orale Buono %d, Bocciati %d\n", oraleBuono, bocciati);

  //  fclose(fpr);
  fout=fopen("medie.txt","w");
  for (i=0;i<NC;i++) fprintf(fout, "%d %f %d \n", i,media[i],votoFinale[i]);
  fclose(fout);


  printf("ordino\n");
  // BUBBLE SORT...
  
  int n1=0;  //Contatore 1
  int n2=0;  //Contatore 2
  int temp=0;  //Variabile di supporto
  
  for(n1=0; n1<NC; n1++){
    for(n2=0; n2<NC-n1-1; n2++){
      if(votoFinale[n2]<votoFinale[n2+1]){  //Scambio valori
                temp=votoFinale[n2];
                votoFinale[n2]=votoFinale[n2+1];
                votoFinale[n2+1] = temp;
      }
    }
  }

  for (i=0;i<NC;i++) printf("%d\n", votoFinale[i]);
    return 0;
}

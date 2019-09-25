#include <stdio.h>
#include <stdlib.h>
#define NUM 5
/* Esempio di algoritmo di ordinamento
   Bubblesort */
int main(){

  int data[NUM], i, j, temp;

/* acquisizione dei dati */
  for(i = 0; i < NUM; i++){
    printf("dato %d=",i+1);
    scanf("%d",&data[i]);
  }
/*  ordinamento */  
  for (i = 0; i < NUM - 1; i++) {
     for (j = NUM - 1; j > i; j--) {
	if (data[j-1] > data[j]) {
           temp = data[j-1];
	   data[j-1] = data[j];
	   data[j] = temp;
	}
     }
  }
/*  stampa dei dati ordinati */    
  printf(" test j=%d %d %d %d %d %d\n",j,
  data[0],data[1],data[2],data[3],data[4]);
  exit(0);
}

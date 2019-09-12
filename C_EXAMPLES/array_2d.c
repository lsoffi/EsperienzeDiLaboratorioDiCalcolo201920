#include <stdlib.h>
#include <stdio.h>
#define N 3
#define M 2
int main()
{
  int i, j;
  int data[N][M];
  int data2[N][M] = {{1,2},{3,4},{5,6}};
  int data3[][M] = {{11,22},{33,44},{55,66}};
  //
  // inizializzazion con ciclo
  for (i=0; i < N; i++)
    for (j=0; j < M; j++)
      data[i][j] = 3.0; 
  printf("\n data[]=\n");
  for (i=0; i < N; i++)
    {
      for (j=0; j < M; j++)
	printf(" %4d", data[i][j]);
      printf("\n");
    }
  printf("\n");	

  // array inizializzato nella dichiarazione
  printf("\n data2[]=\n");
  for (i=0; i < N; i++)
    {
      for (j=0; j < M; j++)
	printf(" %4d", data2[i][j]);
      printf("\n");
    }
  printf("\n");

  // array inizializzato nella dichiarazione
  printf("\n data3[]=\n");
  for (i=0; i < N; i++)
    {
      for (j=0; j < M; j++)
	printf(" %4d", data3[i][j]);
      printf("\n");
    }
  printf("\n");
  return 0;
}

#include <stdlib.h>
#include <stdio.h>
int main()
{
  int i;
  int **pp;
  int *p[3];
  int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};

  // dereferenzio pp 
  pp = (int**) a;
  printf("*pp=%p\n", pp);

  printf("\n");
  // array e puntatori
  //printf("pa[1][1]=%d\n", pp[1][1]);//<--- SBAGLIATO!!!

  for (i=0; i < 3; i++)
    {
      p[i] = a[i];
      // o anche p[i] = &(a[i][0]) // punta alla righa
    }
  pp = p;
  printf("pp[2][2]=%d\n", pp[2][2]);
}

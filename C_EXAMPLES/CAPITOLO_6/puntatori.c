#include <stdlib.h>
#include <stdio.h>
int main()
{
  int a=2;
  int *pa;
  int data[10]={1,2,3,4,5,6,7,8,9,10};

  // stampa di un puntatore
  pa = &a;
  printf("pa=%p\n", pa);

  printf("\n");
  // array e puntatori
  pa = &(data[0]); 
  printf("1)pa=%p\n", pa);

  pa = data; 
  printf("2)pa=%p\n", pa);

  printf("\n");
  // dereferenziazione di un puntatore
  printf("*pa=%d\n", *pa);

  printf("\n");
  // aritmetic dei puntatori 
  printf("data[5]=%d *(pa+5)=%d pa[5]=%d\n", data[5], *(pa+5), pa[5]);
  // pa[i] = *(pa+i) 

  printf("\n");
  pa = pa + 4;// si sposta di sizeof(int)*4=16 byte
  printf("*pa=%d data[4]=%d\n", *pa, data[4]);

  printf("\n");
  pa = pa - 2; 
  printf("*pa=%d data[2]=%d\n", *pa, data[2]);
}

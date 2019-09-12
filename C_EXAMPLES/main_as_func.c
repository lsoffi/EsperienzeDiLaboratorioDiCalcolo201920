#include<stdlib.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
  int i;
  printf("Argomenti che hai passato:");
  for (i=0; i < argc; i++)
    {
      printf(" %s", argv[i]);
    }
  printf("\n");
}

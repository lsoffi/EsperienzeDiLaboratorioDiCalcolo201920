
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long factorial(unsigned long long n);

/*****************************************************************************/
int main(void)
{
  unsigned long long i;

  for(i = 0; i < 21; i++){
    printf("%Lu ! =  %Lu \n", i, factorial(i));
  }
}

/*****************************************************************************/
unsigned long long factorial(unsigned long long n)
{
  if(n == 0) return 1;
  return (n * factorial(n-1));
}


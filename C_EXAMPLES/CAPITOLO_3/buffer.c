#include<stdio.h>
#include<math.h>
#define USE_FFLUSH 2
int main(int argc, char**argv)
{
  int i;
  for (i=0; i < 50; i++)
    {
      printf("X");
    }
#if USE_FFLUSH==1
  fflush(stdout);
#elif USE_FFLUSH==2
  printf("\n");
#endif
  while(1);
}

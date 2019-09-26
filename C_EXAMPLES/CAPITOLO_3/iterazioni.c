#include<stdio.h>
#include<math.h>

int main(int argc, char**argv)
{
  int i;
  // do ... while()
  //
  printf("do....while ()\n");
  i=0;
  do 
    {
      printf("i=%d\n", i);
      i++;
    }
  while (i < 3);

  // while () ....
  printf("\nwhile () ....\n");
  i=0;
  while (i < 3)
    {
      printf("i=%d\n", i);
      i++;
    }

  // che è equivalente a: 
  printf("\nfor () ...\n");
  for (i=0; i < 3; i++)
    {
      printf("i=%d\n", i);
    }
  return 0;
}

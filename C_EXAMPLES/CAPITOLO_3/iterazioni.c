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

  //uso di break (si può usare in tutti i costrutti per iterazioni)
  // while () ....
  printf("\nbreak in ciclo while () ....\n");
  i=0;
  while (1)
    {
      printf("i=%d\n", i);
      i++;
      if (i == 3)
        break;
    }

  // uso di continue
  printf("\ncontinue in ciclo while () ....\n");
  i=0;
  while (i < 3)
    {
      if (i==1)
        {
          i++;
          continue;
        }
      printf("i=%d\n", i);
      i++;
    }
  return 0;
}

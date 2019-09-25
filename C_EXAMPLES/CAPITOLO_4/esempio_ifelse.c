#include<stdio.h>
int main(int argc, char** argv)
{
  int a; 
  
  printf("Immetti un intero a\n");
  scanf("%d", &a);
  /* es. 1 */
  if (a > 0)
    printf("a è maggiore di 0!\n");

  /* es. 2 */
  if (a < 0)
    printf("a è negativo!\n");
  else
    printf("a è positivo o 0!\n");

  /* es. 3 */
  if (a==1) 
    /* attenzione a non usare '=' ossia scrivere 
     * if (a=1) ... è un errore molto frequente!
     */
    {
      printf("a è proprio 1!\n");
    }
  else
    {
      printf("a non è 1\n"); 
    }

  return 0;
}

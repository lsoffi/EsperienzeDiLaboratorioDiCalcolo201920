#include<stdio.h>
int main(int argc, char** argv)
{
  int a; 
  char c; 
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

  /* operatore ternario ? */
  printf("a è %s\n", (a > 0) ? "positivo" : "negativo" );
  c = (a > 0) ? 'p' : 'n';
  printf("c = '%c'\n", c);   
  /* (condizione) ? <espressioneA se condizione vera> : <espressioneB se condizione falsa> 
   * espressioneA o espressioneB a seconda della condizione vengono valutate 
   * ed il risultato della valutazione viene restituito dall'operatore.
   * Nei due esempi viene restituita una stringa o un carattere a seconda della condizione.  
   */

  return 0;
}

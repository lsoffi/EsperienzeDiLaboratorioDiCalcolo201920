#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char *argv[])
{
  const int nmax=36;
  int N=20; 
  double ptot,pocket=0.0, puntata;
  char giocata;
  char dummy[256];
  int fine, vinto, res, ngioc;
  int i, n;
  srand(0);
  pocket=100.0;
  fine=0;
  while (!fine)
    {
      printf("Numero giocate (10/20)? ");
      fine=1;
      res=scanf("%d", &N);
      if (res < 1)
        {
          printf("Problema nella conversione\n");
          scanf(" %256s", dummy);
          fine=0;
        }
      if (N!=10 && N!=20)
        {
          printf("Devi scegliere 10 o 20 giocate!\n");
          fine=0;
        }
    }
  ptot=0.0;
  for (i = 0; i < N; ++i) 
    {
      puntata=-1.0;

      fine=0;
      while (!fine)
        {
          fine=1;
          printf("\nGiocata N. %d\n", i+1);
          printf("Quanto vuoi puntare (Hai %4.2f euro)? ", pocket);
          res=scanf(" %lf", &puntata);
          if (res < 1)
            {
              printf("Problema nella conversione\n");
              scanf(" %256s", dummy);
              //printf("dummy[0]=%uc dummy[1]=%uc\n", dummy[0], dummy[1]);
              fine=0;
              continue;
            }  
          if (puntata < 0 || puntata > pocket)
            {
              printf("Puntata non valida!\n");
              fine=0; 
            }
        }
      ptot+=puntata;
      pocket -= puntata;
      ngioc=-1;
      while (ngioc < 0)
        {
          printf("Scegli il tipo di giocata (E/O/M/P):");
          // il precedente carriage return rimane nel buffer per quello va messo lo spazio
          res=scanf(" %c", &giocata);
          if (res < 0)
            {     
              printf("Problema nella conversione\n");
              scanf(" %256s", dummy);
              continue;
            }         
          //printf("giocata=%c\n",giocata);
          if (giocata=='E')
            {
              ngioc=0;
            }
          else if (giocata=='O')
            {
              ngioc=1;
            }
          else if (giocata=='M')
            {
              ngioc=2;
            }
          else if (giocata=='P')
            {
              ngioc=3;
            }
          else
            {
              printf("giocata non valida, riprova...\n");
              ngioc=-1;
            }
        }
      n=rand()%nmax + 1;
      vinto=0;
      if (n%2==0 && ngioc==0)
        vinto=1;
      if (n%2==0 && ngioc==1)
        vinto=1;
      if (n <= 18 && ngioc==2)
        vinto=1;
      if (n > 18 && ngioc==3)
        vinto=1;
      if (vinto)
        {
          pocket+=2.0*puntata;
          printf("Hai vinto!\n");
          printf("Hai %4.2f euro nel portafoglio\n", pocket);
        } 
      else
        {
          printf("Peccato, non hai vinto...\n");
          printf("Il gioco porta alla dipendenza, smetti!\n"); 
          if (pocket <= 0)
            {
              printf("Hai effettuato N. %d mani\n", i);
              printf("Hai terminato i soldi, il gioco è finito\n");
              break;
            }
        }
    }
  printf("\nHai effettuato N. %d mani\n", i);
  printf("Ammontare totale puntate: %4.2f\n", ptot);
  printf("Euro nel portafoglio: %4.2f\n", pocket);
  return 0;
}

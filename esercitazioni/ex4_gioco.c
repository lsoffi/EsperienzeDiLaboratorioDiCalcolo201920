#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char *argv[])
{
  const int nmax=36;
  int N=20; 
  double ptot,pocket=0.0, puntata;
  char giocata;
  int c, fine, vinto, res, ngioc;
  int i, n;
  srand(0);
  pocket=100.0;
  fine=0;
  while (!fine)
    {
      printf("Numero mani (10/20)? ");
      fine=1;
      res=scanf("%d", &N);
      if (ferror(stdin)||feof(stdin))
        {
          // qui ci arriva se si preme CTRL-D = EOF
          printf("\n");
          clearerr(stdin);
          fine=0;
          continue;
        }
          
      if (res < 1)
        {
          printf("Problema nella conversione\n");
          fine=0;
        }
      else if (N!=10 && N!=20)
        {
          printf("Devi scegliere 10 o 20 giocate!\n");
          fine=0;
        }
      while ((c=getchar())!='\n'); // svuota il buffer di tutti i caratteri eccetto '\n'=newline
    }
  ptot=0.0;
  for (i = 0; i < N; ++i) 
    {
      puntata=-1.0;

      fine=0;
      while (!fine)
        {
          fine=1;
          printf("\nMano N. %d\n", i+1);
          printf("Quanto vuoi puntare (Hai %4.2f euro)? ", pocket);
          res=scanf(" %lf", &puntata);
          if (ferror(stdin)||feof(stdin))
            {
              // qui ci arriva se si preme CTRL-D = EOF o se c'è un error
              printf("\n");
              clearerr(stdin);
              fine=0;
              continue;
            }
 
          if (res < 1)
            {
              printf("Problema nella conversione\n");
              fine=0;
            }  
          else if (puntata < 0 || puntata > pocket)
            {
              printf("Puntata non valida!\n");
              fine=0; 
            }
          else
            printf("ok punti %4.2f\n", puntata);
          while ((c=getchar())!='\n'); // svuota il buffer di tutti i caratteri eccetto '\n'=newline
        }
      ptot+=puntata;
      pocket -= puntata;
      ngioc=-1;
      while (ngioc < 0)
        {
          printf("Scegli il tipo di giocata (E/O/M/P):");
          // il precedente carriage return rimane nel buffer per quello va messo lo spazio
          res=scanf(" %c", &giocata);
          if (ferror(stdin)||feof(stdin))
            {
              // qui ci arriva se si preme CTRL-D = EOF o se c'è un error
              printf("\n");
              clearerr(stdin);
              fine=0;
              continue;
            }
          if (res < 0)
            {     
              printf("Problema nella conversione\n");
            }         
          //printf("giocata=%c\n",giocata);
          else if (giocata=='E')
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
          while ((c=getchar())!='\n'); // svuota il buffer di tutti i caratteri eccetto '\n'=newline
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

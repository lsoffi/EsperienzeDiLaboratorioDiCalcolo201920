#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main()
{
  //dichiaro le variabili
  float credit, bet;
  int x,num;
  int mani;
  //inizializzo il seme per l'algoritmo rand()
  int seed;
  seed=time(0);
  srand(seed);

  //stampo le istruzioni per l'utente
  printf("Benvenuto! Questo programma simula il gioco della roulette con numeri interi compresi tra 1 e 36.\n");

  credit=100;
  //chiedo quanto si vuole scommettere
  do{
  printf("Quanto vuoi scommettere [tra 2 e 10 euro se puoi permetterteli!]\n");
  scanf("%f", &bet);
  }while(bet<2 || bet > 10 || bet > credit);

  //su che numero vuoi scommettere?
  do{
  printf("su che numero vuoi scommettere? [1-36]\n");
  scanf("%d", &num);
  }while(num<1 || num> 36);


  do{
    //genero il numero tra 1 e 36
    x = rand()%36 + 1;
    if(num==x){
      credit+=2*bet;
      printf("E' uscito il numero %d. Congratulazioni hai vinto, il tuo nuovo credito e' %f\n", x, credit);
    }else {

      credit-=bet;
      printf("E' uscito il numero %d. Peccato hai perso, il tuo nuovo credito e' %f\n", x, credit);
    }
    mani++;
  }while(mani<20 && credit >=2.);

  if(credit >0)printf("Il gioco e' finito. Hai giocato per %d mani e il tuo credito finale e' %f\n", mani, credit);
  else printf("Il gioco e' finito. Hai giocato per %d mani e il tuo credito non e' piu' sufficiente a continuare a giocare.\n",mani);
  return 0;
}

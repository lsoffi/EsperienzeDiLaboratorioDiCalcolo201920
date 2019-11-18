#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main()
{
  //dichiaro le variabili
  int x, N; 
  int n, nP=0, nD, nA, nB;
  
  //inizializzo il seme per l'algoritmo rand()
  int seed;
  seed=time(0);
  srand(seed);

  //stampo le istruzioni per l'utente
  printf("Benvenuto! Questo programma simula il gioco della roulette con numeri interi compresi tra 1 e 36. Per favore inserisci il numero di lanci che vuoi fare:\n");
  //acquisisco il numero di lanci N
  scanf("%d", &N);

  //iterare sul numero di lanci
  for (int i=0; i < N; i++) {
    //genero il numero tra 1 e 36
    x = rand()%36 + 1;
    //conto se il numero e' apri, dispari alto o basso
    if(x%2==0){
      nP++;
    }else {
      nD++;
    }
    if(x<19){
      nB++;
    } else{
      nA++;
    }
    if(x%2==0 && x<19) printf("Hai generato %d. Il numero e' pari e basso\n", x);
    if(x%2==0 && x>=19) printf("Hai generato %d. Il numero e' pari e alto\n", x);
    if(x%2==1 && x<19) printf("Hai generato %d. Il numero e' dispari e basso\n", x);
    if(x%2==1 && x>=19) printf("Hai generato %d. Il numero e' dispari e alto\n", x);

    
  }
  //stampo le frequenze degli eventi
  printf("frequenza P=%.7f; frequenza D=%.7f\n", 
         ((double)nP)/N, ((double)nD)/N);
  printf("frequenza B=%.7f; frequenza A=%.7f\n", 
         ((double)nB)/N, ((double)nA)/N);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NMAX 20

/************************************************************/
/****************DICHIARAZIONE DI FUNZIONI*******************/
/*tipo nome_funzione (TIPI DEI VALORI IN IN INPUT);*/
void PrintInitMessage(void);
int getN(void);
int getto(void);
int decido(int ,int);
void clearVec(int *, int);
void mano(int*, int*, int);
/************************************************************/
/************************MAIN*******************************/

int main(void){
  //*************** dichiarazione variabili e inizializzazione algoritmo**********//
  int n;
  srand48(time(0));
  int results_A[NMAX], results_B[NMAX];
  //PUNTO1: ********** STAMPA MESSAGGIO INIZIALE  ***********//

  PrintInitMessage();
  
  //PUNTI 2-3: ************* LETTURA DATI INIZIALI**********//

  n=getN();
	   
  //PUNTI 4-5-6

  //********* svuoto i vettori contatori
  clearVec(results_A,n);
  clearVec(results_B,n);


  //********* simulo la partita di morra cinese
  for(int i=0;i<n;i++){
    mano(results_A,results_B,i);
  }

  //PUNTO 7
  printf("I risultati finali sono  A: %d vs  B: %d su %d mani giocate \n", results_A[n-1],results_B[n-1],n);
  if(results_A[n-1]==results_B[n-1]) printf("La partita e' finita in parita'");
  else {
    printf("Il vincitore della partita e' il giocatore ");
    if(results_A[n-1]>results_B[n-1]) printf(" A\n");
    if(results_A[n-1]<results_B[n-1]) printf(" B\n");
  }

  //PUNTO 8
  FILE* fp;
  fp = fopen("punteggio.dat", "w+");
  for(int i=0;i<n;i++) fprintf(fp,"%d %d %d\n",i,results_A[i],results_B[i]);
  fclose(fp);
}


/************************************************************/
/**************DEFINIZIONE DI FUNZIONE***********************/
/****************(PROTOTIPI DI FUNZIONI)*********************/

/*tipo nome_funzione (tipo var1, tipo var2,....){
  
  blocco del codice
}*/

void PrintInitMessage(void){
  
  fprintf(stdout,"\n");
  fprintf(stdout,"************************************************************\n");
  fprintf(stdout,"QUESTO PROGRAMMA SIMULA IL GIOCO DELLA MORRA CINESE\n");
  fprintf(stdout,"RICHIEDENDO IN INPUT IL NUMERO DI GETTI DA SIMULARE \n");
  fprintf(stdout,"************************************************************\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"------------------------------------------------------------\n");
  fprintf(stdout,"***************************LEGENDA:*************************\n");
  fprintf(stdout,"1=CARTA\n2=FORBICI\n3=SASSO\n");
  fprintf(stdout,"------------------------------------------------------------\n");
  fprintf(stdout,"\n");
}


int getN(){
  int n,check=0 ;
  do{
    printf("Inserisci il numero di getti (massimo n. consentito e' %d): \n", NMAX);
    scanf("%d", &n);
    if(n>0 && n<=NMAX){
      check=1;
    }else{
      printf("Attenzione! Il n. di getti non puo' essere negativo o maggiore di %i\n",NMAX);
    }
  }while(!check);

  return n;
}


//funzione che restituisce un n. intero tra [1,3] )
int getto(void){
  return((int)(drand48()*3)+1);
}

void clearVec(int *v, int n){

  for(int i = 0; i< n;i++){
    v[i] = 0;
  }

}
int decido(int a, int b){
/*per cercare il vicitore ho pensato alla seguente strategia: assegno a
    CARTA(C)   il n. 1
    FORBICI(F) il n. 2
    SASSO(S)   il n. 3
    (quindi estraggo un numero intero tra 1 e 3)
    Se sottraggo il valore estratto del giocatore B a quello del giocatore A trovo che
    
    A   B   diff      RISULTATO
    ----------------------------------
    C   S   1-3=-2    VITTORIA di A
    C   F   1-2=-1    PERDITA  di A
    S   C   3-1= 2    PERDITA  di A
    S   F   3-1= 1    VITTORIA di A   
    F   C   2-1= 1    VITTORIA di A
    F   S   2-3= -1   PERDITA  di A
    
    quindi significa che ogni volta che diff=-2 o 1 allora ha vinto il giocatore A
    se invece diff=2 o -1 ha vinto il giocatore B
    SE I SEGNI DI A e B SONO UGUALI (es. CARTA-CARTA, FORBICI-FORBICI,SASSO-SASSO)
    si effettua di nuovo un getto senza considerare la condizione di parita' 
  */

  int diff = a-b;
  int winner;
  if((diff==-2) || (diff==1)) winner=1;
  else if ((diff==-1) || (diff==2)) winner= 2;
  else winner= 3;
  if(winner==1) printf("A: %d, B: %d, Vince: A \n", a, b);
  else if(winner==2) printf("A: %d, B: %d, Vince: B \n", a, b);
  else printf("A: %d, B: %d, Pari \n", a, b);
  return winner;

}


void mano(int * results_A, int * results_B, int i){
  int value_A, value_B,result;  
  value_A=getto();
  value_B=getto();

  result = decido(value_A,value_B); //la funzione torna 1 se vince A, 2 se vince B, 3 se c'e' parita'
  
  if(result==1){
    results_A[i]= results_A[i-1]+1;
    results_B[i]=results_B[i-1];
  }else if(result==2){
    results_A[i]=results_A[i-1];
    results_B[i]= results_B[i-1]+1;
  }else{
    results_A[i]=results_A[i-1];
    results_B[i]=results_B[i-1];
  }
  
  //  printf("I risultati parziali sono  A: %d vs  B: %d su %d partite giocate \n", results_A[i],results_B[i],i);
}

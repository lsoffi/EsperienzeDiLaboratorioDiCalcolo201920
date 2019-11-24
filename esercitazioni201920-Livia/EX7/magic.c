#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 3


/***************DICHIARAZIONE DI FUNZIONI********************/ 
void getMatrix( int m[][N], int n);
void readMatrix( int m[][N], int n);     
void printMatrix( int m[][N], int n);     
void verifyMatrix( int m[][N], int n);
void createMatrix( int m[][N], int n);

/************************MAIN*******************************/
int main(){
  int m[N][N];
  int t[N][N];
  int scelta=0;
  srand(time(0));
  // stampare messaggio di benvenuto
  printf("Benvenuto! Questo programma analizza i quadrati magici \n");

  //far scegliere l'utente su come riempire la matrice
  printf("Premi 1/ per riempire il quadrato da tastiera o 2/ per leggere i valori da file. \n");
  do{
    scanf("%d", &scelta);
  }while(scelta !=1 && scelta !=2);

  // riempire la matrice nei due modi possibili
  if(scelta ==1) getMatrix(m,N);
  else if(scelta==2) readMatrix(m,N);


  //stampare la matrice
  printMatrix(m, N);

  //verificare se il quadrato sia magico
  verifyMatrix(m, N);
  
  //generare un quadrato nuovo
  createMatrix(t,N);
  //stampare la matrice
  printMatrix(t, N);
  //verificare se il quadrato sia magico                                                                                                                    
  verifyMatrix(t, N);

  return 0;
}
  
/**************DEFINIZIONE DI FUNZIONE***********************/


void getMatrix(int m[][N], int n) {
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++){
      scanf("%2d", &m[i][j]);
    }
  }
}

  
void readMatrix(int m[][N], int n) {

    int i, j;
    FILE* fp;
    char string[10];
    printf("Inserisci il nome del file da cui leggere i numeri: \n");
    scanf("%s",string);
    fp=fopen(string, "r+");
    for (i=0;i<n;i++) {
      fscanf(fp,"%2d %2d %2d", &m[i][0], &m[i][1],&m[i][2]);
}

}

void printMatrix(int m[][N], int n) {

    int i, j;

    for (i=0;i<n;i++) {
        for (j=0;j<N;j++)
            printf("%2d", m[i][j]);
        printf("\n");
    }
}


void verifyMatrix( int m[][N], int n){
     int i, r1 = 0, r2 = 0;
     
     // somma della prima riga
     for(i=0;i<n;i++)
        r1 += m[0][i];
     
     // somma della seconda riga
     for(i=0;i<n;i++)
        r2 += m[1][i];
     
     // se i due risultati precedenti sono uguali, continuo i controlli
     if(r2 == r1)
     {
        r2 = 0;
        
       // sommo la terza riga 
       for(i=0;i<n;i++)
         r2 += m[2][i];
        
       // se il risultato è uguale a quello delle altre righe continuo 
       if(r2 == r1)
       {
          r2 = 0;
          
          // somma della prima colonna
          for(i=0;i<n;i++)
          r2 += m[i][0];
          
          // se il risultato è uguale ai precedenti
          if(r2 == r1)
          {
             r2 = 0;
          
             // somma della seconda colonna
             for(i=0;i<n;i++)
             r2 += m[i][1];
             
             // se il risultato è uguale ai precedenti
             if(r2 == r1)
             {
                r2 = 0;
              
                // somma della terza colonna
                for(i=0;i<n;i++)
                r2 += m[i][2];
                
                // se il risultato è uguale ai precedenti
                if(r2 == r1)
                {
                  r2 = 0;
          
                  // somma della prima diagonale
                  r2 = (m[0][0] + m[1][1] + m[2][2]);
                  
                  // se il risultato è uguale ai precedenti
                  if(r2 == r1)
                  {
                    r2 = 0;
               
                    // somma della seconda diagonale
                    r2 = (m[2][2] + m[1][1] + m[0][0]);
                  }
                }
             }
          }
       }
     }
        
    if(r1 == r2)
        printf(" E' un quadrato magico!\n\n La costante magica e': %d\n", r1);
    else 
        printf(" Non e' un quadrato magico!\n");
    }



void createMatrix(int m[][N], int n) {
  int ok =0;
  int max= N*N;
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++){
      m[i][j]=0;
    }
  }
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++){
      do{
	m[i][j]=rand()%max + 1;
	//	printf("%d\n",m[i][j]);
	ok = 1;
	for (int ii=0;ii<n;ii++){
	  for (int jj=0;jj<n;jj++){
	    if(m[i][j]==m[ii][jj] && (ii!=i || jj!=j) ) ok=0;
	    //	    printf("%d %d %d %d ---> m[%d][%d] = %d ----> m[%d][%d] = %d ok ? %d\n", ii, jj, i, j, ii, jj, m[ii][jj],i, j, m[i][j], ok);
	  }
	}
      }while(ok==0);
    }
  }
}

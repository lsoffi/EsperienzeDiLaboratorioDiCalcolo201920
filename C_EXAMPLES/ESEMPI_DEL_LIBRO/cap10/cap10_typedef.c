

#define MYFLOAT  0
#define MYDOUBLE 1
#define POSIZIONE MYFLOAT  /*questa e' la riga da cambiare*/

#if POSIZIONE == MYFLOAT
typedef float posizione;
#elif POSIZIONE == MYDOUBLE
typedef double posizione;
#endif

main(){
  if (POSIZIONE == MYFLOAT) {
    printf("#Le variabili di tipo POSIZIONE sono dei float.\n");
  } else if (POSIZIONE == MYDOUBLE) {
    printf("#Le variabili di tipo POSIZIONE sono dei double.\n");
  } else{
    printf("Il programma termina a causa di un errore:\n");
    printf("  il valore di POSIZIONE non e' un valore previsto.\n");
    exit(-9);
  }
}

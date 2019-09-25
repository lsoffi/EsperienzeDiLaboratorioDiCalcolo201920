#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 256
#define MAX_WORDS  100

main() {
   char c, line[MAX_STRING], temp[MAX_STRING];
   char words[MAX_WORDS][MAX_STRING];
   char separator = ' ';
   int i = 0, j, k = 0, jchar, kchar;
   int templen, wordcount, charcount;
   int wordlength[MAX_WORDS], swap = 0;
   printf("\n Inserire una frase da scomporre e riordinare "
   " (il tasto INVIO per terminare l'input, max 255 caratteri): ");
   while ((c = getchar()) != '\n' && i < MAX_STRING) {
      line[i++] = c;
   }
   charcount = i;
/*  spostiamo caratteri consecutivi diversi dallo spazio bianco
    nell'array words
    l'indice j del ciclo non si usa direttamente
    al suo posto usiamo jchar per gestire spazi bianchi consecutivi  */
   for (j = 0; j < charcount; j++) {
     if (line[jchar] != separator) {
       words[wordcount][k++] = line[jchar];
     }
     else {
       words[wordcount][k+1] = '\0';
       wordlength[wordcount] = k+1;
       wordcount++;
 /*  ignora spazi bianchi consecutivi */
       if (line[jchar+1] == separator) {
         jchar++;
       }
       k = 0;
     }
     jchar++;
   }
   words[wordcount][k+1] = '\0';
   wordlength[wordcount] = k+1;
/*   confrontiamo le parole a due a due e decidiamo se 
     bisogna scambiarle ridefinendo il valore della variabile swap
     swap = 1  da scambiare
     swap = -1 da non scambiare
     swap = 0  da esaminare   */    
   for (k = 0; k <= wordcount; k++) {     
     for (i = wordcount; i > k; i--) {
	 kchar = 0;
       while (swap == 0 ) {	 
	 while (words[i][kchar] != '\0' 
	 && words[i-1][kchar] != '\0' 
	 && words[i][kchar] ==  words[i-1][kchar]) {
           kchar++;
	 }
	 if (words[i][kchar] == '\0' && words[i-1][kchar] == '\0') {
	   swap = -1;
	 } else if (words[i][kchar] == '\0' 
	   || words[i][kchar] < words[i-1][kchar]) {
	     swap = 1;
	 } else {
	     swap = -1;
	 }
       }
/*   confronta le parole tra loro e le ordina usando
     un array di appoggio temp   */         
       if (swap == 1) {
	 for (j = 0; j < MAX_STRING; j++) {
	   temp[j] = words[i-1][j];
	   templen = wordlength[i-1];
	   words[i-1][j] = words[i][j];
	   wordlength[i-1] = wordlength[i];
	   words[i][j] = temp[j];
	   wordlength[i] = templen;
	 }	    
       }
       swap = 0;
     }
   }
/*   stampa dell'array ordinato    */
   for (i = 0; i <= wordcount; i++) {
     printf(" Parola numero %d ", i);
     for (j = 0; j <= wordlength[i]; j++) {
       printf("%c", words[i][j]);
     }
     printf("\n");
   } 
}

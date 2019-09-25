#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 256
#define MAX_WORDS  100

main() {
  char c, line[MAX_STRING];
  char *wordaddress[MAX_WORDS], *pc, *temp, *p0, *p1;
  char separator = ' ';
  int i = 0, j = 0, k = 0, min;
  int templen;
  int wordcount = 0, charcount = 0;
  int wordlength[MAX_WORDS], swap = 0;
  printf("\n Inserire una frase da scomporre e riordinare\n "
    " (il tasto INVIO per terminare l'input, "
    "max 255 caratteri)\n --> ");
  while ((c = getchar()) != '\n' && i < MAX_STRING) {
     line[i++] = c;
  }
  charcount = i;
  line[charcount] = '\0';
  for (pc = &line[0]; pc < &line[0] + charcount; pc++) {
    if (*pc == separator && *(pc + 1) != separator) {
      wordlength[k] = j;
      wordaddress[k] = pc - j;      
      k++;
      j = 0;
    } 
    else if (*pc == separator && *(pc + 1) == separator) {
    }   
    else {
      j++;
    }
  }
  wordlength[k] = j;
  wordaddress[k] = pc - j;
  wordcount = k;
  for (k = 0; k <= wordcount; k++) {          
     for (i = wordcount; i > k; i--) {
       swap = 0;             
       min = wordlength[i];
       if(min > wordlength[i - 1]) { 
         min = wordlength[i - 1];
       }
       p0 = wordaddress[i - 1];
       p1 = wordaddress[i];
       j = 0;       
       while (swap == 0 && j < min) {
         if (*(p1 + j) < *(p0 + j)) {
	   swap = 1;
	 } else if (*(p0 + j) < *(p1 +j)) {
	   swap = -1;
	 }
	 j++;
       }
       if (swap == 1) {      
         temp = wordaddress[i - 1];
	 templen = wordlength[i - 1];
	 wordaddress[i - 1] = wordaddress[i];
	 wordlength[i - 1] = wordlength[i];
	 wordaddress[i] = temp;
	 wordlength[i] = templen;
	 swap = 0;
       }       
     }
   }
   for (i = 0; i <= wordcount; i++) {
     printf(" Parola numero %d ", i + 1);
     for (j = 0; j < wordlength[i]; j++) {
        pc = wordaddress[i];
	printf("%c",*(wordaddress[i] + j));
     }
     printf("\n");
   } 
}

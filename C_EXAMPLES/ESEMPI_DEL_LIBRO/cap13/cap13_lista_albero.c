
/* un terzo esempio di uso di liste: qui creo un albero binario. */
/* uso una funzione ricorsiva */

#include <stdio.h>
#include <math.h>

#define MY_MAX 100

#define MY_SUCCESS 0
#define MY_RUIN -9

FILE *fInput;
char *fInputName = "leopardi2.dat";

void myStart(void);
void openFile(void);

struct word{
  char *pointerToString;
  struct word *nextWordLeft;
  struct word *nextWordRight;
};
struct fromWord{
  int myEnd;
  char *scratchPointer;
};

struct fromWord readWord(void);
struct word *addToTree(struct word *, char *);
void printTreeInAlphabeticOrder(struct word *);

/*****************************************************************************/
int main(void)
{
  struct fromWord fW1;
  
/* creo la lista e visto che all'inizio e' vuota la inizializzo a NULL */
  struct word *treeRoot = NULL;

  myStart();
  openFile();
  
  fW1.myEnd = 0;
  while(fW1.myEnd != 1){
    fW1 = readWord();
    treeRoot = addToTree(treeRoot, fW1.scratchPointer); 
  } 
  fclose(fInput);
  printTreeInAlphabeticOrder(treeRoot); 
}

/*****************************************************************************/
void myStart(void)
{
  printf("# Costruiremo un albero binario\n");
}

/*****************************************************************************/
void openFile(void)
{
  fInput = fopen(fInputName,"r");
  if(fInput == NULL){
    printf("abort: impossibile aprire il file di input"
	   " in lettura: %s\n",
	   fInputName); 
    exit(MY_RUIN);
  }
  printf("# E' stato aperto il file di input: %s\n",
	 fInputName); 
}

/*****************************************************************************/
struct fromWord readWord(void)
{
  int j = 0;
  char myString[MY_MAX], myFlag = 1;
  char *thisPointer;
  struct fromWord fW1;

  while((j < MY_MAX) && (myFlag == 1)){ 
    myString[j] = fgetc(fInput);
    if(myString[j] == ' '){
      myString[j] = '\0';
      myFlag = 0;
    }
    else if(myString[j] == '\n'){
      j--;
    }
    else if(myString[j] == EOF){
      fW1.myEnd = 1; 
      myString[j] = '\0'; 
      myFlag = 0;
    }
    j++;
  }

  /* per sicurezza mi sto riservando un carattere in piu' oltre 
    al terminatore \0 */
  if(j >= MY_MAX - 1){
    printf("Interruzione del programma: la parola era troppo lunga.\n");
    printf("Ricompilare con un valore di MY_MAX piu grande, era %d.\n",
	   MY_MAX);
    exit(MY_RUIN);
  }
  thisPointer = (char *) malloc(strlen(myString) + 1);
  if(thisPointer == NULL){
    printf("Interruzione del programma: fallita malloc 1\n");
    exit(MY_RUIN);
  }
  strcpy(thisPointer, myString);
  fW1.scratchPointer = thisPointer;
  /* printf("Parola di lunghezza %d: %s\n",strlen(thisPointer),thisPointer); */

  return fW1;
}

/*****************************************************************************/
struct word* addToTree(struct word* inputWord, 
		       char *localPointer)
{
  int stringDifference;
  if(inputWord == NULL){
    inputWord = 
      (struct word *) malloc(sizeof(struct word));  
    if(inputWord == NULL){
      printf("Interruzione del programma: fallita malloc 1\n");
      exit(MY_RUIN);
    }
    inputWord->pointerToString = localPointer;
    inputWord->nextWordLeft = NULL;
    inputWord->nextWordRight = NULL;
  } else if((stringDifference = 
	     strcmp(inputWord->pointerToString,   
		    localPointer)) != 0){
    if(stringDifference > 0) {
      inputWord->nextWordLeft = 
	addToTree(inputWord->nextWordLeft,localPointer);
    } else {
      inputWord->nextWordRight =
	addToTree(inputWord->nextWordRight, localPointer);
    }
  } 
  return inputWord;
}

/*****************************************************************************/
void printTreeInAlphabeticOrder(struct word* inputWord)
{
  if(inputWord != NULL){
    printTreeInAlphabeticOrder(inputWord->nextWordLeft);
    printf("%s\n",inputWord->pointerToString);
    printTreeInAlphabeticOrder(inputWord->nextWordRight);
  }
}

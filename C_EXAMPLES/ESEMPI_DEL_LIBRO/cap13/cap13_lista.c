/* un primo esempio di uso di liste: leggo un testo e creo un dizionario */

#include <stdio.h>
#include <math.h>

#define MY_MAX 100

#define INVERSE_LIST 0
#define DIRECT_LIST 1

#define MY_SUCCESS 0
#define MY_RUIN -9

FILE *fInput;
char *fInputName = "leopardi.dat";

int listType = INVERSE_LIST;
//int listType = DIRECT_LIST;
char myString[MY_MAX];

void myStart(void);
void openFile(void);
int readWord(void);
void buildInverseList(void);
void buildDirectList(void);
void printInverseList(void);
void printDirectList(void);

/* creiamo il puntatore che indica la lista 
   e visto che all'inizio la lista e' vuota 
   lo inizializziamo a NULL */

struct word{
  char *pointerToString;
  struct word *pointerToNextWord;
} *wordList = NULL;

struct word *pointerStart;

/*****************************************************************************/
int main(void)
{
  int myEnd = 0;

  myStart();
  openFile();
  
  while(myEnd != 1){
    myEnd = readWord();
    switch(listType){
    case INVERSE_LIST: 
      buildInverseList(); 
      break;
    case DIRECT_LIST: 
      buildDirectList(); 
      break;
    default: 
      printf("Interruzione programma: caso lista non previsto %d %d.\n",
	     INVERSE_LIST, listType);
      exit(-9); 
    }
  } 
  fclose(fInput);

  switch(listType){
  case INVERSE_LIST: 
    printInverseList(); 
    break;
  case DIRECT_LIST: 
    printDirectList(); 
    break;
  default: 
    printf("Interruzione programma: caso lista non previsto %d %d.\n",
	   INVERSE_LIST, listType);
    exit(-9); 
  }
}

/*****************************************************************************/
void myStart(void)
{
    switch(listType){
    case INVERSE_LIST: 
      printf("# Costruiremo una lista inversa\n");
      break;
    case DIRECT_LIST: 
      printf("# Costruiremo una lista diretta\n");
      break;
    default: 
      printf("Interruzione programma: caso lista non previsto %d.\n",
	     listType);
      exit(-9); 
    }
}

/*****************************************************************************/
void openFile(void)
{
  fInput = fopen(fInputName,"r");
  if(fInput==NULL){
    printf("abort: impossibile aprire il file di input in lettura: %s\n",
	   fInputName); 
    exit(-9);
  }
  printf("# E' stato aperto il file di input: %s\n",
	 fInputName); 
}

/*****************************************************************************/
int readWord(void)
{
  char myFlag = 1;
  int j, myEnd = 0;
  j = 0;
  while( (j < MY_MAX) && (myFlag == 1)){ 
    myString[j] = fgetc(fInput);
    if(myString[j] == ' '){
      myString[j] = '\0';
      myFlag = 0;
    }
    else if(myString[j] == '\n'){
      j--;
    }/*per ignorare il fine riga*/
    else if(myString[j] == EOF){
      myEnd = 1; 
      myString[j] = '\0'; 
      myFlag = 0;
    }
    j++;
  }
  /* per sicurezza mi sto riservando un carattere in piu' oltre 
    al terminatore \0 */
  if(j >= MY_MAX-1){
    printf("Interruzione del programma: la parola era troppo lunga.\n");
    printf("Ricompilare con un valore di MY_MAX piu grande, era %d.\n",
	   MY_MAX);
    exit(-9);
  }
  printf("Parola di lunghezza %d: %s\n", strlen(myString), myString);
  return myEnd;
}

/*****************************************************************************/
void buildInverseList(void)
{
  char *scratchPointer; 
  struct word *wordScratchPointer;

  scratchPointer = (char *)malloc(strlen(myString));
  if(scratchPointer == NULL){
    printf("Interruzione del programma: fallita "
	   "malloc 1 in c_l_i\n");
    exit(-9);
  }
  wordScratchPointer = wordList;
  wordList = (struct word *) malloc(sizeof(struct word));  
  if(wordList==NULL){
    printf("Interruzione del programma: fallita "
	   "malloc 2 in c_l_i\n");
    exit(-9);
  }
  strcpy(scratchPointer, myString);
  wordList->pointerToString = scratchPointer;
  wordList->pointerToNextWord = wordScratchPointer;
}

/*****************************************************************************/
void buildDirectList(void)
{
  char *scratchPointer; 
  struct word *wordScratchPointer;

  scratchPointer = (char *)malloc(strlen(myString));
  if(scratchPointer==NULL){
    printf("Interruzione del programma: "
	   "fallita malloc 1 in c_l_d\n");
    exit(-9);
  }
  wordScratchPointer = wordList;
  wordList = (struct word *) malloc(sizeof(struct word));
  if(wordList==NULL){
    printf("Interruzione del programma: "
	   "fallita malloc 2 in c_l_d\n");
    exit(-9);
  }
  strcpy(scratchPointer,myString);
  wordList->pointerToString = scratchPointer;
  wordList->pointerToNextWord = NULL;
  if(wordScratchPointer!=NULL)
    wordScratchPointer->pointerToNextWord = wordList;
  if(wordScratchPointer==NULL)pointerStart = wordList;
}

/*****************************************************************************/
void printInverseList(void)
{
  struct word *wordScratchPointer = wordList;
  while (wordScratchPointer != NULL) {
    printf("%s\n", wordScratchPointer->pointerToString);
    wordScratchPointer = 
      wordScratchPointer->pointerToNextWord;
  }
}

/*****************************************************************************/
void printDirectList(void)
{
  struct word *wordScratchPointer = pointerStart;

  do{
    printf("%s\n", wordScratchPointer->pointerToString);
    wordScratchPointer = 
      wordScratchPointer->pointerToNextWord;
  }  while(wordScratchPointer->pointerToNextWord!=NULL);
  printf("%s\n", wordScratchPointer->pointerToString);
}

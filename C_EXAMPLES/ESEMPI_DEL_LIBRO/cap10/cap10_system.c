#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main(){
  int i;
  i = system("touch goodFile.txt");
  i = system("rm goodFile.txt");
  if (i != 0) {printf("Errore di rimozione goodFile %d\n",i);}
  i = system("rm badFile.txt");
  if (i != 0) {printf("Errore di rimozione badFile: %d\n",i);}
}

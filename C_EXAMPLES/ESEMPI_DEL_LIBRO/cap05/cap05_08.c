#include <stdio.h>
#include <stdlib.h>

main() {
  char c, line[100];
  int i = 0;
  printf("Immettere la stringa in input: ");
  while ((c = getchar()) != '\n') {
    if (i < 99) {
      line[i++] = c;
    }
    else {
      printf("Raggiunto limite massimo della stringa\n"); 
      exit(1);
    }
  }
}

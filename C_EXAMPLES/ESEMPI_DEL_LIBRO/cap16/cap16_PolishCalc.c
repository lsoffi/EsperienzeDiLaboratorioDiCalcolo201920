/*
  cap16_PolishCalc.c: A simple calculator using inverse Polish notation.
  Copyright (C) 2006 Federico Ricci-Tersenghi (Federico.Ricci@roma1.infn.it)

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

  This program has been extracted from "Programmazione Scientifica",
  Pearson Education ed. (2006), by Barone, Marinari, Organtini and
  Ricci-Tersenghi. ISBN 8871922425.
*/

/* by FRT */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

struct dataStruct {
  double *data;
  int size, numData;
};

void error(char *string);
void push(struct dataStruct *pStack, double  newItem);
double pop(struct dataStruct *pStack);

int main(int argc, char *argv[]) {
  char s1[MAX_INPUT_LENGTH], *s2;
  double a;
  struct dataStruct stack;
 
  stack.size = 1000;
  stack.data = (double *)calloc(stack.size, sizeof(double));
  stack.numData = 0;
  do {
    scanf("%s", s1);
    a = strtod(s1, &s2);
    if (*s2 == '\0') {
      push(&stack, a);
    } else if (s1 != s2) {
      printf("Non capisco cosa mi hai passato!\n");
      printf("Mi sembra un numero scritto male.\n");
    } else if (strlen(s1) != 1) {
      printf("Non capisco cosa mi hai passato!\n");
      printf("Ricorda che so fare solo le 4 operazioni di base.\n");
    } else {
      switch (*s1) {
      case 'q':
	break;
      case 'Q':
	break;
      case '+':
	a = pop(&stack) + pop(&stack);
	printf("%g\n", a);
	push(&stack, a);
	break;
      case '-':
	a = pop(&stack);
	a = pop(&stack) - a;
	printf("%g\n", a);
	push(&stack, a);
	break;
      case '*':
	a = pop(&stack) * pop(&stack);
	printf("%g\n", a);
	push(&stack, a);
	break;
      case '/':
	a = pop(&stack);
	a = pop(&stack) / a;
	printf("%g\n", a);
	push(&stack, a);
	break;
      default:
	printf("Non capisco cosa mi hai passato!\n");
	printf("Ricorda che so fare solo le 4 operazioni di base.\n");
      }
    }
  } while (*s1 != 'q' && *s1 != 'Q');
  return EXIT_SUCCESS;
}

void error(char *string) {
  fprintf(stderr, "ERRORE: %s\n", string);
  exit(EXIT_FAILURE);
}

void push(struct dataStruct *pStack, double newItem) {
  if (pStack->numData == pStack->size) {
    pStack->size *= 2;
    pStack->data = (double *)realloc(pStack->data,
				     pStack->size * sizeof(double));
  }
  pStack->data[pStack->numData++] = newItem;
}

double pop(struct dataStruct *pStack) {
  if (pStack->numData > 0) {
    return pStack->data[--pStack->numData];
  } else {
    error("operazione pop su stack vuoto!");
  }
}

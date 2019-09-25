/*
  cap15_naiveInsertionSort.c: The simplest Insertion Sort algorithm for sorting data.
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

void error(char *);
float *readFile(char *, int *);
void naiveInsertionSort(float *, float *, int);

int main(int argc, char *argv[]) {
  char *filename;
  float *orderedData, *inputData;
  int numData, i;
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename> \n", argv[0]);
    exit(1);
  }
  filename = argv[1];
  inputData = readFile(filename, &numData);
  orderedData = (float*)malloc(numData * sizeof(float));
  naiveInsertionSort(inputData, orderedData, numData);
  for (i = 0; i < numData; i++) {
    printf("%f\n", orderedData[i]);
  }
  return EXIT_SUCCESS;
}

void error(char *string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

float *readFile(char *filename, int *pSize) {
  FILE *inputFile;
  int allocatedSize;
  float *data;
  
  if ((inputFile = fopen(filename, "r")) == NULL)
    error("Opening the file");
  allocatedSize = 2;
  data = (float*)malloc(allocatedSize * sizeof(float));
  *pSize = 0;
  while (fscanf(inputFile, "%f", data + (*pSize)) != EOF) {
    (*pSize)++;
    if (*pSize == allocatedSize) {
      allocatedSize *= 2;
      data = (float*)realloc(data, allocatedSize * sizeof(float));
    }
  }
  fclose(inputFile);
  return data;
}

void naiveInsertionSort(float *input, float *output, int size) {
  int i, j, k;
  float datum;
  
  for (i = 0; i < size; i++) {
    datum = input[i];
    j = 0;
    while (j < i && datum > output[j]) {
      j++;
    }
    for (k = i; k > j; k--) {
      output[k] = output[k-1];
    }
    output[j] = datum;
  }
}

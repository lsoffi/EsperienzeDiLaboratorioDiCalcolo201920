/*
  cap15_insertionSort.c: Ordering data with a good Insertion Sort algorithm.
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
void insertionSort(float *, int);

int main(int argc, char *argv[]) {
  char *filename;
  float *data;
  int numData, i;
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename> \n", argv[0]);
    exit(1);
  }
  filename = argv[1];
  data = readFile(filename, &numData);
  insertionSort(data, numData);
  for (i = 0; i < numData; i++) {
    printf("%f\n", data[i]);
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

void insertionSort(float *data, int size) {
  int i, j;
  float datum;
  
  for (i = 1; i < size; i++) {
    datum = data[i];
    j = i - 1;
    while (j >= 0 && data[j] > datum) {
      data[j + 1] = data[j];
      j--;
    }
    data[j + 1] = datum;
  }
}

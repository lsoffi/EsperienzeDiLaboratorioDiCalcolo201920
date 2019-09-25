/*
  cap16_heapsort.c: Heapsort algorithm for data ordering.
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

struct dataStruct {
  float *data;
  int size, numData;
};

void error(char *);
void readFile(char *, struct dataStruct *);
void heapify(int, struct dataStruct *);
void buildHeap(struct dataStruct *);
void heapSort(struct dataStruct *);
/* non possiamo usare il nome 'heapsort' perche' gia` esiste
   una funzione con questo nome dichiarata dentro <stdlib.h> */

int main(int argc, char *argv[]) {
  char *filename;
  struct dataStruct heap;
  int i;
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename> \n", argv[0]);
    exit(1);
  }
  filename = argv[1];
  readFile(filename, &heap);
  heapSort(&heap);
  for (i = 1; i <= heap.numData; i++) {
    printf("%f\n", heap.data[i]);
  }
  return EXIT_SUCCESS;
}

void error(char *string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

void readFile(char *filename, struct dataStruct *pHeap) {
  FILE *inputFile;
  
  if ((inputFile = fopen(filename, "r")) == NULL)
    error("Opening the file");
  pHeap->size = 2;
  pHeap->data = (float*)malloc(pHeap->size * sizeof(float));
  pHeap->numData = 1;
  /* gli indici devono partire da 1 invece che da 0 */
  while (fscanf(inputFile, "%f", pHeap->data + pHeap->numData) != EOF) {
    pHeap->numData++;
    if (pHeap->numData == pHeap->size) {
      pHeap->size *= 2;
      pHeap->data = (float*)realloc(pHeap->data,
				    pHeap->size * sizeof(float));
    }
  }
  pHeap->numData--;
  /* altrimenti numData varrebbe 1 piu` del numero di dati nell'heap */
  fclose(inputFile);
}

void heapify(int index, struct dataStruct *pHeap) {
  int left, right, max;
  float tmp;
  
  left = 2 * index;
  if (left <= pHeap->numData) {
    /* verifico la priorita` del figlio di sinistra */
    if (pHeap->data[left] > pHeap->data[index]) {
      max = left;
    } else {
      max = index;
    }
    /* e poi di quello di destra */
    right = left + 1;
    if (right <= pHeap->numData &&
	pHeap->data[right] > pHeap->data[max]) {
      max = right;
    }
    /* se necessario faccio lo scambio dei dati di 2 nodi */
    if (max != index) {
      tmp = pHeap->data[index];
      pHeap->data[index] = pHeap->data[max];
      pHeap->data[max] = tmp;
      /* e richiamo heapify ricorsivamente */
      heapify(max, pHeap);
    }
  }
}

void buildHeap(struct dataStruct *pHeap) {
  int i;
  for (i = (int)(pHeap->numData / 2); i > 0; i--) {
    heapify(i, pHeap);
  }
}

void heapSort(struct dataStruct *pHeap) {
  int keepNumData;
  float tmp;

  buildHeap(pHeap);
  keepNumData = pHeap->numData;
  while (pHeap->numData > 1) {
    tmp = pHeap->data[1];
    pHeap->data[1] = pHeap->data[pHeap->numData];
    pHeap->data[pHeap->numData] = tmp;
    pHeap->numData--;
    heapify(1, pHeap);
  }
  pHeap->numData = keepNumData;
}

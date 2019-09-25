/*
  cap17_mstPrim.c: Computing the minimum spanning tree with the Prim algorithm.
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

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
  unsigned numNodes, numLinks, *conn, **neigh;
  float **weight;
} graphStruct;

typedef struct {
  int node, parent;
  float weight;
} vertex;

typedef vertex dataType;

typedef struct {
  dataType *data;
  int size, numData;
} dataStruct;

void error(char *);
void readGraphFromFile(char *, graphStruct *);
void initHeap(dataStruct *, int);
void add2MST(int, graphStruct *, int *, dataStruct *);
void insertInHeap(dataType, dataStruct *);
dataType extractFromHeap(dataStruct *);
void heapify(int, dataStruct *);

int main(int argc, char *argv[]) {
  char *filename;
  graphStruct graph;
  dataStruct heap;
  int i, *visited, numVisited, firstUnvisited, numConnComp;
  vertex tmp;
  double totalWeight = 0.0;
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename> \n", argv[0]);
    exit(1);
  }
  filename = argv[1];
  readGraphFromFile(filename, &graph);
  initHeap(&heap, max(graph.numNodes, graph.numLinks) + 1);

  visited = (int *)calloc(graph.numNodes, sizeof(int));
  for (i = 0; i < graph.numNodes; i++) {
    visited[i] = 0;
  }
  numVisited = 0;
  firstUnvisited = 0;
  numConnComp = 0;
  while (numVisited < graph.numNodes) {
    printf("Componente n.%u\n", ++numConnComp);
    while (visited[firstUnvisited]) firstUnvisited++;
    add2MST(firstUnvisited, &graph, visited, &heap);
    numVisited++;
    while (heap.numData) {
      tmp = extractFromHeap(&heap);
      if (!visited[tmp.node]) {
	totalWeight += tmp.weight;
	printf("%u %u %f\n", tmp.parent, tmp.node, tmp.weight);
	add2MST(tmp.node, &graph, visited, &heap);
	numVisited++;
      }
    }
    printf("\n");
  }
  printf("Il peso del MST e` %f\n", totalWeight);
  printf("Il grafo ha %u componente/i connessa/e.\n\n", numConnComp);
  return EXIT_SUCCESS;
}

void error(char *string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

void readGraphFromFile(char *filename, graphStruct *pGraph) {
  FILE *fin;
  int i, n1, n2;
  float ww;

  if ((fin = fopen(filename,"r")) == NULL) {
    error("opening file");
  }
  fscanf(fin, "N = %u M = %u", &(pGraph->numNodes), &(pGraph->numLinks));

  pGraph->conn = (unsigned *)calloc(pGraph->numNodes, sizeof(unsigned));
  pGraph->neigh = (unsigned **)calloc(pGraph->numNodes, sizeof(unsigned *));
  pGraph->weight = (float **)calloc(pGraph->numNodes, sizeof(float *));
  for (i = 0; i< pGraph->numNodes; i++) {
    pGraph->conn[i] = 0;
  }
  for (i = 0; i < pGraph->numLinks; i++) {
    if (fscanf(fin, "%u %u %f", &n1, &n2, &ww) != 3) {
      error("graph file corrupted");
    }
    if (n1 < 0 || n1 >= pGraph->numNodes ||
	n2 < 0 || n2 >= pGraph->numNodes) {
      error("graph file corrupted");
    }
    pGraph->conn[n1]++;
    pGraph->neigh[n1] =
      realloc(pGraph->neigh[n1], pGraph->conn[n1] * sizeof(unsigned));
    pGraph->weight[n1] =
      realloc(pGraph->weight[n1], pGraph->conn[n1] * sizeof(float));
    pGraph->neigh[n1][pGraph->conn[n1]-1] = n2;
    pGraph->weight[n1][pGraph->conn[n1]-1] = ww;
    pGraph->conn[n2]++;
    pGraph->neigh[n2] =
      realloc(pGraph->neigh[n2], pGraph->conn[n2] * sizeof(unsigned));
    pGraph->weight[n2] =
      realloc(pGraph->weight[n2], pGraph->conn[n2] * sizeof(float));
    pGraph->neigh[n2][pGraph->conn[n2]-1] = n1;
    pGraph->weight[n2][pGraph->conn[n2]-1] = ww;
  }
  fclose(fin);
}

void initHeap(dataStruct *pHeap, int size) {
  pHeap->size = size;
  pHeap->data = (dataType *)calloc(pHeap->size, sizeof(dataType));
  pHeap->numData = 0;
}

void add2MST(int node, graphStruct *pGraph,
	     int *visited, dataStruct *pHeap) {
  int i, *pNeigh = pGraph->neigh[node];
  float *pWeight = pGraph->weight[node];
  vertex tmp;

  visited[node] = 1;
  tmp.parent = node;
  for (i = 0; i < pGraph->conn[node]; i++, pNeigh++, pWeight++) {
    if (!visited[*pNeigh]) {
      tmp.node = *pNeigh;
      tmp.weight = *pWeight;
      insertInHeap(tmp, pHeap);
    }
  }
}

void insertInHeap(dataType item, dataStruct *pHeap) {
  int index = ++(pHeap->numData);
  while (index > 1 &&
	 item.weight < (pHeap->data[(int)(index / 2)]).weight) {
    pHeap->data[index] = pHeap->data[(int)(index / 2)];
    index /= 2;
  }
  pHeap->data[index] = item;
} 

dataType extractFromHeap(dataStruct *pHeap) {
  dataType extracted = pHeap->data[1];
  pHeap->data[1] = pHeap->data[pHeap->numData--];
  if (pHeap->numData) {
    heapify(1, pHeap);
  }
  return extracted;
}

void heapify(int index, dataStruct *pHeap) {
  int left, right, min;
  dataType tmp;
  
  left = 2 * index;
  if (left <= pHeap->numData) {
    if (pHeap->data[left].weight < pHeap->data[index].weight) {
      min = left;
    } else {
      min = index;
    }
    right = left + 1;
    if (right <= pHeap->numData &&
	pHeap->data[right].weight < pHeap->data[min].weight) {
      min = right;
    }
    if (min != index) {
      tmp = pHeap->data[index];
      pHeap->data[index] = pHeap->data[min];
      pHeap->data[min] = tmp;
      heapify(min, pHeap);
    }
  }
}

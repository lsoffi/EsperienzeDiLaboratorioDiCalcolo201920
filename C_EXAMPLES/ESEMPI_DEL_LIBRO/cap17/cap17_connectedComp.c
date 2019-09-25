/*
  cap17_connectedComp.c: A program for computing the connected components of a graph.
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

typedef struct {
  unsigned numNodes, numLinks, *conn, **neigh;
} graphStruct;

void error(char *);
void readGraphFromFile(char *, graphStruct *);
void findConnCompBF(graphStruct *);
void findConnCompDF(graphStruct *);
void findRecursiveConnCompDF(graphStruct *);
void addNode(unsigned, unsigned *, unsigned *, graphStruct *);

int main(int argc, char *argv[]) {
  int scelta;
  graphStruct graph;
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s <graph_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  readGraphFromFile(argv[1], &graph);
  printf("Scelgi il metodo di ricerca delle componenti connesse:\n"
	 "1) Breadth-first\n"
	 "2) Deapth-first\n"
	 "3) Deapth-first ricorsiva\n");
  do {
    scanf("%i", &scelta);
    if (scelta != 1 && scelta != 2 && scelta != 3)
      printf("Digita solo 1, 2 o 3.\n");
  } while (scelta != 1 && scelta != 2 && scelta != 3);
  printf("\n");
  if (scelta == 1) {
    findConnCompBF(&graph);
  } else if (scelta == 2) {
    findConnCompDF(&graph);
  } else {
    findRecursiveConnCompDF(&graph);
  }
  return EXIT_SUCCESS;
}

void error(char *string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

void readGraphFromFile(char* filename, graphStruct *pGraph) {
  FILE* fin;
  int i, n1, n2;

  if ((fin = fopen(filename,"r")) == NULL) {
    error("opening file");
  }
  fscanf(fin, "N = %u M = %u", &(pGraph->numNodes), &(pGraph->numLinks));

  pGraph->conn = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  pGraph->neigh = (unsigned**)calloc(pGraph->numNodes, sizeof(unsigned*));
  for (i = 0; i< pGraph->numNodes; i++) {
    pGraph->conn[i] = 0;
  }
  for (i = 0; i < pGraph->numLinks; i++) {
    if (fscanf(fin, "%u %u", &n1, &n2) != 2) {
      error("graph file corrupted");
    }
    if (n1 < 0 || n1 >= pGraph->numNodes ||
	n2 < 0 || n2 >= pGraph->numNodes) {
      error("graph file corrupted");
    }
    pGraph->conn[n1]++;
    pGraph->neigh[n1] =
      realloc(pGraph->neigh[n1], pGraph->conn[n1] * sizeof(unsigned));
    pGraph->neigh[n1][pGraph->conn[n1]-1] = n2;
    pGraph->conn[n2]++;
    pGraph->neigh[n2] =
      realloc(pGraph->neigh[n2], pGraph->conn[n2] * sizeof(unsigned));
    pGraph->neigh[n2][pGraph->conn[n2]-1] = n1;
  }
  fclose(fin);
}

void findConnCompBF(graphStruct *pGraph) {
  unsigned i, node, *workNeigh, *queue, queueFirst, queueLast;
  unsigned *visited, numVisited, oldNumVisited, firstUnvisited;
  unsigned *clusSize, numClus, max, *distr;

  queue = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  visited = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  clusSize = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  
  for (i = 0; i < pGraph->numNodes; i++) {
    visited[i] = 0;
  }
  numVisited = 0;
  queueFirst = 0;
  queueLast = 0;
  numClus = 0;
  firstUnvisited = 0;
  while (numVisited < pGraph->numNodes) {
    oldNumVisited = numVisited;
    while (visited[firstUnvisited]) firstUnvisited++;
    node = firstUnvisited++;
    queue[queueLast++] = node;
    visited[node] = 1;
    numVisited++;
    while(queueFirst < queueLast) {
      node = queue[queueFirst++];
      workNeigh = pGraph->neigh[node];
      for (i = 0; i < pGraph->conn[node]; i++, workNeigh++) {
	if (!visited[*workNeigh]) {
	  queue[queueLast++] = *workNeigh;
	  visited[*workNeigh] = 1;
	  numVisited++;
	}
      }
    }
    clusSize[numClus++] = numVisited - oldNumVisited;
    printf("La %ia componente connessa e` di %u vertici.\n",
	   numClus, clusSize[numClus-1]);
  }
  printf("\n");
  max = 0;
  for (i = 0; i < numClus; i++) {
    if (clusSize[i] > max) max = clusSize[i];
  }
  distr = (unsigned*)calloc(max + 1, sizeof(unsigned));
  for (i = 0; i < numClus; i++)
    distr[clusSize[i]]++;
  printf("# Numero dei cluster = %u\n", numClus);
  printf("# size numCluster(size)\n");
  for (i = 0; i <= max; i++)
    if (distr[i])
      printf("%u %u\n", i, distr[i]);
  printf("\n");
}

void findConnCompDF(graphStruct *pGraph) {
  unsigned i, node, *workNeigh, *stack, stackIndex;
  unsigned *visited, numVisited, oldNumVisited, firstUnvisited;
  unsigned *clusSize, numClus, max, *distr;

  stack = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  visited = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  clusSize = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  
  for (i = 0; i < pGraph->numNodes; i++) {
    visited[i] = 0;
  }
  numVisited = 0;
  stackIndex = 0;
  numClus = 0;
  firstUnvisited = 0;
  while (numVisited < pGraph->numNodes) {
    oldNumVisited = numVisited;
    while (visited[firstUnvisited]) firstUnvisited++;
    node = firstUnvisited++;
    stack[stackIndex++] = node;

    while(stackIndex) {
      node = stack[--stackIndex];
      if (!visited[node]) {
	visited[node] = 1;
	numVisited++;
	workNeigh = pGraph->neigh[node];
	for (i = 0; i < pGraph->conn[node]; i++, workNeigh++) {
	  if (!visited[*workNeigh]) {
	    stack[stackIndex++] = *workNeigh;
	  }
	}
      }
    }
    clusSize[numClus++] = numVisited - oldNumVisited;
    printf("La %ia componente connessa e` di %u vertici.\n",
	   numClus, clusSize[numClus-1]);
  }
  printf("\n");
  max = 0;
  for (i = 0; i < numClus; i++) {
    if (clusSize[i] > max) max = clusSize[i];
  }
  distr = (unsigned*)calloc(max + 1, sizeof(unsigned));
  for (i = 0; i < numClus; i++)
    distr[clusSize[i]]++;
  printf("# Numero dei cluster = %u\n", numClus);
  printf("# size numCluster(size)\n");
  for (i = 0; i <= max; i++)
    if (distr[i])
      printf("%u %u\n", i, distr[i]);
  printf("\n");
}

void findRecursiveConnCompDF(graphStruct *pGraph) {
  unsigned i, *visited, numVisited, oldNumVisited, firstUnvisited;
  unsigned *clusSize, numClus, max, *distr;

  visited = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  clusSize = (unsigned*)calloc(pGraph->numNodes, sizeof(unsigned));
  
  for (i = 0; i < pGraph->numNodes; i++) {
    visited[i] = 0;
  }
  numVisited = 0;
  numClus = 0;
  firstUnvisited = 0;
  while (numVisited < pGraph->numNodes) {
    oldNumVisited = numVisited;
    while (visited[firstUnvisited]) firstUnvisited++;
    addNode(firstUnvisited++, visited, &numVisited, pGraph);
    clusSize[numClus++] = numVisited - oldNumVisited;
    printf("La %ia componente connessa e` di %u vertici.\n",
	   numClus, clusSize[numClus-1]);
  }
  printf("\n");
  max = 0;
  for (i = 0; i < numClus; i++) {
    if (clusSize[i] > max) max = clusSize[i];
  }
  distr = (unsigned*)calloc(max + 1, sizeof(unsigned));
  for (i = 0; i < numClus; i++)
    distr[clusSize[i]]++;
  printf("# Numero dei cluster = %u\n", numClus);
  printf("# size numCluster(size)\n");
  for (i = 0; i <= max; i++)
    if (distr[i])
      printf("%u %u\n", i, distr[i]);
  printf("\n");
}

void addNode(unsigned node, unsigned *visited,
	     unsigned *pNumVisited, graphStruct *pGraph){
  unsigned i, *workNeigh = pGraph->neigh[node];
  visited[node] = 1;
  (*pNumVisited)++;
  for (i = 0; i < pGraph->conn[node]; i++, workNeigh++) {
    if (!visited[*workNeigh]) {
      addNode(*workNeigh, visited, pNumVisited, pGraph);
    }
  }
}

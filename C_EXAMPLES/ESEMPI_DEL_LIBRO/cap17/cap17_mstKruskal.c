/*
  cap17_mstKruskal.c: Computing the minimum spanning tree with the Kruskal algorithm.
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
  int parent, maxDepth;
} vertex;

typedef struct {
  int n1, n2;
  float weight;
} weightedLink;

vertex *node;
weightedLink *link, *mst;
int numNodes, numLinks;

void error(char *);
void readGraphFromFile(char *);
void sortLinks(void);
void buildHeap(void);
void swapLinks(int, int);
void heapify(int, int);
int rootOfNode(int);
void mergeComp(int, int);

int main(int argc, char *argv[])
{
  int i, j, r1, r2;
  double totalWeight = 0.0;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <graph_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  readGraphFromFile(argv[1]);
  sortLinks();
  j = 0;
  for (i = 1; i <= numLinks; i++) {
    r1 = rootOfNode(link[i].n1);
    r2 = rootOfNode(link[i].n2);
    if (r1 != r2) {
      mst[j++] = link[i];
      totalWeight += link[i].weight;
      mergeComp(r1, r2);
    }
  }
  printf("Il grafo contiene %i componente/i connessa/e.\n"
	 "Il suo MST ha un peso di %f\n"
	 " ed e` costituito dai seguenti archi:\n",
	 numNodes - j, totalWeight);
  for (i = 0; i < j; i++) {
    printf("%i %i %f\n", mst[i].n1, mst[i].n2, mst[i].weight);
  }
  return EXIT_SUCCESS;
}

void error(char* string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

void readGraphFromFile(char* filename) {
  FILE* fin;
  int i;
  int n1, n2;
  float weight;

  if ((fin = fopen(filename,"r")) == NULL) {
    error("opening file.");
  }
  fscanf(fin, "N = %i M = %i", &numNodes, &numLinks);
  if (numNodes < 0 || numLinks < 0) {
    error("graph file corrupted");
  }
  node = (vertex*)calloc(numNodes, sizeof(vertex));
  for (i = 0; i < numNodes; i++) {
    node[i].parent = i;
    node[i].maxDepth = 0;
  }
  mst = (weightedLink*)calloc(numNodes-1, sizeof(weightedLink));
  /* il vettore contenente i link usa indici che partono da 1 perche'
     verra` ordinato con heapsort */
  link = (weightedLink*)calloc(numLinks+1, sizeof(weightedLink));
  for (i = 1; i <= numLinks; i++) {
    if (fscanf(fin, "%i %i %f", &n1, &n2, &weight) != 3) {
      error("graph file corrupted");
    }
    if (n1 < 0 || n1 >= numNodes || n2 < 0 || n2 >= numNodes) {
      error("graph file corrupted");
    }
    link[i].n1 = n1;
    link[i].n2 = n2;
    link[i].weight = weight;
  }
  fclose(fin);
}

void sortLinks(void) {
  int i = numLinks;
  buildHeap();
  while (i > 1) {
    swapLinks(1, i);
    i--;
    heapify(1, i);
  }
}

void buildHeap(void) {
  int i;
  for (i = (int)(numLinks / 2); i > 0; i--) {
    heapify(i, numLinks);
  }
}

void swapLinks(int i, int j) {
  weightedLink tmp = link[i];
  link[i] = link[j];
  link[j] = tmp;
}

void heapify(int index, int heapSize) {
  int left, right, max;
  
  left = 2 * index;
  if (left <= heapSize) {
    if (link[left].weight > link[index].weight) {
      max = left;
    } else {
      max = index;
    }
    right = left + 1;
    if (right <= heapSize && link[right].weight > link[max].weight) {
      max = right;
    }
    if (max != index) {
      swapLinks(index, max);
      heapify(max, heapSize);
    }
  }
}

int rootOfNode(int index) {
  while (node[index].parent != index) {
    index = node[index].parent;
  };
  return index;
}

void mergeComp(int r1, int r2) {
  if (node[r1].maxDepth < node[r2].maxDepth) {
    node[r1].parent = r2;
  } else {
    node[r2].parent = r1;
    if (node[r1].maxDepth == node[r2].maxDepth) {
      node[r1].maxDepth++;
    }
  }
}

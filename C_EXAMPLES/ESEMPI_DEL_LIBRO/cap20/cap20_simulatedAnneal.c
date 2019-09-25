/*
  cap20_simulatedAnneal.c: Searching for the lowest energy configuration of an EA model defined on a generic graph by Simulated Annealing.
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
#include <math.h>

#define TMAX  1.51
#define TSTEP 0.02

#define FNORM   (2.3283064365e-10)
#define RANDOM  ((ira[ip++] = ira[ip1++] + ira[ip2++]) ^ ira[ip3++])
#define FRANDOM (FNORM * RANDOM)
#define pm1     ((FRANDOM > 0.5) ? 1 : -1)

typedef struct {
  int numNodes, numLinks, *conn, **neigh;
  float **J;
} graphStruct;

/* variabili globali per il generatore random */
unsigned myrand, ira[256];
unsigned char ip, ip1, ip2, ip3;

unsigned randForInit(void);
void initRandom(void);
float gaussRan(void);
void error(char *string);
void readGraphFromFile(graphStruct *pGraph, char *filename);
int *initSpin(graphStruct *pGraph);
void oneSweep(float beta, int *s, graphStruct *pGraph);
void measures(int time, int *s, graphStruct *pGraph);
double energy(int *s, graphStruct *pGraph);

int main(int argc, char *argv[]) {
  int t, numIter, *s;
  float temp, beta;
  graphStruct graph;

  if (argc != 4) {
    fprintf(stderr, "usage: %s <filename> <numIter> <seed>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  numIter = atoi(argv[2]);
  myrand = (unsigned)atoi(argv[3]);
  readGraphFromFile(&graph, argv[1]);
  printf("# file = %s   numIter = %i   random seed = %u\n",
	 argv[1], numIter, myrand);
  printf("# T ener\n");
  fflush(stdout);
  initRandom();
  s = initSpin(&graph);
  for (temp = TMAX; temp > 0.0; temp -= TSTEP) {
    beta = 1./ temp;
    for (t = 1; t <= numIter; t++) {
      oneSweep(beta, s, &graph);
      printf("%.3f %f\n", temp, energy(s, &graph));
      fflush(stdout);
    }
  }
  printf("\n");
  return EXIT_SUCCESS;
}

unsigned randForInit(void) {
  unsigned long long y;
  
  y = myrand * 16807LL;
  myrand = (y & 0x7fffffff) + (y >> 31);
  if (myrand & 0x80000000) {
    myrand = (myrand & 0x7fffffff) + 1;
  }
  return myrand;
}

void initRandom(void) {
  int i;
  
  ip = 128;    
  ip1 = ip - 24;    
  ip2 = ip - 55;    
  ip3 = ip - 61;
  for (i = ip3; i < ip; i++) {
    ira[i] = randForInit();
  }
}

float gaussRan(void) {
  static int iset = 0;
  static float gset;
  float fac, rsq, v1, v2;

  if (iset == 0) {
    do {
      v1 = 2.0 * FRANDOM - 1.0;
      v2 = 2.0 * FRANDOM - 1.0;
      rsq = v1 * v1 + v2 * v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    fac = sqrt(-2.0 * log(rsq) / rsq);
    gset = v1 * fac;
    iset = 1;
    return v2 * fac;
  } else {
    iset = 0;
    return gset;
  }
}

void error(char *string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

void readGraphFromFile(graphStruct *pGraph, char *filename) {
  FILE *fin;
  int i, n1, n2;
  float jj;

  if ((fin = fopen(filename,"r")) == NULL) {
    error("opening file");
  }
  fscanf(fin, "N = %u M = %u", &(pGraph->numNodes), &(pGraph->numLinks));

  pGraph->conn = (int *)calloc(pGraph->numNodes, sizeof(int));
  pGraph->neigh = (int **)calloc(pGraph->numNodes, sizeof(int *));
  pGraph->J = (float **)calloc(pGraph->numNodes, sizeof(float *));
  for (i = 0; i< pGraph->numNodes; i++) {
    pGraph->conn[i] = 0;
  }
  for (i = 0; i < pGraph->numLinks; i++) {
    if (fscanf(fin, "%u %u %f", &n1, &n2, &jj) != 3) {
      error("graph file corrupted");
    }
    if (n1 < 0 || n1 >= pGraph->numNodes ||
	n2 < 0 || n2 >= pGraph->numNodes) {
      error("graph file corrupted");
    }
    pGraph->conn[n1]++;
    pGraph->neigh[n1] =
      realloc(pGraph->neigh[n1], pGraph->conn[n1] * sizeof(int));
    pGraph->J[n1] =
      realloc(pGraph->J[n1], pGraph->conn[n1] * sizeof(float));
    pGraph->neigh[n1][pGraph->conn[n1]-1] = n2;
    pGraph->J[n1][pGraph->conn[n1]-1] = jj;
    pGraph->conn[n2]++;
    pGraph->neigh[n2] =
      realloc(pGraph->neigh[n2], pGraph->conn[n2] * sizeof(int));
    pGraph->J[n2] =
      realloc(pGraph->J[n2], pGraph->conn[n2] * sizeof(float));
    pGraph->neigh[n2][pGraph->conn[n2]-1] = n1;
    pGraph->J[n2][pGraph->conn[n2]-1] = jj;
  }
  fclose(fin);
}

int *initSpin(graphStruct *pGraph) {
  int site, *s;

  s = (int *)malloc(pGraph->numNodes * sizeof(int));
  for (site = 0; site < pGraph->numNodes; site++)
    s[site] = pm1;
  return s;
}

void oneSweep(float beta, int *s, graphStruct *pGraph) {
  int j, site, *pNeigh, siteConn;
  float *pJ, sum;
  
  for (site = 0; site < pGraph->numNodes; site++) {
    siteConn = pGraph->conn[site];
    pNeigh = pGraph->neigh[site];
    pJ = pGraph->J[site];
    sum = 0.0;
    for (j = 0; j < siteConn; j++, pNeigh++, pJ++) {
      sum += (*pJ) * s[*pNeigh];
    }
    sum *= s[site];
    if (sum <= 0 || FRANDOM < exp(-2. * beta * sum)) {
      s[site] = -s[site];
    }
  }
}

void measures(int time, int *s, graphStruct *pGraph) {
  int site, j, mag, siteConn, *pNeigh;
  float *pJ, sum;
  double ener;

  mag = 0; ener = 0.0;
  for (site = 0; site < pGraph->numNodes; site++) {
    siteConn = pGraph->conn[site];
    pNeigh = pGraph->neigh[site];
    pJ = pGraph->J[site];
    mag += s[site];
    sum = 0.0;
    for (j = 0; j < siteConn; j++, pNeigh++, pJ++) {
      sum += (*pJ) * s[*pNeigh];
    }
    ener -= s[site] * sum;
  }
  printf("%i %f %f\n", time, (float)mag / pGraph->numNodes,
	 0.5 * (float)ener / pGraph->numNodes);
  fflush(stdout);
}

double energy(int *s, graphStruct *pGraph) {
  int site, j, siteConn, *pNeigh;
  float *pJ, sum;
  double ener;

  ener = 0.0;
  for (site = 0; site < pGraph->numNodes; site++) {
    siteConn = pGraph->conn[site];
    pNeigh = pGraph->neigh[site];
    pJ = pGraph->J[site];
    sum = 0.0;
    for (j = 0; j < siteConn; j++, pNeigh++, pJ++) {
      sum += (*pJ) * s[*pNeigh];
    }
    ener -= s[site] * sum;
  }
  return 0.5 * ener;
}

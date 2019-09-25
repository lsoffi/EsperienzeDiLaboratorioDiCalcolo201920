/*
  cap19_Ising.c: MC simulation for an Ising model on a generic graph.
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

#define L     50

#define L2   (L * L)
#define N     L2
#define DIM   2
#define CONN (2 * DIM)

#define FNORM   (2.3283064365e-10)
#define RANDOM  ((ira[ip++] = ira[ip1++] + ira[ip2++]) ^ ira[ip3++])
#define FRANDOM (FNORM * RANDOM)
#define pm1     ((FRANDOM > 0.5) ? 1 : -1)

typedef struct {
  int numNodes, numLinks, *conn, **neigh;
} graphStruct;

/* variabili globali per il generatore random */
unsigned myrand, ira[256];
unsigned char ip, ip1, ip2, ip3;

unsigned randForInit(void);
void initRandom(void);
float gaussRan(void);
void error(char *string);
void initGraph(graphStruct *pGraph);
void initProb(float temperature, float *prob);
void initSpin(int startingFlag, int *s);
void oneSweep(int *s, graphStruct *pGraph, float *prob);
void oneStep(int *s, graphStruct *pGraph, float *prob);
void measures(int time, int *s, graphStruct *pGraph);

int main(int argc, char *argv[]) {
  int t, numIter, measFreq, startingFlag, s[N];
  float temperature, prob[CONN + 1];
  graphStruct graph;

  if (argc != 6) {
    fprintf(stderr,
	    "usage: %s <T> <numIter> <measFreq> <startingFlag> <seed>\n"
	    "startingFlag = 0: random config\n"
	    "startingFlag = 1: M = 1\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  temperature = (float)atof(argv[1]);
  numIter = (unsigned)atoi(argv[2]);
  measFreq = (unsigned)atoi(argv[3]);
  startingFlag = (unsigned)atoi(argv[4]);
  myrand = (unsigned)atoi(argv[5]);
  
  printf("# L = %d   T = %.3f   random seed = %u\n",
	 L, temperature, myrand);
  printf("# t mag ener\n");
  fflush(stdout);
  initRandom();
  initGraph(&graph);
  initProb(temperature, prob);
  initSpin(startingFlag, s);
  measures(0, s, &graph);
  for (t = 1; t <= numIter; t++) {
    oneSweep(s, &graph, prob);
    if (t % measFreq == 0) measures(t, s, &graph);
  }
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

void initGraph(graphStruct *pGraph) {
  int ix, iy, site, *pNeigh;

  pGraph->numNodes = N;
  pGraph->numLinks = N * DIM;
  pGraph->conn = (int*)malloc(N * sizeof(int));
  pGraph->neigh = (int**)malloc(N * sizeof(int*));
  for (site = 0 ; site < N; site++) {
    pGraph->conn[site] = CONN;
    pGraph->neigh[site] = (int*)malloc(CONN * sizeof(int));
  }
  for (iy = 0; iy < L; iy++) {
    for (ix = 0; ix < L; ix++) {
      site = ix + iy * L;
      pNeigh = pGraph->neigh[site];
      pNeigh[0] = ((ix + 1) % L) + iy * L;
      pNeigh[1] = ix + ((iy + 1) % L) * L;
      pNeigh[2] = ((ix + L - 1) % L) + iy * L;
      pNeigh[3] = ix + ((iy + L - 1) % L) * L;
    }
  }  
}

void initProb(float temperature, float *prob) {
  int i;

  if (temperature > 0.0) {
    for (i = 0; i <= CONN; i++)
      prob[i] = exp(-2.0 * i / temperature);
  } else {
    for (i = 0; i <= CONN; i++)
      prob[i] = 0.0;
  }
}

void initSpin(int startingFlag, int *s) {
  int site;

  if (startingFlag) {
    for (site = 0; site < N; site++) s[site] = 1;
  } else {
    for (site = 0; site < N; site++) s[site] = pm1;
  }
}

void oneSweep(int *s, graphStruct *pGraph, float *prob) {
  int i, j, site, *pNeigh, siteConn, sum;
  
  for (i = 0; i < pGraph->numNodes; i++) {
    site = (int)(FRANDOM * pGraph->numNodes);
    pNeigh = pGraph->neigh[site];
    siteConn = pGraph->conn[site];
    sum = 0;
    for (j = 0; j < siteConn; j++, pNeigh++) {
      sum += s[*pNeigh];
    }
    sum *= s[site];
    if (sum <= 0 || FRANDOM < prob[sum]) {
      s[site] = -s[site];
    }
  }
}

void oneStep(int *s, graphStruct *pGraph, float *prob) {
  int j, site, *pNeigh, siteConn, sum;
  
  site = (int)(FRANDOM * pGraph->numNodes);
  pNeigh = pGraph->neigh[site];
  siteConn = pGraph->conn[site];
  sum = 0;
  for (j = 0; j < siteConn; j++, pNeigh++) {
    sum += s[*pNeigh];
  }
  sum *= s[site];
  if (sum <= 0 || FRANDOM < prob[sum]) {
    s[site] = -s[site];
  }
}

void measures(int time, int *s, graphStruct *pGraph) {
  int site, j, mag, ener, *pNeigh, sum;

  mag = 0; ener = 0;
  for (site = 0; site < pGraph->numNodes; site++) {
    pNeigh = pGraph->neigh[site];
    mag += s[site];
    sum = 0;
    for (j = 0; j < CONN; j++, pNeigh++) {
      sum += s[*pNeigh];
    }
    ener -= s[site] * sum;
  }
  printf("%i %f %f\n", time, (float)mag / pGraph->numNodes,
	 0.5 * (float)ener / pGraph->numNodes);
  fflush(stdout);
}

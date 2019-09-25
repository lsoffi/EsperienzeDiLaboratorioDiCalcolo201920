/*
  cap17_percRandGraph.c: A program for studying the percolation phenomenon on random graphs.
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

#define N 10000

#define FNORM   (2.3283064365e-10)
#define RANDOM  ((ira[ip++] = ira[ip1++] + ira[ip2++]) ^ ira[ip3++])
#define FRANDOM (FNORM * RANDOM)

struct connComp {
  struct connComp *parent;
  unsigned size;
} comp[N];

void initRandom(void);
unsigned randForInit(void);
void error(char *);
struct connComp *componentOf(struct connComp *);
unsigned mergeComp(struct connComp *, struct connComp *);

/* variabili per il generatore random */
unsigned myrand, ira[256];
unsigned char ip, ip1, ip2, ip3;

int main(int argc, char *argv[]) {
  unsigned i, is, numSamples, site1, site2, largestClusSize, newSize;
  unsigned long long meanClusSize; /* taglia media moltiplicata per N */
  struct connComp *pComp1, *pComp2;

  if (argc != 3) {
    fprintf(stderr, "usage: %s <n_samples> <seed>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  numSamples = (unsigned)atoi(argv[1]);
  myrand = (unsigned)atoi(argv[2]);
  if (myrand == 2147483647)
    error("seed must be less than 2147483647");

  printf("# percolazione su grafo random\n");
  printf("# N = %u   random seed = %u\n", N, myrand);
  printf("# conn mean_clus_size largest_clus_size\n");

  initRandom();
  for (is = 0; is < numSamples; is++) {
    for (i = 0; i < N; i++) {
      comp[i].parent = comp + i;
      comp[i].size = 1;
    }
    meanClusSize = N;
    largestClusSize = 1;
    for (i = 1; i <= N; i++) {
      site1 = (unsigned)(FRANDOM * N);
      pComp1 = componentOf(comp + site1);
      do {
	site2 = (unsigned)(FRANDOM * N);
      } while (site2 == site1);
      pComp2 = componentOf(comp + site2);
      if (pComp1 != pComp2) {
	meanClusSize += 2 * (unsigned long long)pComp1->size * pComp2->size;
	newSize = mergeComp(pComp1, pComp2);
	if (newSize > largestClusSize) {
	  largestClusSize = newSize;
	}
      }
      if (i % (N / 100) == 0) {
	printf("%f %f %f\n", 2.*(float)i/N,
	       (float)meanClusSize/N, (float)largestClusSize/N);
	fflush(stdout);
      }
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}

void initRandom(void) {
  int i;
  
  ip = 128;    
  ip1 = ip - 24;    
  ip2 = ip - 55;    
  ip3 = ip - 61;
  for (i = ip3; i < ip; i++)
    ira[i] = randForInit();
}

unsigned randForInit(void) {
  unsigned long long y;
  
  y = myrand * 16807LL;
  myrand = (y & 0x7fffffff) + (y >> 31);
  if (myrand & 0x80000000)
    myrand = (myrand & 0x7fffffff) + 1;
  return myrand;
}

void error(char* string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

struct connComp *componentOf(struct connComp *pComp) {
  while (pComp->parent != pComp) pComp = pComp->parent;
  return pComp;
}

unsigned mergeComp(struct connComp *pComp1, struct connComp *pComp2) {
  if (pComp1->size < pComp2->size) {
    pComp1->parent = pComp2;
    pComp2->size += pComp1->size;
    return pComp2->size;
  } else {
    pComp2->parent = pComp1;
    pComp1->size += pComp2->size;
    return pComp1->size;
  }
}

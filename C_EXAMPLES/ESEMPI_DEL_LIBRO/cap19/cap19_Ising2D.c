/*
  cap19_Ising2D.c: MC simulation for an Ising model on a 2D square lattice (mostly optimized).
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

/* variabili globali per il generatore random */
unsigned myrand, ira[256];
unsigned char ip, ip1, ip2, ip3;

unsigned randForInit(void);
void initRandom(void);
float gaussRan(void);
void error(char *string);
void initProb(float temperature, float *prob);
void initSpin(int startingFlag, int *s, int *pMag, int *pEner);
void oneSweep2D(int *s, float *prob, int *pMag, int *pEner);
void measures(int time, int *s);

int main(int argc, char *argv[]) {
  int t, numIter, measFreq, startingFlag, s[N], mag, ener;
  float temperature, prob[CONN + 1], invN = 1.0 / N;

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
  initProb(temperature, prob);
  initSpin(startingFlag, s, &mag, &ener);
  printf("%i %f %f\n", 0, invN * mag, invN * ener);
  for (t = 1; t <= numIter; t++) {
    oneSweep2D(s, prob, &mag, &ener);
    if (t % measFreq == 0) printf("%i %f %f\n", t, invN * mag, invN * ener);
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

void initSpin(int startingFlag, int *s, int *pMag, int *pEner) {
  int site;

  if (startingFlag) {
    for (site = 0; site < N; site++) s[site] = 1;
    *pMag = N;
  } else {
    *pMag = 0;
    for (site = 0; site < N; site++) {
      s[site] = pm1;
      *pMag += s[site];
    }
  }
  *pEner = 0;
  /* sommiamo prima le interazioni verticali */
  for (site = 0; site < N - L; site++) {
    *pEner -= s[site] * s[site + L];
  }
  /* gli spin dell'ultima riga sono connessi a quelli della prima */
  for (site = N - L; site < N; site++) {
    *pEner -= s[site] * s[site + L - N];
  }
  /* sommiamo quindi le interazioni orizzontali */
  for (site = 0; site < N; site++) {
    /* quelli della prima colonna sono connessi a quelli dell'ultima */
    if (site % L == 0) {
      *pEner -= s[site] * s[site + L - 1];
    } else {
      *pEner -= s[site] * s[site - 1];
    }
  }
}

void oneSweep2D(int *s, float *prob, int *pMag, int *pEner) {
  int site, ix, iy, sum;

  site = 0;
  /* caso   iy = 0   ix = 0 */
  sum = s[site] * (s[site+L2-L] + s[site+L-1] + s[site+1] + s[site+L]);
  if (sum <= 0 || FRANDOM < prob[sum]) {
    s[site] = -s[site];
    *pMag += 2 * s[site];
    *pEner += 2 * sum;
  }
  site++;
  /* caso   iy = 0   0 < ix < L-1 */
  for (ix = 1; ix < L-1; ix++, site++) {
    sum = s[site] * (s[site+L2-L] + s[site-1] + s[site+1] + s[site+L]);
    if (sum <= 0 || FRANDOM < prob[sum]) {
      s[site] = -s[site];
      *pMag += 2 * s[site];
      *pEner += 2 * sum;
    }
  }
  /* caso   iy = 0   ix = L-1 */
  sum = s[site] * (s[site+L2-L] + s[site-1] + s[site+1-L] + s[site+L]);
  if (sum <= 0 || FRANDOM < prob[sum]) {
    s[site] = -s[site];
    *pMag += 2 * s[site];
    *pEner += 2 * sum;
  }
  site++;
  for (iy = 1; iy < L-1; iy++) {
    /* caso   0 < iy < L-1   ix = 0 */
    sum = s[site] * (s[site-L] + s[site+L-1] + s[site+1] + s[site+L]);
    if (sum <= 0 || FRANDOM < prob[sum]) {
      s[site] = -s[site];
      *pMag += 2 * s[site];
      *pEner += 2 * sum;
    }
    site++;
    /* caso   0 < iy < L-1   0 < ix < L-1 */
    for (ix = 1; ix < L-1; ix++, site++) {
      sum = s[site] * (s[site-L] + s[site-1] + s[site+1] + s[site+L]);
      if (sum <= 0 || FRANDOM < prob[sum]) {
	s[site] = -s[site];
	*pMag += 2 * s[site];
	*pEner += 2 * sum;
      }
    }
    /* caso   0 < iy < L-1   ix = L-1 */
    sum = s[site] * (s[site-L] + s[site-1] + s[site+1-L] + s[site+L]);
    if (sum <= 0 || FRANDOM < prob[sum]) {
      s[site] = -s[site];
      *pMag += 2 * s[site];
      *pEner += 2 * sum;
    }
    site++;
  }
  /* caso   iy = L-1   ix = 0 */
  sum = s[site] * (s[site-L] + s[site+L-1] + s[site+1] + s[site+L-L2]);
  if (sum <= 0 || FRANDOM < prob[sum]) {
    s[site] = -s[site];
    *pMag += 2 * s[site];
    *pEner += 2 * sum;
  }
  site++;
  /* caso   iy = L-1   0 < ix < L-1 */
  for (ix = 1; ix < L-1; ix++, site++) {
    sum = s[site] * (s[site-L] + s[site-1] + s[site+1] + s[site+L-L2]);
    if (sum <= 0 || FRANDOM < prob[sum]) {
      s[site] = -s[site];
      *pMag += 2 * s[site];
      *pEner += 2 * sum;
    }
  }
  /* caso   iy = L-1   ix = L-1 */
  sum = s[site] * (s[site-L] + s[site-1] + s[site+1-L] + s[site+L-L2]);
  if (sum <= 0 || FRANDOM < prob[sum]) {
    s[site] = -s[site];
    *pMag += 2 * s[site];
    *pEner += 2 * sum;
  }
}

void measures(int time, int *s) {
  int site, mag, ener;
  
  mag = 0; ener = 0;
  /* sommiamo quindi le interazioni orizzontali */
  for (site = 0; site < N; site++) {
    mag += s[site];
    /* quelli della prima colonna sono connessi a quelli dell'ultima */
    if (site % L == 0) {
      ener -= s[site] * s[site + L - 1];
    } else {
      ener -= s[site] * s[site - 1];
    }
  }
  /* sommiamo prima le interazioni verticali */
  for (site = 0; site < N - L; site++) {
    ener -= s[site] * s[site + L];
  }
  /* gli spin dell'ultima riga sono connessi a quelli della prima */
  for (site = N - L + 1; site < N; site++) {
    ener -= s[site] * s[site + L - N];
  }
  printf("%i %f %f\n", time, (float)mag / N, (float)ener / N);
}

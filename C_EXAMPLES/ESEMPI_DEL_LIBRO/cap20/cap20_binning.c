/*
  cap20_binning.c: Computing the error on a set of correlated data by binning.
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

#define L     20

#define L2   (L * L)
#define N     L2
#define DIM   2
#define CONN (2 * DIM)
#define Tc   (2.26918531421302)

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
void initSpin(int *s, int *pMag, int *pEner);
void oneSweep2D(int *s, float *prob, int *pMag, int *pEner);
void measures(int time, int *s);

int main(int argc, char *argv[]) {
  int i, numMeas, binSize;
  int t, thermMCS, numIter, s[N], mag, ener, tmp;
  float temperature, prob[CONN + 1], *m, *e, *pm, *pe, *pm2, *pe2;
  double aveM, aveE, aveM2, aveE2, invN = 1./ N;

  if (argc != 5) {
    fprintf(stderr,
	    "usage: %s <T> <thermMCS> <numIter> <seed>\n",
	    argv[0]);
    exit(EXIT_FAILURE);
  }
  temperature = atof(argv[1]);
  thermMCS = atoi(argv[2]);
  numIter = atoi(argv[3]);
  myrand = (unsigned)atoi(argv[4]);
  if (temperature < 0.0) temperature = Tc;
  numMeas = numIter;
  printf("# L = %d   T = %.3f   thermMCS = %i   numMeas = %i   random seed = %u\n", L, temperature, thermMCS, numMeas, myrand);
  printf("# binSize <M> error <E> error numMeas\n");
  fflush(stdout);
  m = calloc(numMeas, sizeof(int));
  e = calloc(numMeas, sizeof(int));
  initRandom();
  initProb(temperature, prob);
  initSpin(s, &mag, &ener);
  for (t = 0; t < thermMCS; t++) {
    oneSweep2D(s, prob, &mag, &ener);
  }
  for (t = 0; t < numIter; t++) {
    oneSweep2D(s, prob, &mag, &ener);
    m[t] = mag;
    e[t] = ener;
  }
  for (binSize = 1; binSize <= numMeas / 100; binSize *= 2) {
    tmp = (int)(numMeas / 2);
    pm = m; pm2 = m; pe = e; pe2 = e;
    aveM = 0.0; aveM2 = 0.0; aveE = 0.0; aveE2 = 0.0;
    for (i = 0; i < tmp; i++, pm++, pm2 += 2, pe++, pe2 += 2) {
      aveM += *pm2 + *(pm2 + 1);
      aveM2 += (double)(*pm2) * (*pm2) +
	(double)(*(pm2 + 1)) * (*(pm2 + 1));
      *pm = 0.5 * (*pm2 + *(pm2 + 1));
      aveE += *pe2 + *(pe2 + 1);
      aveE2 += (double)(*pe2) * (*pe2) +
	(double)(*(pe2 + 1)) * (*(pe2 + 1));
      *pe = 0.5 * (*pe2 + *(pe2 + 1));
    }
    numMeas = 2 * tmp;
    printf("%i %g %g %g %g %i\n", binSize, invN * aveM / numMeas,
	   invN * sqrt((aveM2 - aveM / numMeas * aveM) /
		numMeas / (numMeas - 1)), invN * aveE / numMeas,
	   invN * sqrt((aveE2 - aveE / numMeas * aveE) /
		numMeas / (numMeas - 1)), numMeas);
    numMeas = tmp;
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

void initSpin(int *s, int *pMag, int *pEner) {
  int site;

  *pMag = 0;
  for (site = 0; site < N; site++) {
    s[site] = pm1;
    *pMag += s[site];
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

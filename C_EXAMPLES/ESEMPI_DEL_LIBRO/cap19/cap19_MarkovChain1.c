/*
  cap19_MarkovChain1.c: Convergence on a simple Markov chain.
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

#define N 6

void error(char *);
void measures(int, float *, float *);
void oneStep(float *, float *);

int main(int argc, char *argv[]) {
  int i, niter;
  float p[N], pi[N] = {0, 0.3, 0, 0.1, 0.15, 0.45};
  float w[N*N] = {0.0, 0.0,   8./9, 0.0, 0.0,  0.0,
		  0.0, 3./5,  0.0,  0.0, 4./5, 0.0,
		  1.0, 0.0,   0.0,  0.0, 0.0,  0.0,
		  0.0, 1./3,  1./9, 0.0, 0.0,  0.0,
		  0.0, 0.0,   0.0,  0.0, 0.0,  1./3,
		  0.0, 1./15, 0.0,  1.0, 1./5, 2./3};

  if (argc != 2) {
    fprintf(stderr, "usage: %s <niter>\n", argv[0]);
    exit(1);
  }
  
  niter = (unsigned)atoi(argv[1]);

  printf("# Configurazione iniziale?\n");
  for (i = 0; i < N; i++) {
    scanf("%f", p+i);
  }
  measures(0, p, pi);
  for (i = 1; i <= niter; i++) {
    oneStep(p, w);
    measures(i, p, pi);
  }
  return 0;
}

void oneStep(float *p, float *w) {
  int i, j;
  float tmp[N];

  for (i = 0; i < N; i++) {
    tmp[i] = 0.0;
    for (j = 0; j < N; j++, w++) {
      tmp[i] += *w * p[j];
    }
  }
  for (i = 0; i < N; i++) {
    p[i] = tmp[i];
  }
}

void measures(int time, float *p, float *pi) {
  int i;
  float dist1=0.0, dist2=0.0, norm=0.0;

  for (i = 0; i < N; i++) {
    norm += p[i];
  }
  for (i = 0; i < N; i++) {
    p[i] /= norm;
    dist1 += fabs(p[i] - pi[i]);
    dist2 += (p[i] - pi[i]) * (p[i] - pi[i]);
  }
  printf("%i %g %g\n", time, dist1, sqrt(dist2));
}

void error(char *string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}

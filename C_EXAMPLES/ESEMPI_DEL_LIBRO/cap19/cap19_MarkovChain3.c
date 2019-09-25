/*
  cap19_MarkovChain3.c: Convergence on a 1-dimensional, but large, Markov chain.
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

#define N 999

void measures(int, double *);
void oneStep(double *);

int main(int argc, char *argv[]) {
  int i, t, niter, measTime;
  double p[N];

  if (argc != 2) {
    fprintf(stderr, "usage: %s <niter>\n", argv[0]);
    exit(1);
  }
  
  niter = (unsigned)atoi(argv[1]);

  p[0] = 1.0;
  for (i = 1; i < N; i++) {
    p[i] = 0.0;
  }
  measures(0, p);
  measTime = 1;
  t = 0;
  while (measTime <= niter) {
    oneStep(p);
    t++;
    if (t == measTime) {
      measures(t, p);
      measTime = (int)(measTime * 1.05) + 1;
    }
  }
  return 0;
}

void oneStep(double *p) {
  int i;
  double tmp[N];

  tmp[0] = 0.5 * (p[N-1] + p[1]);
  for (i = 1; i < N-1; i++) {
    tmp[i] = 0.5 * (p[i-1] + p[i+1]);
  }
  tmp[N-1] = 0.5 * (p[N-2] + p[0]);
  for (i = 0; i < N; i++) {
    p[i] = tmp[i];
  }
}

void measures(int time, double *p) {
  int i;
  double invN=1.0/N, dist1=0.0, dist2=0.0;

  for (i = 0; i < N; i++) {
    dist1 += fabs(p[i] - invN);
    dist2 += (p[i] - invN) * (p[i] - invN);
  }
  printf("%i %g %g\n", time, dist1, sqrt(dist2));
  fflush(stdout);
}

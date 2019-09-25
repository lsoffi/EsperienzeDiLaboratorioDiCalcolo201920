/*
  cap18_densStatesIsing2D.c: Enumerating the configurations of the 2D Ising model, to obtain the density of states.
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

#define L     4

#define L2   (L * L)
#define N     L2
#define DIM   2
#define CONN (2 * DIM)

int main(int argc, char *argv[]) {
  int i, j, ix, iy, site, neigh[N][CONN], *pNeigh, s[N], ener, mag, sum;
  unsigned long long int t, mask, histo[N + 1][N + 1]={{0}};
  unsigned long long int histoMag[N + 1]={0}, histoEner[N + 1]={0};

  printf("# enumerazione esaustiva configurazioni\n"
	 "# del modello di Ising in 2D con L = %i\n", L);
  printf("# mag ener num.conf.\n");
  fflush(stdout);
  
  for (iy = 0; iy < L; iy++) {
    for (ix = 0; ix < L; ix++) {
      site = ix + iy * L;
      pNeigh = neigh[site];
      pNeigh[0] = ((ix + 1) % L) + iy * L;
      pNeigh[1] = ix + ((iy + 1) % L) * L;
      pNeigh[2] = ((ix + L - 1) % L) + iy * L;
      pNeigh[3] = ix + ((iy + L - 1) % L) * L;
    }
  }  
  for (i = 0; i < N; i++) s[i] = 1;
  mag = N;
  ener = -DIM * N;
  histo[(mag + N) / 2][(ener + DIM * N) / 4]++;
  histoMag[(mag + N) / 2]++;
  histoEner[(ener + DIM * N) / 4]++;
  for (t = 0; t < (1ULL<<N)-1; t++) {
    mask = 1; i = 0;
    while (t & mask) {
      mask = mask << 1;
      i++;
    }
    s[i] = -s[i];
    pNeigh = neigh[i];
    sum = s[pNeigh[0]] + s[pNeigh[1]] + s[pNeigh[2]] + s[pNeigh[3]];
    mag += 2 * s[i];
    ener -= 2 * sum * s[i];
    histo[(mag + N) / 2][(ener + DIM * N) / 4]++;
    histoMag[(mag + N) / 2]++;
    histoEner[(ener + DIM * N) / 4]++;
  }
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++){
      printf("%i %i %llu\n", 2 * i - N, 4 * j - DIM * N, histo[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
  for (i = 0; i <= N; i++) {
    printf("%i %llu\n", 2 * i - N, histoMag[i]);
  }
  printf("\n\n");
  for (j = 0; j <= N; j++) {
    printf("%i %llu\n", 4 * j - DIM * N, histoEner[j]);
  }
  printf("\n\n");
  return EXIT_SUCCESS;
}

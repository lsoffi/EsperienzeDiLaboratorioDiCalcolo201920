/*
  cap04_kahan.c: Kahan algorithm implementation
  Copyright (C) 2006 Giovanni Organtini (G.Organtini@roma1.infn.it)

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

#include <stdio.h>

#define N 10000000

main() {
  float sum=0., corr=0., x = 7.;
  int i;
  for(i=0; i<N; i++) {
    float tmp, y;
    y = corr + x;
    tmp = sum + y;
    corr = (sum - tmp) + y; 
    sum = tmp;
  }
  sum += corr;
  printf("Using floats  : %.0f x %d = %.0f\n", x, N, sum);
}

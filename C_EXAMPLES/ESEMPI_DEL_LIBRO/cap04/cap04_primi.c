/*
  cap04_primi.c: Prime numbers
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

#include <math.h>

#define N 100

main() {
  int i;
  printf("I numeri primi tra 2 e %d sono\n", N);
  for (i = 1; i < N; i++) { 
    int j = 2, jMax = (int)sqrt(i) + 1;
    while ((j < jMax) && (i % j)) { 
      j++;
    }
    if (j == jMax) {
      printf("%d\n", i);
    } 
  }
}

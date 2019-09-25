/*
  cap04_bisezione.c: Newton'd method to solve equations
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
#include <stdio.h>

#define EPSILON 1.e-5

main() {
  double a = 0., b = M_PI, c;
  double delta = fabs(a - b);
  int i = 1;
  printf("Questo programma trova la soluzione "
         "dell'equazione cos(x)=0 in (0, PI)\n");
  while (delta > EPSILON) {
    double p;
    c = 0.5 * (a + b);
    p = cos(a) * cos(c);
    if (p > 0.) {
      a = c;
    } else if (p < 0.) {
      b = c;
    } else { 
      a = b = c; /* soluzione esatta */
    }
    printf("Iterazione n. %d: x = %f\n", i++, 
	   0.5 * (a + b));
    delta = fabs(a - b);
  }
  printf("La soluzione trovata vale: %f\n", c);
  printf("La soluzione vera vale   : %f\n", 0.5 * M_PI);
  printf("La differenza vale       : %e\n", 
         fabs(0.5 * M_PI - c));
}

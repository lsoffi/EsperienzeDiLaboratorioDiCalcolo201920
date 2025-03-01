/*
  cap04_conversione_2.c: Temperature conversion
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

main() {
  double tIn, tOut, offset, conv;
  int option = 0;
  
  offset = 32.;
  printf("Premi\n'1' per trasformare da F a C\n"
	 "'2' per trasformare da C a F\n\nScelta:");
  scanf("%d", &option);
  if (option == 1) {
    conv = 5./ 9.;
    printf("Valore in gradi Fahrenheit= ");
    scanf("%lf",&tIn);
    tOut = (tIn - offset) * conv;
    printf("Valore in gradi Celsius= %f\n",tOut);
  } else {
    conv = 9./ 5.;
    printf("Valore in gradi Celsius= ");
    scanf("%lf", &tIn);
    tOut = tIn * conv + offset;
    printf("Valore in gradi Fahrenheit= %f\n",tOut);
  }
}

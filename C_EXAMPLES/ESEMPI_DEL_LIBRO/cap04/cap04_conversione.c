/*
  cap04_conversione.c: Temperature conversion
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

#define TF2TC 

main() {
  double tc, tf, offset, conv;
  
  offset = 32.;
#ifdef TF2TC   
  conv = 5. / 9.;
  printf("Valore in gradi Fahrenheit= ");
  scanf("%lf",&tf);
  tc = (tf - offset) * conv;
  printf("Valore in gradi celsius= %f\n",tc);
#endif
#ifndef TF2TC
  conv = 9. / 5.;
  printf("Valore in gradi celsius= ");
  scanf("%lf", &tc);
  if (tc < -273.16) printf("Attenzione! T<0 K...\n");
  tf = tc * conv + offset;
  printf("Valore in gradi Fahrenheit= %f\n",tf);
#endif
}

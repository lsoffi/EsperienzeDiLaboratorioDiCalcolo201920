#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define G 9.82

/* questo programma calcola le coordinate x,y di un peso
lanciato ad angolo theta con l'asse x, e v iniziale
v0. Tutte le grandezze vanno considerate nel sistema MKS */

main() {
  double t = 0;          /* tempo */         
  double theta;          /* angolo di lancio */
  double v0, v0x, v0y;   /* v iniziale  */
  double xt, yt, vx, vy;

  printf("Inserisci l'angolo di lancio in radianti: ");
  scanf("%lf", &theta);
  printf("\nInserisci la velocita' iniziale: ");
  scanf("%lf", &v0);
  printf("\nInserisci il valore del tempo t in m/sec: ");
  scanf("%lf", &t);
/* Calcola le componenti di v */
  v0x = v0 * cos(theta);
  v0y = v0 * sin(theta);
  vx = v0x;
  vy = v0y - G * t;
/* ora calcola le coordinate */
  xt = vx * t;
  yt = v0y * t - 0.5 * G * pow(t, 2.0);
  printf("\nLe coordinate al tempo %lf sono x = %lf, y = %lf\n"
  , t, xt, yt);
  exit(0);
}

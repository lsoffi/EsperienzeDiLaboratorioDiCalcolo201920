#include<stdio.h>
#include<stdlib.h>
#define G 9.82 // m/s^2
int main(int argc, char** argv)
{
  double K, U, m, v0, h0, t, v, h;
  printf("Immetti la massa del grave (kg):");
  scanf("%lf", &m);  // kg
  printf("Immetti la velocità iniziale del grave (m/s):");
  scanf("%lf", &v0); // m/s
  printf("Immetti l'altezza da cui viene lanciato (m):");
  scanf("%lf", &h0); // m

  printf("Tempo a cui calcolare energia cinetica e potenziale (s):");
  scanf("%lf", &t);

  // direzione positiva verso l'alto
  v = v0 - G*t;
  h = -0.5*G*t*t + v0*t + h0;
  K = 0.5*m*v*v;
  U = m*G*h;
  printf("L'energia cinetica vale %.7f J\n", K);
  printf("L'energia potenziale vale %.7f J\n", U);
  return 0;
}

#include <stdio.h>
#include <math.h>

#define N 100
void triangle(int, double [][], double *);
void solve(int, double [][], double *, double *);
main() {
/* soluzione dei sistemi di equazioni con il metodo di eliminazione
     delle incognite di Gauss */
  double A[N][N], b[N], x[N];
  int n, i, j;
/* inserisce i dati iniziali */
  printf(" Inserisci il numero di equazioni (<100): ");
  scanf("%d", &n);
  printf("\n Inserisci ora i coefficienti del sistema 
           e i termini noti\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("A[%d, %d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
    printf("b[%d] = ", i);
    scanf("%lf", &b[i]);
  }
/*  triangolarizza la matrice */
  triangle(n, A, b);
/*  risolve */
  solve(n, A, b, x); 
/*   stampa il risultato */ 
  for (i = 0; i < n; i++) {
    printf("x[%d] = %lf\n", i, x[i]);
  } 
}
void triangle(int n, double a[N][N], double *b) {
  int i, j, k;
  double c;
  for (i = 0; i < n; i++) {
/* divide l'i-esima equazione per l'elemento diagonale C */
    c = a[i][i];
    for (j = i; j < n; j++) {
      a[i][j] /= c;
    }
    *(b + i) /= c;
/* sottrae l'equazione normalizzata dalle altre */
    for (k = i + 1; k < n; k++) {
      c = a[k][i];
      for (j = i; j < n; j++) {
	a[k][j] -= a[i][j] * c;
      }
      b[k] -= c * b[i];
    }   
  }
}

void solve(int n, double a[N][N], double *b, double *x) {
  int i, k;
  double s;  
  x[n] = b[n] / a[n][n];
  for (k = n - 1; k >= 0; k--) {
    s = 0.;
    for (i = k + 1; i < n; i++) {
      s += a[k][i] * x[i];
    }
    x[k] = b[k] - s;
  }
}

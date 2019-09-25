#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1.e-15

void dumpTableau(double **t, int n, int m) {
  int i, j;
  printf("Tableau\n");
  for (i = 0; i <= n; i++) {
    for (j = 0; j <= m; j++) {
      printf("%+5f ", t[i][j]);
    }
    printf("\n");
  }
}

int minC(double *line, int size) {
  int i = 0, index = 0;
  double minimum = line[i];

  for (i = 0; i < size; i++) {
    if (minimum > line[i]) {
      minimum = line[i];
      index = i;
    }
  }
  if (line[index] >= 0.) {
    return -1;
  } else {
    return index;
  }
}

int maxC(double **tableau, int size, int col, int k) {
  int i = 0, index = 0;
  double minimum = tableau[i][k]/tableau[i][col];
  while (minimum < 0) {
    i++;
    minimum = tableau[i][k]/tableau[i][col];
  }
  for (; i < size; i++) {
    if ((tableau[i][col] > 0) && (minimum > tableau[i][k]/tableau[i][col])) {
      minimum = tableau[i][k]/tableau[i][col];
      index = i;
    }
  }
  return index;
}

void rmArtificialVar(double *a, int m, int s, int r, double **tableau) {
  int j;
  double *ap = (double *)calloc(m + 1, sizeof(double));
  for (j = 0; j < m; j++) {
    ap[j] = a[j];
  }
  for (j = 0; j < m; j++) {
    a[j] -= ap[s]*tableau[r][j]/tableau[r][s];
  }
  free(ap);
}

void removeVariable(double **a, int n, int m, int r, int s) {
  int i, j;
  double **ap = (double **)calloc(n + 1, sizeof(double*));
  for (i = 0; i <= n; i++) {
    ap[i] = (double *)calloc(m + 1, sizeof(double));
    for (j = 0; j <= m; j++) {
      ap[i][j] = a[i][j];
    }
  }
  for (i = 0; i <= n; i++) {
    if (i != r) {
      for (j = 0; j <= m; j++) {
	a[i][j] -= ap[i][s]*ap[r][j]/ap[r][s];
	if (fabs(a[i][j]) < EPSILON) {
	  a[i][j] = 0.;
	}
      }
    } else {
      for (j = 0; j <= m; j++) {
	a[i][j] = ap[i][j]/ap[i][s];
	if (fabs(a[i][j]) < EPSILON) {
	  a[i][j] = 0.;
	}
      }
    }
  }
  for (i = 0; i <= n; i++) {
    free(ap[i]);
  }
  free(ap);
}

void findBasis(double *x, double **a, int n, int m) {
  int i, j, s, count;

  for (j = 0; j < m; j++) {
    count = 0;
    for (i = 0; i < n; i++) {
      if (a[i][j] != 0.) {
	count++;
	s = i;
      }
    } 
    if (count == 1) {
      if ((x[j] = a[s][m]/a[s][j]) < 0) { 
	x[j] = 0; 
      }
    } else {
      x[j] = 0;
    }
  }
}

void dumpBasis(double *x, int n) {
  int i;
  printf("Current Basis:\n");
  for (i = 0; i < n; i++) {
    printf("x_%d = %f\n", i, x[i]);
  }
}

double weight(double *x, int n) {
  double w = 0.;
  int i;
  for (i = 0; i < n; i++) {
    w += x[i];
  }
  return w;
}

void dump(double *x, int n, char *s) {
  int i;
  for (i=0; i < n; i++) {
    printf("%s[%d] = %f\n", s, i, x[i]);
  }
}

main() {
  int n, m, k, i, j, s, r, iter = 1;
  double **tableau;
  double *basis, *wobj, w, z;

  printf("Inserisci il numero di equazioni: ");
  scanf("%d", &n);
  printf("Inserisci il numero totale di incognite: ");
  scanf("%d", &m);
  printf("Inserisci il numero di incognite artificiali: ");
  scanf("%d", &k);

  // input phase
  basis = (double *)calloc(m, sizeof(double));
  tableau = (double **)calloc(n + 1, sizeof(double*));
  for (i = 0; i < n; i++) {
    tableau[i] = (double *)calloc(m + 1, sizeof(double));
    for (j = 0; j < m; j++) {
      printf("coeff. %2d, %2d: ", i+1, j+1);
      scanf("%lf", &tableau[i][j]);
    }
    printf("termine noto eq. %2d: ", i+1);
    scanf("%lf", &tableau[i][m]);
  }
  tableau[n] = (double *)calloc(m + 1, sizeof(double));
  for (j = 0; j < m; j++) {
	printf("cost coeff. %2d: ", j+1);
	scanf("%lf", &tableau[n][j]);
  }

  printf("\n-----------------------\n");
  findBasis(basis, tableau, n, m);
  dumpBasis(basis, m);
  if (k > 0) {
    wobj = (double *)calloc(m, sizeof(double));
    printf("Created an array of %d components\n", m);
    for (i = 0; i < m - k; i++) {
      wobj[i] = 0.;
      for (j = m; j > m - k; j--) {
	if (basis[j] > 0) {
	  wobj[i] -= tableau[n - 1 - m + j][i];
	}
      }
    }
    dump(wobj, m, "w");
  }

  // dump the initial tableau
  dumpTableau(tableau, n, m);

  do {
    printf("---------- Iteration n. %3d -------------------------\n", iter++); 
    findBasis(basis, tableau, n, m);
    dumpBasis(basis, m);
    
    if (k > 0) {
      // look for the minimum cost coefficient within the wobj line
      s = minC(wobj, m);
    } else {
      s = minC(tableau[n], m);
    }
    printf("We found s = %d\n", s);
    if (s >= 0) {
      r = maxC(tableau, n, s, m);
      printf("We found r = %d\n", r);
      if (k > 0) {
	rmArtificialVar(wobj, m, s, r, tableau);
      }
      removeVariable(tableau, n, m, r, s);
    }
    dumpTableau(tableau, n, m);
    if (k > 0) {
      dump(wobj, m, "w");
      // compute w
      w = weight(wobj, m - k);
      printf("w = %f\n", w);
      if (w == 0.) {
	k = 0;       
      }
    }
    z = weight(tableau[n], m);
    printf("Now z is %f\n", -z);
  } while (s >= 0);
  findBasis(basis, tableau, n, m);
  printf("The solution is:\n");
  dumpBasis(basis, m);

  for (i = 0; i <= n; i++) {
    free(tableau[i]);
  }
  free(tableau);
  free(basis);
  free(wobj);
}

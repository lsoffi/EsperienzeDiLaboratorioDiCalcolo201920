double Lagrange(double y, double *f, double *x, int n) {
  double P, S = 0.;
  int i, j;

  for (i = 0; i < n; i++) {
    P = 1.;
    for (j = 0; j < n; j++) {
      if (j != i) {
	P *= (y - x[j]) / (x[i] - x[j]);
      }
    }
    S += P*f[i];
  }
  return S;
}


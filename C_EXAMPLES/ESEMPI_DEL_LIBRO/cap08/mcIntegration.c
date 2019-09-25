double mcIntegration(double a, double b, int N, 
		     double (*f)(double)) {
  int i;
  double S = 0.;
  double x;

  for (i = 0; i < n; i++) {
    x = a + (b - a) * (double)lrand48() / (double)RAND_MAX;
    S += (*f)(x);
  }
  return S * (b - a) / N;
}

double midpoint(double a, double b, int n, double (*f)(double)) {
  /* Una buona realizzazione dell'algoritmo del punto di mezzo */
  double I = 0., x, h = (b - a) / (double) n;
  int i;

  for (i = 0; i < n; i++) {
    x = a + h * i + 0.5 * h;
    I += (*f)(x);
  }
  return I * h;
}

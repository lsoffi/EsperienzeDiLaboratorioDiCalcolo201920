double midpoint(double a, double b, int n, double (*f)(double)) {
  /* una cattiva realizzazione dell'algoritmo del punto di mezzo */
  double I = 0., x = a;
  double h = (b - a) / (double) n;

  while (x < b) { 
    I += (*f)(x + 0.5 * delta);
    x += h;
  }
  return I * h;
}

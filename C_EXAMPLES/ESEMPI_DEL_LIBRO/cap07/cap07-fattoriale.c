unsigned long long int factorial(int n ) {
  int i;
  unsigned long long int p = 1;
  for (i = 1; i <= n; i++) {
    p *= i;
  }
  return p;
}

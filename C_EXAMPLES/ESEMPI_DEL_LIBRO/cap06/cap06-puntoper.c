#define LEN 10

main() {
  double data[LEN] = {3.14, 1.57}, *pd;
  double a, b, c;
  int k = 2;

  pd = data;
  a = *(pd + 1);
  pd++;
  b = *(pd - 1);
  c = *(pd + k);
}

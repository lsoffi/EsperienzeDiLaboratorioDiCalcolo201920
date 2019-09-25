main() {
  int a[3], d[3];
  int *pointer;
  a = d;      /* operazione vietata */
  a = &d[0];  /* operazione vietata */
  pointer = d;
}

void bubblesort(int data[], int n) {
  int i, temp, *pd;
  for (i = 0; i < n - 1; i++) {
    for (pd = data + n - 1; pd > data + i; pd--) {
      if (*(pd - 1) > *pd) {
        temp = *(pd - 1);
	*(pd - 1) = *pd;
	*pd = temp;
      }
    }
  }
}
